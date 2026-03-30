#include "fraction.hpp"
#include <cmath>
#include <cstring>
#include <cstdlib>

// Конструктор по умолчанию (0/1)
Fraction::Fraction() : numerator(0), denominator(1) {}

// Конструктор с параметрами
Fraction::Fraction(int num, int den) {
    if (den == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен 0");
    }

    // Обработка знака
    if (den < 0) {
        num = -num;
        den = -den;
    }

    numerator = num;
    denominator = den;
    simplify();
}

// Конструктор преобразования из строки
Fraction::Fraction(const char* str) {
    fromString(str);
}

// Конструктор копирования
Fraction::Fraction(const Fraction& other)
    : numerator(other.numerator), denominator(other.denominator) {}

// Конструктор из double
Fraction::Fraction(double value) {
    // Обработка отрицательных чисел
    bool isNegative = (value < 0);
    value = std::abs(value);

    // Разделяем целую и дробную части
    long long intPart = static_cast<long long>(value);
    double fractionalPart = value - intPart;

    // Преобразуем дробную часть в целое число с заданной точностью
    long long num = static_cast<long long>(fractionalPart * std::pow(10, kNumberDecimalPlaces) + 0.5);
    long long den = static_cast<long long>(std::pow(10, kNumberDecimalPlaces));

    // Сокращаем дробную часть
    if (num > 0) {
        long long tempGcd = gcd(static_cast<int>(num), static_cast<int>(den));
        num /= tempGcd;
        den /= tempGcd;
    }

    // Формируем числитель и знаменатель
    numerator = static_cast<int>(intPart * den + num);
    denominator = static_cast<int>(den);

    if (isNegative && numerator != 0) {
        numerator = -numerator;
    }

    simplify();
}

