#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Container, typename Elem>
void FindAndPrint(const Container& container, const Elem& elem) {
    auto pos = find(begin(container), end(container), elem);
    PrintRange(begin(container), pos);
    PrintRange(pos, end(container));
}

int main() {
    set<int> test = {1, 1, 1, 2, 3, 4, 5, 5};
    cout << "Test1"s << endl;
    FindAndPrint(test, 3);
    cout << "Test2"s << endl;
    FindAndPrint(test, 0); // элемента 0 нет в контейнере
    cout << "End of tests"s << endl;
}
