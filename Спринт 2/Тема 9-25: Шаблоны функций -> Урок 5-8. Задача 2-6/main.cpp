#include <iostream>
#include <vector>

using namespace std;

template <typename Type>
ostream& operator<<(ostream& out, const vector<Type>& container) {
    bool is_first = true;
    for (const auto& elem : container) {
        if (is_first) {
            out << elem;
            is_first = false;
            continue;
        }
        out << ", "s << elem;
    }
    return out;
}

int main() {
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    return 0;
}
