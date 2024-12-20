#include <iostream>
#include <set>
#include <string>
#include <numeric>

using namespace std;

string SumStr(const string& query, const string& stop_word) {
    return query + " -"s + stop_word;
}

string AddStopWords(const string& query, const set<string>& stop_words) {
    // Напишите тело функции.
    return accumulate(stop_words.begin(), stop_words.end(), query, SumStr);
}

int main() {
    cout << AddStopWords({"some tasty oranges"}, {"of", "in"}) << endl;
}
