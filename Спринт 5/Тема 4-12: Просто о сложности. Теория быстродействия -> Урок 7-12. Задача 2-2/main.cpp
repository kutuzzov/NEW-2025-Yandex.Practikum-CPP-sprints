#include <iostream>
#include <string>

using namespace std;

template <typename F>
string BruteForce(F check) {
    // верните строку str, для которой check(str) будет true
    string result;

    for (char ch1 = 'A'; ch1 != 'Z' + 1; ++ch1) {
        for (char ch2 = 'A'; ch2 != 'Z' + 1; ++ch2) {
            for (char ch3 = 'A'; ch3 != 'Z' + 1; ++ch3) {
                for (char ch4 = 'A'; ch4 != 'Z' + 1; ++ch4) {
                    for (char ch5 = 'A'; ch5 != 'Z' + 1; ++ch5) {
                        result = { ch1, ch2, ch3, ch4, ch5 };
                        if (check(result)) {
                            return result;
                        }
                    }
                }
            }
        }
    }
    return {};
}

int main() {
    string pass = "ARTUR"s;
    auto check = [pass](const string& s) {
        return s == pass;
        };
    cout << BruteForce(check) << endl;
}
