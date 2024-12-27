#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

template <typename Type>
ostream& operator<<(ostream& out, const vector<Type>& container);
template <typename Type>
ostream& operator<<(ostream& out, const set<Type>& container);
template <typename Key, typename Value>
ostream& operator<<(ostream& out, const map<Key, Value>& container);

template <typename First, typename Second>
ostream& operator<<(ostream& out, const pair<First, Second>& container) {
    out << "("s;
    out << container.first << ", " << container.second;
    out << ")"s;
    return out;
}

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
    out << "["s;
    Print(out, container);
    out << "]"s;
    return out;
}

template <typename Type>
ostream& operator<<(ostream& out, const set<Type>& container) {
    out << "{"s;
    Print(out, container);
    out << "}"s;
    return out;
}

template <typename Key, typename Value>
ostream& operator<<(ostream& out, const map<Key, Value>& container) {
    out << "<"s;
    Print(out, container);
    out << ">"s;
    return out;
}

int main() {
#ifdef _WIN32
    system("chcp 1251");
    std::cout << std::endl;
#endif

    const set<string> cats = { "Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s };
    cout << cats << endl;
    const vector<int> ages = { 10, 5, 2, 12 };
    cout << ages << endl;
    const map<string, int> cat_ages = {
        {"Мурка"s, 10},
        {"Белка"s, 5},
        {"Георгий"s, 2},
        {"Рюрик"s, 12}
    };
    cout << cat_ages << endl;
}
