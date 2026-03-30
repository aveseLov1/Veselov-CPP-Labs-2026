#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    int numerator;    // числитель
    int denominator;  // знаменатель (всегда положительный)

    // Вспомогательные приватные методы
    void simplify();           // сокращение дроби
    int gcd(int a, int b) const;  // наибольший общий делитель
    void fromString(const char* str);  // преобразование из строки

public:
    // Конструкторы
    Fraction();                          // конструктор по умолчанию
    Fraction(int num, int den = 1);      // конструктор с параметрами
    Fraction(const char* str);           // конструктор преобразования из строки
    Fraction(const Fraction& other);     // конструктор копирования

    // Конструкторы для преобразования простых типов (Часть 2)
    Fraction(double value);              // из double

    // Деструктор
    ~Fraction() = default;

    // Оператор присваивания
    Fraction& operator=(const Fraction& other) = default;

    // Методы доступа
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    // Арифметические операторы
    Fraction operator+(const Fraction& other) const;
    Fraction& operator+=(const Fraction& other);
    Fraction operator-(const Fraction& other) const;
    Fraction& operator-=(const Fraction& other);

    // Дружественные операторы для работы с double и int
    friend Fraction operator+(double lhs, const Fraction& rhs);
    friend Fraction operator+(int lhs, const Fraction& rhs);
    friend Fraction operator+(const Fraction& lhs, double rhs);
    friend Fraction operator+(const Fraction& lhs, int rhs);

    friend Fraction& operator+=(Fraction& lhs, double rhs);
    friend Fraction& operator+=(Fraction& lhs, int rhs);

    // Дружественные функции для потокового ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
    friend std::istream& operator>>(std::istream& is, Fraction& frac);

    // Константа для точности преобразования double
    static const int kNumberDecimalPlaces = 4;
};

#endif // FRACTION_H
