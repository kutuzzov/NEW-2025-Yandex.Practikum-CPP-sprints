#include <iostream>
#include <string>

using namespace std;

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные буквы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, - это не палиндромы
bool IsPalindrome(const string& text) {
    // Напишите недостающий код
    if (text.empty()) {
        return false;
    }
    string str;
    for (const char& ch : text) {
        if (ch == ' ') {
            continue;
        }
        str += ch;
    }
    for (size_t i = 0; i < str.size() / 2; ++i) {
        if (str[i] == str[str.size() - i - 1]) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {
    string text;
    getline(cin, text);

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    } else {
        cout << "not a palindrome"s << endl;
    }
}
