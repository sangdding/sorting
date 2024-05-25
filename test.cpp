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
    cout << get_pretty_time((finish_time - start_time).count()) << '\n';
}

template <typename T>
void merge(std::vector<T> V)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::stable_sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << get_pretty_time((finish_time - start_time).count()) << '\n';
}

template <typename T>
void parallel(std::vector<T> V)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    parallel_intro_sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << get_pretty_time((finish_time - start_time).count()) << '\n';
}

template <typename T>
void aips(std::vector<T> V)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    aips2o::sort(V.begin(), V.end() - 1);
    auto finish_time = std::chrono::high_resolution_clock::now();
    cout << get_pretty_time((finish_time - start_time).count()) << '\n';
}

int main(int argc, char *argv[])
{

    int size = atoi(argv[1]);
    int num = atoi(argv[2]);

    std::vector<double> I(size);
    skim_generator<double> *gen_i = new skim_generator<double>(I);
    switch (num)
    {
    case 1:
        cout << "uniform" << endl;
        gen_i->uniform_distribution();
        gen_i->apply_changes(I);
        break;
    case 2:
        cout << "normal" << endl;
        gen_i->normal_distribution();
        gen_i->apply_changes(I);
        break;
    case 3:
        cout << "log_normal" << endl;
        gen_i->log_normal_distribution();
        gen_i->apply_changes(I);
        break;
    case 4:
        cout << "mix_gauss" << endl;
        gen_i->mix_gauss();
        gen_i->apply_changes(I);
        break;
    case 5:
        cout << "exponential" << endl;
        gen_i->exponential_distribution();
        gen_i->apply_changes(I);
        break;
    case 6:
        cout << "chi_squard" << endl;
        gen_i->chi_squared_distribution();
        gen_i->apply_changes(I);
        break;
    case 7:
        cout << "root_dups" << endl;
        gen_i->root_dups();
        gen_i->apply_changes(I);
        break;
    case 8:
        cout << "two_dups" << endl;
        gen_i->two_dups();
        gen_i->apply_changes(I);
        break;
    }

    stl(I);
    merge(I);
    parallel(I);
    aips(I);
    return 0;
}