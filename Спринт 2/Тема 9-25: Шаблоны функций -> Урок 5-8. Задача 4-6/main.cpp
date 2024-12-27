#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <typename Type>
ostream& operator<<(ostream& out, const vector<Type>& container);
template <typename Type>
ostream& operator<<(ostream& out, const set<Type>& container);

template <typename Type>
void Print(ostream& out, Type& container) {
    bool is_first = true;
    for (const auto& elem : container) {
        if (!is_first) {
            out << ", "s;
        }
        out << elem;
        is_first = false;
    }
}

template <typename Type>
ostream& operator<<(ostream& out, const vector<Type>& container) {
    Print(out, container);
    return out;
}

template <typename Type>
ostream& operator<<(ostream& out, const set<Type>& container) {
    Print(out, container);
    return out;
}

int main() {
    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl;

    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;

    const vector<vector<int>> ratings = {
        {3, 5, 6, 1},
        {1, 2},
        {5, 6, 6, 8, 7},
    };
    cout << ratings << endl;
}
