#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Container>
void EraseAndPrint(Container& container, int pos, int start, int finish) {
    container.erase(container.begin() + pos);
    PrintRange(container.begin(), container.end());
    container.erase(container.begin() + start, container.begin() + finish);
    PrintRange(container.begin(), container.end());
}

int main() {
    vector<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    EraseAndPrint(langs, 0, 0, 2);
    return 0;
}
