#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // считайте входные данные и сформируйте вывод программы
    // ...
    int n;
    cin >> n;
    vector<string> words;
    for (int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        words.push_back(str);
    }
    
    sort(words.begin(), words.end(), [](const string& left, const string& right) {
            return lexicographical_compare(
                left.begin(), left.end(), 
                right.begin(), right.end(), [](char cl, char cr) { return tolower(cl) < tolower(cr); } );
    });
    
    for (const auto& word : words) {
        cout << word << " ";
    }
    cout << endl;
}
