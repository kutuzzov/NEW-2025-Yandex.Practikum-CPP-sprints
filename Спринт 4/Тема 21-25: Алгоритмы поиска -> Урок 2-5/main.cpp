#include <iostream>
#include <algorithm>

using namespace std;

void PrintSpacesPositions(string& str) {
    // напишите реализацию
    for (auto it = find(str.begin(), str.end(), ' '); it != str.end(); it = find(it + 1, str.end(), ' ')) {
        cout << distance(str.begin(), it) << endl;
    }
}

int main() {
    string str = "He said: one and one and one is three"s;
    PrintSpacesPositions(str);
    return 0;
}
