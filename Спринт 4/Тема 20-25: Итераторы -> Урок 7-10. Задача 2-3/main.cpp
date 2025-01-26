#include <iostream>

using namespace std;

bool IsPowOfTwo(int num) {
    if (num == 0) {
        return false;
    }
    if (num == 1) {
        return true;
    }
    if (num % 2 == 0) {
        return IsPowOfTwo(num / 2);
    }
    return false;
}

int main() {
    int result = IsPowOfTwo(1024);
    cout << result << endl;
}
