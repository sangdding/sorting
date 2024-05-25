#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

// sort_algorithms 헤더에 모든 정렬 알고리즘의 전방 선언이 모여있습니다.
#include "intro_sort.hpp"
#include "temp_sort_algorithms.hpp"
#include "utility.h"
#include <cstring>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

template <typename T>
void parallel(std::vector<T> V, unsigned int num)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    parallel_intro_sort_thread(V.begin(), V.end() - 1, num);
    auto finish_time = std::chrono::high_resolution_clock::now();
    std::cout << V.size() << ',' << num << ',' << get_pretty_time((finish_time - start_time).count()) << '\n';
}

int main()
{

    unsigned int thread_num = 1;
    int size;
    
    std::random_device rd;  // 하드웨어를 기반으로 랜덤 수 생성기 초기화
    std::mt19937 gen(rd()); // 메르센 트위스터 알고리즘 사용
    std::uniform_int_distribution<> dis(1, 1000000); // 1과 1000000 사이의 균등 분포

    for (; thread_num <= 32; thread_num *= 2)
    {
        for (size = 100000; size <= 10000000; size *= 10)
        {
            std::vector<int> I(size);
            std::generate(I.begin(), I.end(), [&]()
                          { return dis(gen); });

            parallel(I, thread_num);
        }
    }

    return 0;
}