// НОД
int Fraction::gcd(int a, int b) const {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Сокращение дроби
void Fraction::simplify() {
    if (denominator == 0) return;
    if (numerator == 0) {
        denominator = 1;
        return;
    }

    int divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;

    // Знаменатель всегда положительный
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

// Преобразование из строки
void Fraction::fromString(const char* str) {
    if (str == nullptr || str[0] == '\0') {
        *this = Fraction();
        return;
    }

    // Пропускаем начальные пробелы
    while (*str == ' ' || *str == '\t') {
        str++;
    }

    if (*str == '\0') {
        *this = Fraction();
        return;
    }

    int sign = 1;
    const char* ptr = str;

    // Обработка знака
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }

    // Ищем пробел и слеш
    const char* spacePos = nullptr;
    const char* slashPos = nullptr;
    const char* temp = ptr;

    while (*temp != '\0') {
        if (*temp == ' ' && spacePos == nullptr) {
            spacePos = temp;
        } else if (*temp == '/') {
            slashPos = temp;
            break;
        }
        temp++;
    }

    if (slashPos != nullptr) {
        // Нашли слеш - это дробь
        if (spacePos != nullptr && spacePos < slashPos) {
            // Есть целая часть: целая часть числитель/знаменатель
            int wholePart = 0;
            const char* wholeStart = ptr;
            int wholeLen = spacePos - wholeStart;

            char wholeBuf[32];
            int wholeIdx = 0;
            for (int i = 0; i < wholeLen; i++) {
                wholeBuf[wholeIdx++] = wholeStart[i];
            }
            wholeBuf[wholeIdx] = '\0';
            wholePart = std::atoi(wholeBuf);

            // Пропускаем пробелы
            const char* numStart = spacePos + 1;
            while (*numStart == ' ' || *numStart == '\t') {
                numStart++;
            }

            // Извлекаем числитель
            int num = 0;
            const char* numPtr = numStart;
            char numBuf[32];
            int numIdx = 0;
            while (numPtr < slashPos && (*numPtr >= '0' && *numPtr <= '9')) {
                numBuf[numIdx++] = *numPtr;
                numPtr++;
            }
            numBuf[numIdx] = '\0';
            num = std::atoi(numBuf);

            // Извлекаем знаменатель
            int den = 0;
            const char* denStart = slashPos + 1;
            char denBuf[32];
            int denIdx = 0;
            while (*denStart >= '0' && *denStart <= '9') {
                denBuf[denIdx++] = *denStart;
                denStart++;
            }
            denBuf[denIdx] = '\0';
            den = std::atoi(denBuf);

            if (den == 0) {
                throw std::invalid_argument("Знаменатель не может быть равен 0");
            }

            numerator = sign * (wholePart * den + num);
            denominator = den;
        } else {
            // Только дробная часть: числитель/знаменатель
            int num = 0;
            const char* numPtr = ptr;
            char numBuf[32];
            int numIdx = 0;
            while (numPtr < slashPos && (*numPtr >= '0' && *numPtr <= '9')) {
                numBuf[numIdx++] = *numPtr;
                numPtr++;
            }
            numBuf[numIdx] = '\0';
            num = std::atoi(numBuf);

            int den = 0;
            const char* denStart = slashPos + 1;
            char denBuf[32];
            int denIdx = 0;
            while (*denStart >= '0' && *denStart <= '9') {
                denBuf[denIdx++] = *denStart;
                denStart++;
            }
            denBuf[denIdx] = '\0';
            den = std::atoi(denBuf);

            if (den == 0) {
                throw std::invalid_argument("Знаменатель не может быть равен 0");
            }

            numerator = sign * num;
            denominator = den;
        }
    } else {
        // Целое число
        int wholePart = std::atoi(ptr);
        numerator = sign * wholePart;
        denominator = 1;
    }

    simplify();
}

// Оператор сложения дробей
Fraction Fraction::operator+(const Fraction& other) const {
    Fraction result;
    result.numerator = numerator * other.denominator + other.numerator * denominator;
    result.denominator = denominator * other.denominator;
    result.simplify();
    return result;
}

// Оператор сложения с присваиванием
Fraction& Fraction::operator+=(const Fraction& other) {
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator = denominator * other.denominator;
    simplify();
    return *this;
}

// Оператор вычитания дробей
Fraction Fraction::operator-(const Fraction& other) const {
    Fraction result;
    result.numerator = numerator * other.denominator - other.numerator * denominator;
    result.denominator = denominator * other.denominator;
    result.simplify();
    return result;
}

// Оператор вычитания с присваиванием
Fraction& Fraction::operator-=(const Fraction& other) {
    numerator = numerator * other.denominator - other.numerator * denominator;
    denominator = denominator * other.denominator;
    simplify();
    return *this;
}

// Дружественные операторы для double
Fraction operator+(double lhs, const Fraction& rhs) {
    return Fraction(lhs) + rhs;
}

Fraction operator+(const Fraction& lhs, double rhs) {
    return lhs + Fraction(rhs);
}

Fraction& operator+=(Fraction& lhs, double rhs) {
    lhs = lhs + Fraction(rhs);
    return lhs;
}

// Дружественные операторы для int
Fraction operator+(int lhs, const Fraction& rhs) {
    return Fraction(lhs, 1) + rhs;
}

Fraction operator+(const Fraction& lhs, int rhs) {
    return lhs + Fraction(rhs, 1);
}

Fraction& operator+=(Fraction& lhs, int rhs) {
    lhs = lhs + Fraction(rhs, 1);
    return lhs;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    if (frac.numerator == 0) {
        os << "0";
    } else {
        int whole = frac.numerator / frac.denominator;
        int remainder = std::abs(frac.numerator % frac.denominator);

        if (whole != 0) {
            os << whole;
            if (remainder != 0) {
                os << " " << remainder << "/" << frac.denominator;
            }
        } else {
            os << frac.numerator << "/" << frac.denominator;
        }
    }
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Fraction& frac) {
    char buffer[256];
    is >> buffer;

    try {
        frac.fromString(buffer);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка ввода дроби: " << e.what() << std::endl;
        frac = Fraction();
    }

    return is;
}
