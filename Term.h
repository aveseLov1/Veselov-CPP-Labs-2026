#ifndef TERM_H
#define TERM_H

#include <iostream>

class Term {
private:
    double coef;  // коэффициент
    int power;    // степень

public:
    // Конструкторы
    Term();                                    // 0x^0
    Term(double coef);                         // coef * x^0
    Term(double coef, int power);              // coef * x^power
    // Term(const Term& other);                   // конструктор копирования

    // Деструктор
    ~Term() = default;

    // Геттеры
    double getCoef() const { return coef; }
    int getPower() const { return power; }

    // Сеттеры
    void setCoef(double c) { coef = c; }
    void setPower(int p) { power = p; }

    // Операторы
    Term operator+(const Term& other) const;   // сложение (только для одинаковых степеней)
    // Term& operator=(const Term& other);        // присваивание
    bool operator==(const Term& other) const;  // сравнение (по степени)

    // Ввод/вывод
    friend std::istream& operator>>(std::istream& is, Term& term);
    friend std::ostream& operator<<(std::ostream& os, const Term& term);

    // Дружественный класс Polynomial
    friend class Polynomial;
};

#endif // TERM_H
