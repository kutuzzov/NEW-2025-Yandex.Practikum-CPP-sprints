#include <stack>
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

template <typename Type>
class Queue {
public:
    void Push(const Type& element) {
        // напишите реализацию
        stack1_.push(element);
    }
    void Pop() {
        // напишите реализацию
        MoveToTemp();
        stack2_.pop();
        MoveFromTemp();
    }
    Type& Front() {
        // напишите реализацию
        MoveToTemp();
        Type& front_element = stack2_.top();
        MoveFromTemp();
        return front_element;
    }
    uint64_t Size() const {
        // напишите реализацию
        return stack1_.size();
    }
    bool IsEmpty() const {
        // напишите реализацию
        return stack1_.empty();
    }

private:
    stack<Type> stack1_;
    stack<Type> stack2_;

    void MoveToTemp() {
        size_t counter = Size();
        for (size_t i = 0; i < counter; ++i) {
            stack2_.push(stack1_.top());
            stack1_.pop();
        }
    }
    void MoveFromTemp() {
        size_t counter = stack2_.size();
        for (size_t i = 0; i < counter; ++i) {
            Push(stack2_.top());
            stack2_.pop();
        }
    }
};

template <typename It>
void PrintRange(It begin, It end) {
    for (auto it = begin; it != end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

int main() {
#ifdef _WIN32
    system("chcp 1251");
    std::cout << std::endl;
#endif

    Queue<int> queue;
    vector<int> values(5);
    // заполняем вектор для тестирования очереди
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);
    PrintRange(values.begin(), values.end());
    cout << "Заполняем очередь"s << endl;
    // заполняем очередь и выводим элемент в начале очереди
    for (int i = 0; i < 5; ++i) {
        queue.Push(values[i]);
        cout << "Вставленный элемент "s << values[i] << endl;
        cout << "Первый элемент очереди "s << queue.Front() << endl;
    }
    cout << "Вынимаем элементы из очереди"s << endl;
    // выводим элемент в начале очереди и вытаскиваем элементы по одному
    while (!queue.IsEmpty()) {
        // сначала будем проверять начальный элемент, а потом вытаскивать,
        // так как операция Front на пустой очереди не определена
        cout << "Будем вынимать элемент "s << queue.Front() << endl;
        queue.Pop();
    }
    return 0;
}
