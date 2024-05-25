#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

// sort_algorithms 헤더에 모든 정렬 알고리즘의 전방 선언이 모여있습니다.
#include "aips2o.hpp"
#include "intro_sort.hpp"
#include "sort_algorithms.hpp"
#include "data_generator.h"
#include "skim_generator.h"
#include "utility.h"
#include "ips4o.hpp"
#include <cstring>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>


template <typename T>
void stl(std::vector<T> V)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << get_pretty_time((finish_time - start_time).count()) << ' ';
}
                                                                                                                
template <typename T>
void merge(std::vector<T> V)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::stable_sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << get_pretty_time((finish_time - start_time).count()) << ' ';
}

template <typename T>
void parallel(std::vector<T> V)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    parallel_intro_sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << get_pretty_time((finish_time - start_time).count()) << ' ';
}

template <typename T>
void aips(std::vector<T> V)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    aips2o::sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << get_pretty_time((finish_time - start_time).count()) << '\n';
}

int main()
{

    int size;
    
    std::random_device rd;  // 하드웨어를 기반으로 랜덤 수 생성기 초기화
    std::mt19937 gen(rd()); // 메르센 트위스터 알고리즘 사용
    std::uniform_int_distribution<> dis(1, 1000000); // 1과 1000000 사이의 균등 분포

    for(size = 1000; size <= 100000; size++) {
        std::vector<int> I(size);
        skim_generator<int> *gen_i = new skim_generator<int>(I);
        std::generate(I.begin(), I.end(), [&]() { return dis(gen); });

        stl(I);
        merge(I);
        parallel(I);
        aips(I);
    }

    
    return 0;
}