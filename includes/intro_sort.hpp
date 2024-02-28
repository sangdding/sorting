
#ifndef SFSORT_INTRO_SORT_UTILITY_HPP
#define SFSORT_INTRO_SORT_UTILITY_HPP

#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

template <typename RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
    for (auto i = first + 1; i != last; ++i) {
        auto key = *i;
        auto j = i - 1;
        while (j >= first && *j > key) {
            *(j + 1) = *j;
            --j;
        }
        *(j + 1) = key;
    }
}

template <typename RandomIt>
void heap_sort(RandomIt first, RandomIt last) {
    std::make_heap(first, last);
    std::sort_heap(first, last);
}

template <typename RandomIt>
void introsort_util(RandomIt first, RandomIt last, int depthLimit) {
    int size = std::distance(first, last);

    if (size < 16) {
        insertion_sort(first, last);
    } else if (depthLimit == 0) {
        heap_sort(first, last);
    } else {
        RandomIt pivot = std::partition(first, last, [pivot = *first](const auto& em) { return em < pivot; });
        introsort_util(first, pivot, depthLimit - 1);
        introsort_util(pivot, last, depthLimit - 1);
    }
}

template <typename RandomIt>
void intro_sort(RandomIt first, RandomIt last) {
    int depthLimit = 2 * std::log(std::distance(first, last));
    introsort_util(first, last, depthLimit);
}

template<typename Iterator>
void set_pivot(Iterator dest, Iterator a, Iterator b, Iterator c) {
    if (*a < *b) {
        if (*b < *c)
            std::iter_swap(dest, b);
        else if (*a < *c)
            std::iter_swap(dest, c);
        else
            std::iter_swap(dest, a);
    } else if (*a < *c)
        std::iter_swap(dest, a);
    else if (*b < *c)
        std::iter_swap(dest, c);
    else
        std::iter_swap(dest, b);
}

template<typename Iterator>
Iterator partition(Iterator pivot, Iterator start, Iterator end) {
    end--; // 마지막 요소로 이동하기 위해
    while (true) {
        do start++;
        while (start < end && *start < *pivot);
        do end--;
        while (start < end && *pivot < *end);
        if (end <= start) {
            std::iter_swap(end, pivot);
            return end;
        }
        std::iter_swap(end, start);
    }
}

#endif //SFSORT_INTRO_SORT_UTILITY_H