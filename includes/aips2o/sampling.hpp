/******************************************************************************
 * include/aips2o/sampling.hpp
 *
 * In-place Parallel Super Scalar Samplesort (IPS⁴o)
 *
 ******************************************************************************
 * BSD 2-Clause License
 *
 * Copyright © 2017, Michael Axtmann <michael.axtmann@gmail.com>
 * Copyright © 2017, Daniel Ferizovic <daniel.ferizovic@student.kit.edu>
 * Copyright © 2017, Sascha Witt <sascha.witt@kit.edu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#pragma once

#include <iterator>
#include <random>
#include <utility>

#include "aips2o_fwd.hpp"
#include "classifier.hpp"
#include "config.hpp"
#include "memory.hpp"
#include "rmi.hpp"

#define RMI_THRESHOLD 1000000
#define DISTINCT_PERC_THRESOLD 0.9

namespace aips2o {
namespace detail {

/**
 * Selects a random sample in-place.
 */
template <class It, class RandomGen>
void selectSample(It begin, const It end,
                  typename std::iterator_traits<It>::difference_type num_samples,
                  RandomGen&& gen) {
    using std::swap;

    auto n = end - begin;
    while (num_samples--) {
        const auto i = std::uniform_int_distribution<
                typename std::iterator_traits<It>::difference_type>(0, --n)(gen);
        swap(*begin, begin[i]);
        ++begin;
    }
}

/**
 * Builds the classifer.
 * Number of used_buckets is a power of two and at least two.
 */
template <class Cfg>
std::pair<int, bool> Sorter<Cfg>::buildClassifier(const iterator begin,
                                                  const iterator end,
                                                  Classifier& classifier) {
    const auto n = end - begin;
    int log_buckets = Cfg::logBuckets(n);
    int num_buckets = 1 << log_buckets;
    const auto step = std::max<diff_t>(1, Cfg::oversamplingFactor(n));
    const auto num_samples = std::min(step * num_buckets - 1, n / 2);

    // Select the sample
    detail::selectSample(begin, end, num_samples, local_.random_generator);

    // Sort the sample
    sequential(begin, begin + num_samples);

    int distinct_values = 1;

    for(int i = 1; i < num_samples; i++) {
        if (begin[i] != begin[i-1]) {
            distinct_values++;
        }
    }

    bool too_many_duplicates = distinct_values <= (DISTINCT_PERC_THRESOLD * num_samples);

    if (n >= RMI_THRESHOLD && !too_many_duplicates) {

        const int rmi_log_buckets = 10;
        const int rmi_num_buckets = (1 << rmi_log_buckets);

        auto rmi_samples = std::max(n/100, num_samples);

        if (rmi_samples - num_samples > 0) {
            detail::selectSample(
                begin + num_samples, end, rmi_samples - num_samples, local_.random_generator
            );
            sequential(begin, begin + rmi_samples);
        }

        typename learned_sort::TwoLayerRMI<iterator>::Params p;
        learned_sort::TwoLayerRMI<iterator> recursive_model_index(p);
        recursive_model_index.train(begin, begin + rmi_samples);

        classifier.build_with_rmi(rmi_log_buckets, recursive_model_index);
        this->classifier_ = &classifier;

        return {rmi_num_buckets, 0};
    }    
    else {
        auto splitter = begin + step - 1;
        auto sorted_splitters = classifier.getSortedSplitters();
        const auto comp = classifier.getComparator();

        // Choose the splitters
        AIPS2OML_ASSUME_NOT(sorted_splitters == nullptr);
        new (sorted_splitters) typename Cfg::value_type(*splitter);
        for (int i = 2; i < num_buckets; ++i) {
            splitter += step;
            // Skip duplicates
            if (comp(*sorted_splitters, *splitter)) {
                AIPS2OML_ASSUME_NOT(sorted_splitters + 1 == nullptr);
                new (++sorted_splitters) typename Cfg::value_type(*splitter);
            }
        }

        // Check for duplicate splitters
        const auto diff_splitters = sorted_splitters - classifier.getSortedSplitters() + 1;
        const bool use_equal_buckets = Cfg::kAllowEqualBuckets
                && num_buckets - 1 - diff_splitters >= Cfg::kEqualBucketsThreshold;

        // Fill the array to the next power of two
        log_buckets = log2(diff_splitters) + 1;
        num_buckets = 1 << log_buckets;
        for (int i = diff_splitters + 1; i < num_buckets; ++i) {
            AIPS2OML_ASSUME_NOT(sorted_splitters + 1 == nullptr);
            new (++sorted_splitters) typename Cfg::value_type(*splitter);
        }

        // Build the tree
        classifier.build(log_buckets);
        this->classifier_ = &classifier;

        const int used_buckets = num_buckets * (1 + use_equal_buckets);
        return {used_buckets, use_equal_buckets};
    }
}

}  // namespace detail
}  // namespace aips2o
