#include <iostream>

//sort_algorithms 헤더에 모든 정렬 알고리즘의 전방 선언이 모여있습니다.
#include "aips2o.hpp"
#include "sort_algorithms.h"
#include "data_generator.h"
#include "utility.h"
#include "ips4o.hpp"
#include <cstring>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

//간단한 사용 예시입니다.
int main() {
    const int size = 100000000;
    data_generator *gen = new data_generator(size);
    int *data = new int[size];
    
    // SKIM::make container
    std::vector<int> V;

    cout << "num data: " << size << '\n';

    //제네레이터가 가진 데이터를 무작위로 뒤섞습니다.
    auto st_t = std::chrono::high_resolution_clock::now();
    gen->make_all_rand();
    auto ed_t = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>sec = ed_t - st_t;
    cout << "data randomize time: " << sec.count() << '\n';

    // SKIM::Init Vector
    for (int i = 0; i < size; i++) {
	V.push_back(data[i]);
    }

    //뒤섞인 데이터를 임시 배열에 복사합니다.
    st_t = std::chrono::high_resolution_clock::now();
    memcpy(data, gen->get_data(), size * sizeof(int));
    ed_t = std::chrono::high_resolution_clock::now();
    sec = ed_t - st_t;
    cout << "generated data memcopy time: " << sec.count() << '\n';


    //Sorting algorithms and time
   // cout << "1. insertion sort: " << get_pretty_time(get_proc_time(insertion_sort, data, data + size)) << '\n';

    memcpy(data, gen->get_data(), size * sizeof(int));
    cout << "2. intro sort: " << get_pretty_time(get_proc_time(intro_sort, data, data + size)) << '\n';

    memcpy(data, gen->get_data(), size * sizeof(int));
    cout << "3. parallel intro sort: " << get_pretty_time(get_proc_time(parallel_intro_sort, data, data + size)) << '\n';

    //똑같은 데이터를 다시 복사해서 STL sort의 실행 시간을 측정합니다.
    memcpy(data, gen->get_data(), size * sizeof(int));
    cout << "4. STL sort (quick sort): " << get_pretty_time(get_proc_time(sort<int*>, data, data + size)) << '\n';

    memcpy(data, gen->get_data(), size * sizeof(int));
    cout << "5. STL stable sort (Merge sort): " << get_pretty_time(get_proc_time(std::stable_sort<int*>, data, data + size)) << '\n';


// SKIM:: aips2o sort

    auto start_time = std::chrono::high_resolution_clock::now();
    aips2o::sort(V.begin(), V.end());
    auto finish_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish_time - start_time);
    cout << "6. aips2o sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    ips4o::sort(V.begin(), V.end());
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "7. ips4o sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    ips4o::parallel::sort(V.begin(), V.end());
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "8. ips4o parallel sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';

    delete gen;
    delete[] data;
    return 0;
}
