#include "Polynomial.h"
#include <cctype>
#include <cmath>

const int INITIAL_CAPACITY = 4;

// Конструктор по умолчанию
Polynomial::Polynomial() : size(0), capacity(INITIAL_CAPACITY), order(false) {
    terms = new Term[capacity];
}

// Конструктор от константы
Polynomial::Polynomial(double constant) : size(0), capacity(INITIAL_CAPACITY), order(false) {
    terms = new Term[capacity];
    if (constant != 0) {
        addTerm(Term(constant, 0));
    }
}

// Конструктор от терма
Polynomial::Polynomial(const Term& term) : size(0), capacity(INITIAL_CAPACITY), order(false) {
    terms = new Term[capacity];
    addTerm(term);
}

// Конструктор копирования
Polynomial::Polynomial(const Polynomial& other)
    : size(other.size), capacity(other.capacity), order(other.order) {
    terms = new Term[capacity];
    for (int i = 0; i < size; i++) {
        terms[i] = other.terms[i];
    }
}

// Деструктор
Polynomial::~Polynomial() {
    delete[] terms;
}

// Увеличение capacity
void Polynomial::resize() {
    capacity *= 2;
    Term* newTerms = new Term[capacity];
    for (int i = 0; i < size; i++) {
        newTerms[i] = terms[i];
    }
    delete[] terms;
    terms = newTerms;
}

// Приведение подобных членов
void Polynomial::simplify() {
    if (size <= 1) return;

    sort();

    int writeIndex = 0;
    for (int i = 0; i < size; i++) {
        if (writeIndex > 0 && terms[writeIndex - 1].getPower() == terms[i].getPower()) {
            Term sum = terms[writeIndex - 1] + terms[i];
            terms[writeIndex - 1] = sum;
        } else {
            if (writeIndex != i) {
                terms[writeIndex] = terms[i];
            }
            writeIndex++;
        }
    }
    size = writeIndex;

    removeZeros();
}

// Удаление нулевых членов
void Polynomial::removeZeros() {
    int writeIndex = 0;
    for (int i = 0; i < size; i++) {
        if (terms[i].getCoef() != 0) {
            if (writeIndex != i) {
                terms[writeIndex] = terms[i];
            }
            writeIndex++;
        }
    }
    size = writeIndex;
}

// Сортировка по степени
void Polynomial::sort() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bool needSwap = order ? (terms[j].getPower() > terms[j + 1].getPower())
                                  : (terms[j].getPower() < terms[j + 1].getPower());
            if (needSwap) {
                Term temp = terms[j];
                terms[j] = terms[j + 1];
                terms[j + 1] = temp;
            }
        }
    }
}

// Добавление одночлена
void Polynomial::addTerm(const Term& term) {
    if (term.getCoef() == 0) return;

    if (size >= capacity) {
        resize();
    }

    terms[size] = term;
    size++;

    simplify();
}

// Удаление одночлена по степени
void Polynomial::removeTerm(int power) {
    int foundIndex = -1;
    for (int i = 0; i < size; i++) {
        if (terms[i].getPower() == power) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < size - 1; i++) {
            terms[i] = terms[i + 1];
        }
        size--;
    }
}

// Вычисление значения
double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        double termValue = terms[i].getCoef();
        if (terms[i].getPower() > 0) {
            termValue *= pow(x, terms[i].getPower());
        }
        result += termValue;
    }
    return result;
}

// Оператор присваивания
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] terms;
        size = other.size;
        capacity = other.capacity;
        order = other.order;
        terms = new Term[capacity];
        for (int i = 0; i < size; i++) {
            terms[i] = other.terms[i];
        }
    }
    return *this;
}

// Оператор сложения полиномов
Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial result = *this;
    for (int i = 0; i < other.size; i++) {
        result.addTerm(other.terms[i]);
    }
    return result;
}

// Оператор сложения полинома с термом
Polynomial Polynomial::operator+(const Term& term) const {
    Polynomial result = *this;
    result.addTerm(term);
    return result;
}

