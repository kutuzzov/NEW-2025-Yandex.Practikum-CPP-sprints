#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    int range_length = static_cast<int>(range_end - range_begin);
    if (range_length < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    RandomIt middle = elements.begin() + range_length / 2;

    MergeSort(elements.begin(), middle);
    MergeSort(middle, elements.end());

    merge(elements.begin(), middle, middle, elements.end(), range_begin);
}

int main() {
#ifdef _WIN32
    system("chcp 1251");
    std::cout << std::endl;
#endif

    vector<int> test_vector(10);
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(test_vector.begin(), test_vector.end(), 1);

    // shuffle   -> https://ru.cppreference.com/w/cpp/algorithm/random_shuffle
    // Перемешивает элементы в случайном порядке
    random_device rd;
    mt19937 g(rd());
    shuffle(test_vector.begin(), test_vector.end(), g);

    // Выводим вектор до сортировки
    PrintRange(test_vector.begin(), test_vector.end());
    // Сортируем вектор с помощью сортировки слиянием
    MergeSort(test_vector.begin(), test_vector.end());
    // Выводим результат
    PrintRange(test_vector.begin(), test_vector.end());

    return 0;
}
