#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

vector<int> ReverseVector(const vector<int>& source_vector) {
    vector<int> res;
    for (int i : source_vector) {
        res.insert(res.begin(), i);
    }

    return res;
}

int CountPops(const vector<int>& source_vector, int begin, int end) {
    int res = 0;

    for (int i = begin; i < end; ++i) {
        if (source_vector[i]) {
            ++res;
        }
    }

    return res;
}

void AppendRandom(vector<int>& v, int n) {
    for (int i = 0; i < n; ++i) {
        // получаем случайное число с помощью функции rand.
        // с помощью (rand() % 2) получим целое число в диапазоне 0..1.
        // в C++ имеются более современные генераторы случайных чисел,
        // но в данном уроке не будем их касаться
        v.push_back(rand() % 2);
    }
}

void Operate() {
    vector<int> random_bits;

    // операция << для целых чисел это сдвиг всех бит в двоичной
    // записи числа. Запишем с её помощью число 2 в степени 17 (131072)
    static const int N = 1 << 17;

    auto start_time = chrono::steady_clock::now();
    // заполним вектор случайными числами 0 и 1
    AppendRandom(random_bits, N);
    auto end_time = chrono::steady_clock::now();
    cerr << "Append random: "s << duration_cast<milliseconds>(end_time - start_time).count() << " ms"s << endl;

    start_time = chrono::steady_clock::now();
    // перевернём вектор задом наперёд
    vector<int> reversed_bits = ReverseVector(random_bits);
    end_time = chrono::steady_clock::now();
    cerr << "Reverse: "s << duration_cast<milliseconds>(end_time - start_time).count() << " ms"s << endl;

    
    start_time = chrono::steady_clock::now();
    // посчитаем процент единиц на начальных отрезках вектора
    for (int i = 1, step = 1; i <= N; i += step, step *= 2) {
        // чтобы вычислить проценты, мы умножаем на литерал 100. типа double;
        // целочисленное значение функции CountPops при этом автоматически
        // преобразуется к double, как и i
        double rate = CountPops(reversed_bits, 0, i) * 100. / i;
        cout << "After "s << i << " bits we found "s << rate << "% pops"s
            << endl;
    }
    end_time = chrono::steady_clock::now();
    cerr << "Counting: "s << duration_cast<milliseconds>(end_time - start_time).count() << " ms"s << endl;
}

int main() {
    Operate();
    return 0;
}
