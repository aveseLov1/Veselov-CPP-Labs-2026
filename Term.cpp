#include "Term.h"
#include <cctype>
#include <cstdlib>
#include <cmath>

// Конструктор по умолчанию
Term::Term() : coef(0.0), power(0) {}

// Конструктор с одним параметром (коэффициент)
Term::Term(double coef) : coef(coef), power(0) {}

// Конструктор с двумя параметрами
Term::Term(double coef, int power) : coef(coef), power(power) {}

// Конструктор копирования
Term::Term(const Term& other) : coef(other.coef), power(other.power) {}

// Оператор сложения (только для одинаковых степеней)
Term Term::operator+(const Term& other) const {
    if (power != other.power) {
        return *this;
    }
    return Term(coef + other.coef, power);
}

// Оператор присваивания
Term& Term::operator=(const Term& other) {
    if (this != &other) {
        coef = other.coef;
        power = other.power;
    }
    return *this;
}

// Оператор сравнения (по степени)
bool Term::operator==(const Term& other) const {
    return power == other.power;
}

// Парсинг одного терма из C-строки
bool parseTerm(const char* str, double& coef, int& power) {
    if (!str || str[0] == '\0') return false;

    int i = 0;
    int sign = 1;

    // Обработка знака
    if (str[i] == '+') {
        i++;
    } else if (str[i] == '-') {
        sign = -1;
        i++;
    }

    // Парсинг коэффициента
    double tempCoef = 0.0;
    bool hasDecimal = false;
    double decimalDiv = 1.0;

    if (str[i] && (isdigit(str[i]) || str[i] == '.')) {
        while (str[i]) {
            if (isdigit(str[i])) {
                if (!hasDecimal) {
                    tempCoef = tempCoef * 10 + (str[i] - '0');
                } else {
                    tempCoef = tempCoef + (str[i] - '0') / decimalDiv;
                    decimalDiv *= 10;
                }
                i++;
            } else if (str[i] == '.' && !hasDecimal) {
                hasDecimal = true;
                decimalDiv = 10.0;
                i++;
            } else {
                break;
            }
        }
        coef = sign * tempCoef;
    } else {
        coef = sign * 1.0;
    }

    // Поиск переменной x
    if (str[i] == 'x') {
        i++;
        power = 1;

        if (str[i] == '^') {
            i++;
            if (str[i] && isdigit(str[i])) {
                power = 0;
                while (str[i] && isdigit(str[i])) {
                    power = power * 10 + (str[i] - '0');
                    i++;
                }
            } else {
                return false;
            }
        }
    } else {
        power = 0;
    }

    return true;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Term& term) {
    char buffer[100];
    is >> buffer;

    double coef;
    int power;

    if (parseTerm(buffer, coef, power)) {
        term.coef = coef;
        term.power = power;
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.coef == 0) {
        os << "0";
        return os;
    }

    if (term.coef < 0) {
        os << "-";
    }

    double absCoef = std::abs(term.coef);

    if (term.power == 0) {
        os << absCoef;
    } else if (term.power == 1) {
        if (absCoef == 1) {
            os << "x";
        } else {
            os << absCoef << "x";
        }
    } else {
        if (absCoef == 1) {
            os << "x^" << term.power;
        } else {
            os << absCoef << "x^" << term.power;
        }
    }

    return os;
}
