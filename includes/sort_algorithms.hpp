#ifndef SF_SORT_HPP
#define SF_SORT_HPP

#include <thread>

template<typename RandomIt>
void parallel_intro_sort(RandomIt start, RandomIt end);

template<typename RandomIt>
static void __parallel_intro_sort(RandomIt start, RandomIt end, unsigned int depth_check, unsigned int threshold) {
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

    if (std::distance(start, end) <= threshold) {
        __parallel_intro_sort(start, pivot, depth_check, threshold);
        __parallel_intro_sort(pivot + 1, end, depth_check, threshold);
    } else {
        std::thread t1{[=]() {
            __parallel_intro_sort(start, pivot, depth_check, threshold);
        }};
        __parallel_intro_sort(pivot + 1, end, depth_check, threshold);
        t1.join();
    }
}

template<typename RandomIt>
void parallel_intro_sort(RandomIt start, RandomIt end) {
    unsigned int core_count = std::thread::hardware_concurrency();
    unsigned int threshold = std::distance(start, end) / core_count;
    __parallel_intro_sort(start, end, 2 * std::log(std::distance(start, end)), threshold);
}

#endif