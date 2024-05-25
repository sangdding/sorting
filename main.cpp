#include <iostream>
#include "aips2o.hpp"
#include "intro_sort.hpp"
#include "sort_algorithms.hpp"
#include "data_generator.h"
#include "skim_generator.h"
#include "utility.h"
#include "ips4o.hpp"
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

#define CORE 48

using namespace std;

template <typename T>
void sort_and_print(std::vector<T> &V, int algorithm)
{
    switch (algorithm)
    {
    case 1:
        std::sort(V.begin(), V.end());
        break;
    case 2:
        std::stable_sort(V.begin(), V.end());
        break;
    case 3:
        parallel_intro_sort(V.begin(), V.end());
        break;
    case 4:
        aips2o::sort(V.begin(), V.end());
        break;
    }
}

int main()
{
    const int experiment_repeats = 1000;
    const int num_distributions = 8;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_size(1000, 10000000);

    for (int type = 0; type < 2; ++type) // 0 for int, 1 for double
    {
        for (int exp = 0; exp < experiment_repeats; ++exp)
        {
            int data_size = dist_size(gen);

            for (int dist = 1; dist <= num_distributions; ++dist)
            {
                if (type == 0) // int
                {
                    std::vector<int> data(data_size);
                    skim_generator<int> *gen_i = new skim_generator<int>(data);

                    switch (dist)
                    {
                    case 1:
                        gen_i->uniform_distribution();
                        break;
                    case 2:
                        gen_i->normal_distribution();
                        break;
                    case 3:
                        gen_i->log_normal_distribution();
                        break;
                    case 4:
                        gen_i->mix_gauss();
                        break;
                    case 5:
                        gen_i->exponential_distribution();
                        break;
                    case 6:
                        gen_i->chi_squared_distribution();
                        break;
                    case 7:
                        gen_i->root_dups();
                        break;
                    case 8:
                        gen_i->two_dups();
                        break;
                    }
                    gen_i->apply_changes(data);

                    for (int algo = 1; algo <= 4; ++algo)
                    {
                        auto start = chrono::high_resolution_clock::now();
                        sort_and_print(data, algo);
                        auto end = chrono::high_resolution_clock::now();
                        chrono::duration<double, milli> elapsed = end - start;
                        cout << data_size << "," << CORE << "," << (type == 0 ? 1 : 2) << "," << dist << "," << algo << "," << elapsed.count() << endl;
                    }
                }
                else // double
                {
                    std::vector<double> data(data_size);
                    skim_generator<double> *gen_d = new skim_generator<double>(data);

                    switch (dist)
                    {
                    case 1:
                        gen_d->uniform_distribution();
                        break;
                    case 2:
                        gen_d->normal_distribution();
                        break;
                    case 3:
                        gen_d->log_normal_distribution();
                        break;
                    case 4:
                        gen_d->mix_gauss();
                        break;
                    case 5:
                        gen_d->exponential_distribution();
                        break;
                    case 6:
                        gen_d->chi_squared_distribution();
                        break;
                    case 7:
                        gen_d->root_dups();
                        break;
                    case 8:
                        gen_d->two_dups();
                        break;
                    }
                    gen_d->apply_changes(data);

                    for (int algo = 1; algo <= 4; ++algo)
                    {
                        auto start = chrono::high_resolution_clock::now();
                        sort_and_print(data, algo);
                        auto end = chrono::high_resolution_clock::now();
                        chrono::duration<double, milli> elapsed = end - start;
                        cout << data_size << "," << CORE << "," << (type == 0 ? 1 : 2) << "," << dist << "," << algo << "," << elapsed.count() << endl;
                    }
                }
            }
        }
    }
    return 0;
}
