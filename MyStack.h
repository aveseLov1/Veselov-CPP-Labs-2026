#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>

// Структура узла связного списка
template <typename T>
struct ListNode {
    T data;
    ListNode<T>* next;
    ListNode(const T& value) : data(value), next(nullptr) {}
};

// Шаблонный класс стека
template <typename T>
class MyStack {
private:
    ListNode<T>* top; // указатель на вершину стека

public:
    // Конструктор по умолчанию
    MyStack() : top(nullptr) {}

    // Деструктор
    ~MyStack() {
        clear();
    }

    // Добавление элемента на вершину
    void push(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = top;
        top = newNode;
    }

    // Удаление элемента с вершины
    bool pop(T& value) {
        if (isEmpty()) {
            return false;
        }
        value = top->data;
        ListNode<T>* temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    // Получение значения верхнего элемента без удаления
    bool peek(T& value) const {
        if (isEmpty()) {
            return false;
        }
        value = top->data;
        return true;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return top == nullptr;
    }

    // Очистка стека
    void clear() {
        while (!isEmpty()) {
            T temp;
            pop(temp);
        }
    }

    // Вывод содержимого стека от вершины ко дну
    void print() const {
        ListNode<T>* current = top;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " * ";
            }
            current = current->next;
        }
    }
};

#endif
