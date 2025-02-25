#include "log_duration.h"

#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct Temperatures {
   float pozitive_counts = 0.0f;
   float pozitive_sums = 0.0f;
};

vector<float> ComputeAvgTemp(const vector<vector<float>>& measures) {
    // место для вашего решения
    if (measures.empty()) {
        return {};
    }

    const int measures_count = measures.at(0).size();
    vector<float> result(measures_count);
    vector<Temperatures> temps(measures_count);

    for (size_t i = 0; i < measures_count; ++i) {
        for (size_t j = 0; j < measures.size(); ++j) {
            temps[i].pozitive_counts += (measures[j][i] > 0 ? 1 : 0);
            temps[i].pozitive_sums += (measures[j][i] > 0 ? measures[j][i] : 0);
        }
        temps[i].pozitive_sums == 0 ? (result[i] = 0) : (result[i] = temps[i].pozitive_sums / temps[i].pozitive_counts);
    }

    return result;
}

vector<float> GetRandomVector(int size) {
    static mt19937 engine;
    uniform_real_distribution<float> d(-100, 100);

    vector<float> res(size);
    for (int i = 0; i < size; ++i) {
        res[i] = d(engine);
    }

    return res;
}

void Test() {
    // 4 дня по 3 измерения
    vector<vector<float>> v = {
        {0, -1, -1},
        {1, -2, -2},
        {2, 3, -3},
        {3, 4, -4}
    };

    // среднее для 0-го измерения (1+2+3) / 3 = 2 (не учитывам 0)
    // среднее для 1-го измерения (3+4) / 2 = 3.5 (не учитывам -1, -2)
    // среднее для 2-го не определено (все температуры отрицательны), поэтому должен быть 0
    const auto v2 = ComputeAvgTemp(v);

    assert(v2 == vector<float>({ 2, 3.5f, 0 }));
}

int main() {
    Test();

    vector<vector<float>> data;
    data.reserve(5000);

    for (int i = 0; i < 5000; ++i) {
        data.push_back(GetRandomVector(5000));
    }

    vector<float> avg;
    {
        LOG_DURATION("ComputeAvgTemp"s);
        avg = ComputeAvgTemp(data);
    }

    cout << "Total mean: "s << accumulate(avg.begin(), avg.end(), 0.f) / avg.size() << endl;
}
