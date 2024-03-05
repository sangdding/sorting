#include <iostream>

//sort_algorithms 헤더에 모든 정렬 알고리즘의 전방 선언이 모여있습니다.
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

using namespace std;

template<typename T>
void sort_and_print(std::vector<T> &V) {
    
    cout << "sort start" << endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    std::sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << "1. STL sort (Intro sort): " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    std::stable_sort(V.begin(), V.end() - 1);
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "2. STL stable sort (Merge sort): " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    parallel_intro_sort(V.begin(), V.end() - 1);
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "3. parallel intro sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    aips2o::sort(V.begin(), V.end());
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "4. aips2o sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    aips2o::parallel::sort(V.begin(), V.end());
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "5. aips2o parallel sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    ips4o::sort(V.begin(), V.end());
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "6. ips4o sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';

    start_time = std::chrono::high_resolution_clock::now();
    ips4o::parallel::sort(V.begin(), V.end());
    finish_time = std::chrono::high_resolution_clock::now();
    cout << "7. ips4o parallel sort: " << get_pretty_time((finish_time - start_time).count()) << '\n';
}

int main() {

    size_t size;
    string filename;
    int method;

    cin >> size >> method >> filename;
    cout << "Data Size : " << size << endl;
    cout << "Generation Method" << endl;
    cout << "Method : ";
    cout << filename << endl;
    std::vector<int> I(size);
    std::vector<double> D(size);
    std::vector<uint32_t> I_32;
    std::vector<uint64_t> I_64;
    skim_generator<int> *gen_i = new skim_generator<int>(I);
    skim_generator<double> *gen_d = new skim_generator<double>(D);
    skim_generator<uint32_t> *gen_i32 = new skim_generator<uint32_t>(I_32);
    skim_generator<uint64_t> *gen_i64 = new skim_generator<uint64_t>(I_64);
    switch (method)
    {
    case 1:
        cout << "uniform" << endl;
        gen_i->uniform_distribution();
        gen_i->apply_changes(I);
        sort_and_print(I);
        break;
        case 2:
        cout << "normal" << endl;        
        gen_d->normal_distribution();
        gen_d->apply_changes(D);
        sort_and_print(D);
        break;
        case 3:
        cout << "log_normal" << endl;
        gen_d->log_normal_distribution();
        gen_d->apply_changes(D);
        sort_and_print(D);
        break;
        case 4:
        cout << "mix_gauss" << endl;
        gen_d->mix_gauss();
        gen_d->apply_changes(D);
        sort_and_print(D);
        break;
        case 5:
        cout << "exponential" << endl;
        gen_d->exponential_distribution();
        gen_d->apply_changes(D);
        sort_and_print(D);
        break;
        case 6:
        cout << "chi_squard" << endl;
        gen_d->chi_squared_distribution();
        gen_d->apply_changes(D);
        sort_and_print(D);
        break;
        case 7:
        cout << "root_dups" << endl;
        gen_i->root_dups();
        gen_i->apply_changes(I);
        sort_and_print(I);
        break;
        case 8:
        cout << "two_dups" << endl;
        gen_i->two_dups();
        gen_i->apply_changes(I);
        sort_and_print(I);
        break;
        case 9:
        gen_i32->read_data_32(filename);
        gen_i32->apply_changes(I_32);
        sort_and_print(I_32);
        break;
        case 10:
        gen_i64->read_data_32(filename);
        gen_i64->apply_changes(I_64);
        sort_and_print(I_64);
        break;
    }
    return 0;
}