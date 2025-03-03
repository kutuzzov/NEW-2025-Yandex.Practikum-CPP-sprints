#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// реализуйте эту функцию:
size_t GetFileSize(const string& file) {
    ifstream fin(file);
    if (!fin) {
        return string::npos;
    }
    fin.seekg(0, ios::end);
    return static_cast<size_t>(fin.tellg());
}

int main() {
    ofstream("test.txt") << "123456789"s;
    assert(GetFileSize("test.txt"s) == 9);

    ofstream test2("test2.txt"s);
    test2.seekp(1000);
    test2 << "abc"s;
    test2.flush();

    assert(GetFileSize("test2.txt"s) == 1003);
    assert(GetFileSize("missing file name"s) == string::npos);
}
