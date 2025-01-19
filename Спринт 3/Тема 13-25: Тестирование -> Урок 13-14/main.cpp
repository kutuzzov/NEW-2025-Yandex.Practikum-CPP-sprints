// -------- Начало модульных тестов поисковой системы ----------

// Добавление документов.
// Добавленный документ должен находиться по поисковому запросу, который содержит слова из документа.
void TestAddingDocuments() {
    const int doc_id = 42;
    const string content = "cat in the city"s;
    const vector<int> ratings = { 1, 2, 3 };
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        const auto found_docs = server.FindTopDocuments("city"s);
        ASSERT_EQUAL(found_docs.size(), 1u);
        const Document& doc0 = found_docs[0];
        ASSERT_EQUAL(doc0.id, doc_id);
    }
}

// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
void TestExcludeStopWordsFromAddedDocumentContent() {
    const int doc_id = 42;
    const string content = "cat in the city"s;
    const vector<int> ratings = { 1, 2, 3 };
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        const auto found_docs = server.FindTopDocuments("in"s);
        ASSERT_EQUAL(found_docs.size(), 1u);
        const Document& doc0 = found_docs[0];
        ASSERT_EQUAL(doc0.id, doc_id);
    }

    {
        SearchServer server;
        server.SetStopWords("in the"s);
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        ASSERT_HINT(server.FindTopDocuments("in"s).empty(),
            "Stop words must be excluded from documents"s);
    }
}

// Поддержка минус-слов.
// Документы, содержащие минус-слова из поискового запроса, не должны включаться в результаты поиска.
void TestExcludeMinusWordsFromAddedDocumentContent() {
    const int doc_id = 42;
    const string content = "cat in the city"s;
    const vector<int> ratings = { 1, 2, 3 };
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        const auto found_docs = server.FindTopDocuments("cat in the -city"s);
        ASSERT_EQUAL(found_docs.size(), 0);
    }
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        ASSERT_HINT(server.FindTopDocuments("-city"s).empty(),
            "Minus words must be excluded from documents"s);
    }
}

ostream& operator<<(ostream& output, DocumentStatus document_status) {
    switch (document_status) {
        case DocumentStatus::ACTUAL:
            output << "ACTUAL"s;
            break;
        case DocumentStatus::IRRELEVANT:
            output << "IRRELEVANT"s;
            break;
        case DocumentStatus::BANNED:
            output << "BANNED"s;
            break;
        case DocumentStatus::REMOVED:
            output << "REMOVED"s;
            break;
        default:
            output << "<unknown>"s;
            break;
    }
    return output;
}

// Соответствие документов поисковому запросу.
// При этом должны быть возвращены все слова из поискового запроса, присутствующие в документе.
// Если есть соответствие хотя бы по одному минус-слову, должен возвращаться пустой список слов.
void TestMatchingDocuments() {
    SearchServer server;
    server.SetStopWords("and in on"s);
    server.AddDocument(100, "fluffy cat and black dog in a collar"s, DocumentStatus::BANNED, { 1, 2, 3 });

    {
        const auto [matched_words, status] = server.MatchDocument("dog and cat"s, 100);
        const vector<string> expected_result = { "cat"s, "dog"s };
        ASSERT_EQUAL(expected_result, matched_words);
        ASSERT_EQUAL(status, DocumentStatus::BANNED);
    }

    {
        const auto [matched_words, status] = server.MatchDocument("dog and -cat"s, 100);
        const vector<string> expected_result = {}; // пустой результат поскольку есть минус-слово
        ASSERT_EQUAL(expected_result, matched_words);
        ASSERT(matched_words.empty());
    }
}

// Сортировка найденных документов по релевантности.
// Возвращаемые при поиске документов результаты должны быть отсортированы в порядке убывания релевантности.
void TestSortingDocumentsByRelevance() {
    SearchServer search_server;
    search_server.SetStopWords("и в на"s);
    search_server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, { 5, -12, 2, 1 });

    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(0).id, 1);
    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(1).id, 2);
    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(2).id, 0);
}

// Вычисление рейтинга документов.
// Рейтинг добавленного документа равен среднему арифметическому оценок документа.
void TestRatingCalculate() {
    SearchServer search_server;
    search_server.SetStopWords("и в на"s);
    search_server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, { 5, -12, 2, 1 });

    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(0).rating, 5);
    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(1).rating, -1);
    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(2).rating, 2);
}

// Фильтрация результатов поиска с использованием предиката, задаваемого пользователем.
void TestFilterByUserPredicate() {
    SearchServer search_server;
    search_server.SetStopWords("и в на"s);
    search_server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, { 5, -12, 2, 1 });

    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s,
        [](int document_id, DocumentStatus status, int rating) { return document_id % 2 == 0; }).at(0).id % 2, 0);
    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s,
        [](int document_id, DocumentStatus status, int rating) { return document_id % 2 == 0; }).at(1).id % 2, 0);
}

// Поиск документов, имеющих заданный статус.
void TestFindDocumentsWithStatus() {
    const int doc_id1 = 42;
    const int doc_id2 = 43;
    const int doc_id3 = 44;
    const string content1 = "cat in the city"s;
    const string content2 = "cat in the town"s;
    const string content3 = "cat in the town or city"s;
    const vector<int> ratings = { 1, 2, 3 };
    SearchServer server;
    server.AddDocument(doc_id1, content1, DocumentStatus::ACTUAL, ratings);
    server.AddDocument(doc_id2, content2, DocumentStatus::IRRELEVANT, ratings);
    server.AddDocument(doc_id3, content3, DocumentStatus::IRRELEVANT, ratings);
    const auto found_docs = server.FindTopDocuments("in the cat"s, DocumentStatus::IRRELEVANT);

    {
        ASSERT_HINT(found_docs[0].id == doc_id2, "Wrong status");
        ASSERT_HINT(found_docs[1].id == doc_id3, "Wrong status");
        ASSERT_HINT(found_docs.size() == 2, "Wrong status request");
    }
}

// Корректное вычисление релевантности найденных документов.
void TestRelevanseCalculate() {
    SearchServer search_server;
    search_server.SetStopWords("и в на"s);
    search_server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, { 5, -12, 2, 1 });

    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(0).relevance, 0.65067242136109593);
    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(1).relevance, 0.27465307216702745);
    ASSERT_EQUAL(search_server.FindTopDocuments("пушистый ухоженный кот"s).at(2).relevance, 0.10136627702704110);
}

// Функция TestSearchServer является точкой входа для запуска тестов
void TestSearchServer() {
    RUN_TEST(TestAddingDocuments);
    RUN_TEST(TestExcludeStopWordsFromAddedDocumentContent);
    RUN_TEST(TestExcludeMinusWordsFromAddedDocumentContent);
    RUN_TEST(TestMatchingDocuments);
    RUN_TEST(TestSortingDocumentsByRelevance);
    RUN_TEST(TestRatingCalculate);
    RUN_TEST(TestFilterByUserPredicate);
    RUN_TEST(TestFindDocumentsWithStatus);
    RUN_TEST(TestRelevanseCalculate);
}

// --------- Окончание модульных тестов поисковой системы -----------
