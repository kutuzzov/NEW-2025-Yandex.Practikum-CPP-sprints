#include <iostream>

using namespace std;

int Fibonacci(int num) {
    if (num == 0) {
        return 0;
    }
    if (num == 1) {
        return 1;
    }
    return Fibonacci(num - 1) + Fibonacci(num - 2);
}

int main() {
    cout << Fibonacci(6) << endl;
}
