#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED
};

struct Document {
    int id;
    double relevance;
    int rating;
};

struct Query {
    set<string> plus_words;
    set<string> minus_words;
};

class SearchServer {
public:
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    void AddDocument(int document_id, const string& document, DocumentStatus status, const vector<int>& ratings) {
        const vector<string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size();
        for (const string& word : words) {
            word_to_document_freqs_[word][document_id] += inv_word_count;
        }
        const DocumentData data = { ComputeAverageRating(ratings), status };
        document_ratings_.emplace(document_id, data);
    }

    vector<Document> FindTopDocuments(const string& raw_query, DocumentStatus status) const {
        const Query query_words = ParseQuery(raw_query);
        vector<Document> raw_matched_documents = FindAllDocuments(query_words);
        vector<Document> matched_documents;

        for (const auto& doc : raw_matched_documents) {
            DocumentStatus raw_status = document_ratings_.at(doc.id).status;
            if (raw_status == status) {
                matched_documents.push_back(doc);
            }
        }
        sort(matched_documents.begin(), matched_documents.end(),
            [](const Document& lhs, const Document& rhs) {
                return lhs.relevance > rhs.relevance;
            });
        
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

private:
    struct DocumentData {
        int rating;
        DocumentStatus status;
    };

    map<string, map<int, double>> word_to_document_freqs_;
    set<string> stop_words_;
    map<int, DocumentData> document_ratings_;

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    Query ParseQuery(const string& text) const {
        Query query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            if (word[0] == '-') {
                const string minus_word = word.substr(1);
                if (stop_words_.count(minus_word) == 0) {
                    query_words.minus_words.insert(minus_word);
                }
            }
            else {
                query_words.plus_words.insert(word);
            }
        }
        return query_words;
    }

    double ComputeWordInverseDocumentFreq(const string& word) const {
        return log(document_ratings_.size() * 1.0 / word_to_document_freqs_.at(word).size());
    }

    vector<Document> FindAllDocuments(const Query& query_words) const {
        vector<Document> matched_documents;
        map<int, double> document_to_relevance;
        for (const auto& word : query_words.plus_words) {
            if (word_to_document_freqs_.count(word)) {
                double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
                for (const auto& [document_id, term_freq] : word_to_document_freqs_.at(word)) {
                    document_to_relevance[document_id] += term_freq * inverse_document_freq;
                }
            }
        }
        for (const auto& word : query_words.minus_words) {
            if (word_to_document_freqs_.count(word)) {
                for (const auto& [document_id, term_freq] : word_to_document_freqs_.at(word)) {
                    document_to_relevance.erase(document_id);
                }
            }
        }
        for (const auto& [id, relevance] : document_to_relevance) {
            matched_documents.push_back({ id, relevance, document_ratings_.at(id).rating });
        }
        return matched_documents;
    }

    static int ComputeAverageRating(const vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        }
        int total_rating = 0;
        for (const int rating : ratings) {
            total_rating += rating;
        }

        return total_rating / static_cast<int>(ratings.size());
    }
};

/*
SearchServer CreateSearchServer() {
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());

    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        auto document = ReadLine();
        
        int ratings_size;
        cin >> ratings_size;
        vector<int> ratings(ratings_size, 0);
        for (int& rating : ratings) {
            cin >> rating;
        }
        
        search_server.AddDocument(document_id, document, ratings);
        ReadLine();
    }

    return search_server;
}
*/

void PrintDocument(const Document& document) {
    cout << "{ "s
        << "document_id = "s << document.id << ", "s
        << "relevance = "s << document.relevance << ", "s
        << "rating = "s << document.rating
        << " }"s << endl;
}

int main() {
    SearchServer search_server;
    search_server.SetStopWords("и в на"s);
    search_server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, { 5, -12, 2, 1 });
    search_server.AddDocument(3, "ухоженный скворец евгений"s, DocumentStatus::BANNED, { 9 });
    cout << "ACTUAL:"s << endl;
    for (const Document& document : search_server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::ACTUAL)) {
        PrintDocument(document);
    }
    cout << "BANNED:"s << endl;
    for (const Document& document : search_server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::BANNED)) {
        PrintDocument(document);
    }
    return 0;
}
