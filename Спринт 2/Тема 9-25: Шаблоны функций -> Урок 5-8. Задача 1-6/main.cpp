#include <iostream>
#include <vector>

using namespace std;

template <typename Type>
ostream& operator<<(ostream& out, const vector<Type>& container) {
    for (const auto& elem : container) {
        out << elem << " "s;
    }
    return out;
}

int main() {
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    return 0;
}
