#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Term.h"
#include <iostream>

class Polynomial {
private:
    Term* terms;      // массив термов
    int size;         // фактический размер
    int capacity;     // выделенная память
    bool order;       // true - по возрастанию, false - по убыванию

    // Вспомогательные методы
    void resize();                    // увеличение capacity
    void simplify();                  // приведение подобных членов
    void sort();                      // сортировка по степени
    void removeZeros();               // удаление нулевых членов

public:
    // Конструкторы
    Polynomial();                     // полином 0
    Polynomial(double constant);      // константа
    Polynomial(const Term& term);     // один терм
    Polynomial(const Polynomial& other); // конструктор копирования

    // Деструктор
    ~Polynomial();

    // Методы
    void addTerm(const Term& term);   // добавление одночлена
    void removeTerm(int power);       // удаление по степени
    double evaluate(double x) const;  // вычисление значения

    // Операторы присваивания
    Polynomial& operator=(const Polynomial& other);

    // Арифметические операторы
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator+(const Term& term) const;
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator+=(const Term& term);

    Polynomial operator-(const Polynomial& other) const;
    Polynomial& operator-=(const Polynomial& other);

    Polynomial operator*(const Polynomial& other) const;
    Polynomial& operator*=(const Polynomial& other);

    // Операторы сравнения
    bool operator==(const Polynomial& other) const;

    // Ввод/вывод
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

    // Геттеры
    int getSize() const { return size; }
    bool getOrder() const { return order; }
    void setOrder(bool ord) { order = ord; sort(); }
};

#endif // POLYNOMIAL_H
