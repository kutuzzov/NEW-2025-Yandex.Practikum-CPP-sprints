#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int count;
    cin >> count;
    vector<pair<int, string>> candidates;
    for (int i = 0; i < count; ++i) {
        string name;
        int age;
        cin >> name >> age;
        // сохраните в вектор пар
        candidates.push_back({ age, name });
    }

    // Выведите только имена в порядке убывания возраста
    // Имена людей одинакового возраста нужно вывести в порядке, обратном алфавитному
    sort(candidates.begin(), candidates.end());
    reverse(candidates.begin(), candidates.end());
    
    for (const auto& candidat : candidates) {
        cout << candidat.second << endl;
    }
}
