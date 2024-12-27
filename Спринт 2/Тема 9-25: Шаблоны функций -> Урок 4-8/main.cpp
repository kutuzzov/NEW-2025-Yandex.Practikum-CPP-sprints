#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template <typename Document, typename Term>
vector<double> ComputeTfIdfs(const Document& documents, const Term& term) {
    vector<double> tf_idfs;

    int document_freq = 0;
    for (const auto& document : documents) {
        const auto freq = count(document.begin(), document.end(), term);
        if (freq > 0) {
            ++document_freq;
        }
        tf_idfs.push_back(static_cast<double>(freq) / static_cast<double>(document.size()));
    }

    const double idf = log(static_cast<double>(documents.size()) / document_freq);
    for (double& tf_idf : tf_idfs) {
        tf_idf *= idf;
    }

    return tf_idfs;
}

int main() {
    const vector<vector<string>> documents = {
        {"белый"s, "кот"s, "и"s, "модный"s, "ошейник"s},
        {"пушистый"s, "кот"s, "пушистый"s, "хвост"s},
        {"ухоженный"s, "пёс"s, "выразительные"s, "глаза"s},
    };
    const auto tf_idfs = ComputeTfIdfs(documents, "кот"s);
    for (const double tf_idf : tf_idfs) {
        cout << tf_idf << " "s;
    }
    cout << endl;
}
