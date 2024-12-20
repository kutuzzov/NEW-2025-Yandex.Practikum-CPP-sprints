#include <algorithm>
#include <chrono>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int SAMPLE_COUNT = 5;

/**
 * Определяет, какие имена из вектора candidates содержатся внутри множества storage.
 * Возвращает вектор, где каждому элементу из candidates соответствует одно из чисел:
 *  0 - элемент из candidates отсутствует в storage
 *  1 - элемент из candidates присутствует внутри storage
 */
vector<int> CountNamesLong(const set<string>& storage, const vector<string>& candidates) {
    // Эта функция работает правильно, но недостаточно быстро.
    // Не удаляйте и не изменяйте код этой функции.
    
    vector<int> output;
    for (auto& name : candidates) {
        // Подсчитываем количество вхождений name в storage стандартным алгоритмом count
        output.push_back(count(storage.begin(), storage.end(), name));
    }
    return output;
}

// Напишите тело функции CountNames, которая выдаёт результат, аналогичный CountNamesLong,
// но выполняется быстрее за счёт использования встроенного алгоритма count вместо общего
vector<int> CountNames(const set<string>& storage, const vector<string>& candidates) {
    vector<int> output;
    // Напишите реализацию здесь
    for (auto& name : candidates) {
        // Подсчитываем количество вхождений name в storage встроенным алгоритмом count
        output.push_back(storage.count(name));
    }
    return output;
}

int main() {
    set<string> s;
    vector<string> v;
    string stra;
    string strb;

    for (int j = 0; j < 10000; ++j) {
        s.insert(stra);
        stra += "a"s;
        if (j % 2 == 0) {
            v.push_back(strb);
            strb += "b"s;
        } else {
            v.push_back(stra);
        }
    }

    cout << "Testing slow version" << endl;
    // Замеряем время работы несколько раз, так как оно может отличаться от запуска к запуску
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        // Засекаем время запуска функции
        auto begin = chrono::steady_clock::now();
        CountNamesLong(s, v);
        // Засекаем время завершения функции
        auto end = chrono::steady_clock::now();

        // Выводим время работы в микросекундах
        cout << "Time difference Long = "s
             << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]"s << endl;
    }

    // Вы можете замерить время работы функции CountNames и сравнить её с временем
    // работы CountNamesLong
    cout << "Testing fast version" << endl;
    // Замеряем время работы несколько раз, так как оно может отличаться от запуска к запуску
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        // Засекаем время запуска функции
        auto begin = chrono::steady_clock::now();
        CountNames(s, v);
        // Засекаем время завершения функции
        auto end = chrono::steady_clock::now();

        // Выводим время работы в микросекундах
        cout << "Time difference Fast = "s
             << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]"s << endl;
    }
}
