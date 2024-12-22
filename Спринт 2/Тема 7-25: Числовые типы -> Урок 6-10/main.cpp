#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Document {
    int id;
    int rating;
};

void PrintDocuments(vector<Document> documents, size_t skip_start, size_t skip_finish) {
    // отсортировать документы и вывести не все
    if (documents.empty() || (documents.size() < (skip_start + skip_finish)) ) {
        return;
    }
    sort(documents.begin(), documents.end(), [](const Document& lhs, const Document& rhs) {
        return lhs.rating > rhs.rating;
    });
    documents.erase(documents.begin(), documents.begin() + skip_start);
    documents.erase(documents.end() - skip_finish, documents.end());
    
    for (const auto& doc : documents) {
        cout << "{ "s
             << "id = "s << doc.id << ", "
             << "rating = "s << doc.rating
             << " }"s << endl;
    }
}

int main() {
    PrintDocuments({{100, 5}, {101, 7}, {102, -4}, {103, 9}, {104, 1}}, 1, 2);
}