// Оператор += для полинома
Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (int i = 0; i < other.size; i++) {
        addTerm(other.terms[i]);
    }
    return *this;
}

// Оператор += для терма
Polynomial& Polynomial::operator+=(const Term& term) {
    addTerm(term);
    return *this;
}

// Оператор вычитания
Polynomial Polynomial::operator-(const Polynomial& other) const {
    Polynomial result = *this;
    for (int i = 0; i < other.size; i++) {
        Term negTerm(-other.terms[i].getCoef(), other.terms[i].getPower());
        result.addTerm(negTerm);
    }
    return result;
}

// Оператор -=
Polynomial& Polynomial::operator-=(const Polynomial& other) {
    for (int i = 0; i < other.size; i++) {
        Term negTerm(-other.terms[i].getCoef(), other.terms[i].getPower());
        addTerm(negTerm);
    }
    return *this;
}

// Оператор умножения
Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial result;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < other.size; j++) {
            double newCoef = terms[i].getCoef() * other.terms[j].getCoef();
            int newPower = terms[i].getPower() + other.terms[j].getPower();
            result.addTerm(Term(newCoef, newPower));
        }
    }
    return result;
}

// Оператор *=
Polynomial& Polynomial::operator*=(const Polynomial& other) {
    *this = *this * other;
    return *this;
}

// Оператор сравнения
bool Polynomial::operator==(const Polynomial& other) const {
    if (size != other.size) return false;

    for (int i = 0; i < size; i++) {
        if (terms[i].getPower() != other.terms[i].getPower() ||
            terms[i].getCoef() != other.terms[i].getCoef()) {
            return false;
        }
    }
    return true;
}

// Функция для парсинга терма из C-строки (объявлена в Term.cpp)
extern bool parseTerm(const char* str, double& coef, int& power);

// Функция для парсинга терма без использования istringstream
static void parseTermFromString(const char* str, Term& term) {
    double coef;
    int power;

    if (parseTerm(str, coef, power)) {
        term = Term(coef, power);
    }
}

// Разбор строки на термы (без STL)
static void parsePolynomialString(const char* line, Polynomial& poly) {
    const char* ptr = line;
    char termBuffer[100];
    int termIndex = 0;
    bool inTerm = false;

    while (*ptr) {
        // Пропускаем пробелы
        while (*ptr && isspace(*ptr)) {
            ptr++;
        }

        if (*ptr == '+' || *ptr == '-') {
            // Завершаем предыдущий терм
            if (inTerm && termIndex > 0) {
                termBuffer[termIndex] = '\0';
                Term term;
                parseTermFromString(termBuffer, term);
                poly.addTerm(term);
                termIndex = 0;
                inTerm = false;
            }

            // Начинаем новый терм
            termBuffer[termIndex++] = *ptr;
            ptr++;
            inTerm = true;
        }
        else if (*ptr && !isspace(*ptr)) {
            // Добавляем символ к текущему терму
            if (termIndex < 99) {
                termBuffer[termIndex++] = *ptr;
            }
            ptr++;
            inTerm = true;
        }
        else if (*ptr == '\0') {
            break;
        }
        else {
            ptr++;
        }
    }

    // Завершаем последний терм
    if (inTerm && termIndex > 0) {
        termBuffer[termIndex] = '\0';
        Term term;
        parseTermFromString(termBuffer, term);
        poly.addTerm(term);
    }
}

// Оператор ввода (без STL)
std::istream& operator>>(std::istream& is, Polynomial& poly) {
    char line[1000];
    is.getline(line, 1000);

    poly = Polynomial();
    parsePolynomialString(line, poly);

    return is;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.size == 0) {
        os << "0";
        return os;
    }

    bool first = true;
    for (int i = 0; i < poly.size; i++) {
        const Term& term = poly.terms[i];
        if (term.getCoef() == 0) continue;

        if (!first) {
            if (term.getCoef() > 0) {
                os << " + ";
            } else {
                os << " - ";
            }
            Term tempTerm(std::abs(term.getCoef()), term.getPower());
            os << tempTerm;
        } else {
            os << term;
            first = false;
        }
    }

    return os;
}
