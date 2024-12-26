#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
template <typename Term>
map<Term, int> ComputeTermFreqs(const vector<Term>& terms) {
    map<Term, int> term_freqs;
    for (const Term& term : terms) {
        ++term_freqs[term];
    }
    return term_freqs;
}
pair<string, int> FindMaxFreqAnimal(const vector<pair<string, int>>& animals) {
    // верните животного с максимальной частотой
    pair<string, int> result;
    int max_freq = 0;
    for (const auto& [name, freq] : ComputeTermFreqs(animals)) {
        if (freq > max_freq) {
            max_freq = freq;
            result = name;
        }
    }
    return result;
}

int main() {
    const vector<pair<string, int>> animals = {
        {"Murka"s, 5},  // 5-летняя Мурка
        {"Belka"s, 6},  // 6-летняя Белка
        {"Murka"s, 7},  // 7-летняя Мурка не та же, что 5-летняя!
        {"Murka"s, 5},  // Снова 5-летняя Мурка
        {"Belka"s, 6},  // Снова 6-летняя Белка
    };
    const pair<string, int> max_freq_animal = FindMaxFreqAnimal(animals);
    cout << max_freq_animal.first << " "s << max_freq_animal.second << endl;
}
