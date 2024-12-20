#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool StartsWithA(const string& str) {
    /* Возвращает true, если str начинается с символа 'A' или 'a' */
    if (!str.empty() && (str[0] == 'A' || str[0] == 'a')) {
        return true;
    }
    return false;
}

int CountStartsWithA(const vector<string>& xs) {
    // посчитайте число строк, начинающихся на букву A или a
    return count_if(xs.begin(), xs.end(), StartsWithA);
}

int main() {
    // не меняйте тело main
    cout << CountStartsWithA({"And"s, "another"s, "one"s, "gone"s, "another"s,
                              "one"s
                              "bites"s,
                              "the"s, "dust"s});

}
