#include <iostream>
#include <vector>
#include <cstdint>
#include <random>
#include <algorithm>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Stack {
public:
    void Push(const Type& element) {
        // напишите реализацию
        elements_.push_back(element);
    }
    void Pop() {
        // напишите реализацию
        elements_.pop_back();
    }
    const Type& Peek() const {
        // напишите реализацию
        return elements_.back();
    }
    Type& Peek() {
        // напишите реализацию
        return elements_.back();
    }
    void Print() const {
        // напишите реализацию
        PrintRange(elements_.begin(), elements_.end());
    }
    uint64_t Size() const {
        // напишите реализацию
        return elements_.size();
    }
    bool IsEmpty() const {
        // напишите реализацию
        return elements_.empty();
    }
    const Stack& operator[](size_t index) const {
        return elements_[index];
    }
    Type& operator[](size_t index) {
        return elements_[index];
    }
 
private:
    vector<Type> elements_;
};

template <typename Type>
bool operator<(const Type& lhs, const Type& rhs) {
    return std::lexicographical_compare(lhs,rhs);
}

template <typename Type>
class SortedSack {
public:
    void Push(const Type& element) {
    // напишите реализацию метода
        if (elements_.IsEmpty()) {
            elements_.Push(element);
        } else {
            elements_.Push(element);
            for (size_t i = elements_.Size() - 1; i != 0; --i) {
                if (elements_[i - 1] < elements_[i]) {
                    swap(elements_[i - 1], elements_[i]);
                }
            }
        }
    }
    void Pop() {
    // напишите реализацию метода
        elements_.Pop();
    }
    const Type& Peek() const {
        return elements_.Peek();
    }
    Type& Peek() {
        return elements_.Peek();
    }
    void Print() const {
        elements_.Print();
    }
    uint64_t Size() const {
        return elements_.Size();
    }
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }
private:
    Stack<Type> elements_;
};

int main() {
    SortedSack<int> sack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего класса
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);

    // заполняем класс и проверяем, что сортировка сохраняется после каждой вставки
    for (int i = 0; i < 5; ++i) {
        cout << "Вставляемый элемент = "s << values[i] << endl;
        sack.Push(values[i]);
        sack.Print();
    }
}
