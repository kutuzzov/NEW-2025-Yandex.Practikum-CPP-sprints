#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    // Выведите первый язык, начинающийся на C, используя алгоритм find_if
    auto it = find_if(langs.begin(), langs.end(), [](string& word) {
                    return word[0] == 'C';
                });
    cout << *it << endl;
}
