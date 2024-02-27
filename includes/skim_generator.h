#ifndef SKIM_DATA_GENERATOR_H
#define SKIM_DATA_GENERATOR_H

#include <random>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

template<typename T>
class skim_generator
{
private:
    /* data */
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::vector<T> data;
    size_t size;
public:
    explicit skim_generator(std::vector<T> &V) {
        data = V;
        size = data.size();
    }

    void uniform_distribution() {
        std::uniform_int_distribution<> uniform_dist(0, size - 1);
        for (T& num : data) {
            num = uniform_dist(gen);
        }
    };

    void normal_distribution() {
        std::normal_distribution<> normal_dist(0.0, 1.0);
        for (T &num : data)
        {
            num = normal_dist(gen);
        }
    };

    void log_normal_distribution() {
        std::lognormal_distribution<> lognormal_dist(0.0, 0.5);
        for (T &num : data)
        {
            num = lognormal_dist(gen);
        }
    };

    void mix_gauss() {
        std::normal_distribution<> dist1(-2.0, 0.5);
        std::normal_distribution<> dist2(1.0, 1.0);
        std::normal_distribution<> dist3(4.0, 2.0);
        std::normal_distribution<> dist4(8.0, 3.0);
        std::normal_distribution<> dist5(12.0, 4.0);
        for (T &num : data)
        {
            num = dist1(gen) + dist2(gen) + dist3(gen) + dist4(gen) + dist5(gen);
        }
    };

    void exponential_distribution() {
        std::exponential_distribution<> exponential_dist(2.0);
        for (T &num : data)
        {
            num = exponential_dist(gen);
        }
    };

    void chi_squared_distribution() {
        std::chi_squared_distribution<> chi_squared_dist(4.0);
        for (T &num : data)
        {
            num = chi_squared_dist(gen);
        }
    };

    void root_dups() {
        for (int i = 0; i < size; ++i)
        {
            data[i] = i % static_cast<int>(sqrt(size));
        }
    };

    void two_dups() {
        for (int i = 0; i < size; ++i)
        {
            data[i] = (i * i + size / 2) % size;
        }
    };

    void apply_changes(std::vector<T>& org) {
        org = data;
    }
};

#endif //SKIM_DATA_GENERATOR_H