#include <iostream>

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

using namespace std;

template <typename T>
void sort_and_print(std::vector<T> &V, int algorithm)
{
    switch (algorithm)
    {
    case 1:
        std::sort(V.begin(), V.end() - 1);
        break;
    case 2:
        std::stable_sort(V.begin(), V.end() - 1);
        break;
    case 3:
        parallel_intro_sort(V.begin(), V.end() - 1);
        break;
    case 4:
        aips2o::sort(V.begin(), V.end());
        break;
    }
}

int main(int argc, char *argv[])
{

    string type = argv[1];
    string filename = argv[2];
    int algorithm = atoi(argv[3]);

    std::vector<uint32_t> I_32;
    std::vector<uint64_t> I_64;
    skim_generator<uint32_t> *gen_i32 = new skim_generator<uint32_t>(I_32);
    skim_generator<uint64_t> *gen_i64 = new skim_generator<uint64_t>(I_64);

    if (type == "uint_32")
    {
        gen_i32->read_data_32(filename);
        gen_i32->apply_changes(I_32);
        sort_and_print(I_32, algorithm);
    } else {
        gen_i64->read_data_32(filename);
        gen_i64->apply_changes(I_64);
        sort_and_print(I_64, algorithm);
    }
    return 0;
}