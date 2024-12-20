#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

int main() {
    const int queryCount = ReadLineWithNumber();

    vector<string> queries(queryCount);
    for (string& query : queries) {
        query = ReadLine();
    }
    const string buzzword = ReadLine();

    cout << count_if(queries.begin(), queries.end(), [buzzword](const string& query) {
        // Реализуйте эту лямбда-функцию
        // Верните true, если query содержит слово buzzword
        vector<string> words;
        string word;
        for (char ch : query) {
            if (ch == ' ') {
                words.push_back(word);
                word.clear();
                continue;
            }
            word += ch;
        }
        words.push_back(word);
        
 //       for(auto w : words) { cout << w << " "; }
        
        if (count(words.begin(), words.end(), buzzword) != 0) {
            return true;
        }
        return false;
        
    });
    cout << endl;
}
