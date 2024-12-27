#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <typename Type>
ostream& operator<<(ostream& out, const vector<Type>& container) {
    bool is_first = true;
    for (const auto& elem : container) {
        if (!is_first) {
            out << ", "s;
        }
        out << elem;
        is_first = false;
    }
    return out;
}

template <typename Type>
ostream& operator<<(ostream& out, const set<Type>& container) {
    bool is_first = true;
    for (const auto& elem : container) {
        if (!is_first) {
            out << ", "s;
        }
        out << elem;
        is_first = false;
    }
    return out;
}

int main() {
    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl;
    return 0;
}
