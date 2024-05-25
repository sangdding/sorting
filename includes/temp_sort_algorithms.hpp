#ifndef SF_SORT_HPP
#define SF_SORT_HPP

#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>

template<typename RandomIt>
void parallel_intro_sort_thread(RandomIt start, RandomIt end, unsigned int num_threads);

template<typename RandomIt>
static void __parallel_intro_sort_thread(RandomIt start, RandomIt end, unsigned int depth_check, unsigned int num_threads) {
    if (std::distance(start, end) <= 1) return;

    if (std::distance(start, end) <= 32) {
        insertion_sort(start, end); // 반복자 기반 삽입 정렬 함수 필요
        return;
    }

    if (depth_check <= 0) {
        std::make_heap(start, end);
        std::sort_heap(start, end);
        return;
    }

    auto mid = start;
    std::advance(mid, std::distance(start, end) / 2);
    set_pivot(start, start + 1, mid, end - 1); // 반복자 기반 set_pivot 함수 필요
    auto pivot = partition(start, start, end); // 반복자 기반 partition 함수 필요

    depth_check = (depth_check >> 1) + (depth_check >> 2);

    if (num_threads > 1) {
        std::thread t1{[=]() {
            __parallel_intro_sort_thread(start, pivot, depth_check, num_threads / 2);
        }};
        __parallel_intro_sort_thread(pivot + 1, end, depth_check, num_threads - num_threads / 2);
        t1.join();
    } else {
        __parallel_intro_sort_thread(start, pivot, depth_check, 1);
        __parallel_intro_sort_thread(pivot + 1, end, depth_check, 1);
    }
}

template<typename RandomIt>
void parallel_intro_sort_thread(RandomIt start, RandomIt end, unsigned int num_threads) {
    __parallel_intro_sort_thread(start, end, 2 * std::log2(std::distance(start, end)), num_threads);
}

#endif
