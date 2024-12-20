#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

double Average(const vector<int>& xs) {
    // Напишите реализацию функции.
    if (!xs.empty()) {
        return (accumulate(xs.begin(), xs.end(), 0.0)) / xs.size();
    }
    return 0;
}

int main() {
    cout << Average({}) << endl;        // Результат: 0.
    cout << Average({2, 3}) << endl;    // Результат: 2.5.
    cout << Average({7, 2, 6}) << endl; // Результат: 5.
}
