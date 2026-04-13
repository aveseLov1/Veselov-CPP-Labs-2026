#include <iostream>
#include <iomanip>
#include "fraction.hpp"

using namespace std;

int main() {
    try {
        // Ввод дроби с клавиатуры
        cout << "Введите дробь: \n";
        char input[256];
        cin.getline(input, 256);  // Читаем всю строку в C-строку
        Fraction z(input);
        cout << "z=" << z << endl;

        // Проверка конструкторов
        Fraction fr1(10, 14), fr2;
        cout << "fr2=" << fr2 << endl;
        cout << "fr1=" << fr1 << endl;
        Fraction fr = "-1 4/8";
        cout << "fr=" << fr << endl;

        Fraction x(z), y;
        cout << "x=" << x << endl;

        double dbl = -1.25;
        Fraction f = dbl;
        cout << "f=" << f << endl;

        // Проверка перегруженной операции "+"
        y = x + z;
        cout << "y=" << y << endl;

        y += x;
        f += dbl / 2;
        cout << "f=" << f << endl;

        y = x + dbl;
        cout << "y=" << y << endl;

        y = dbl + y;
        cout << "y=" << y << endl;

        y += dbl;
        cout << "y=" << y << endl;

        int i = 5;
        y += i;
        cout << "y=" << y << endl;

        y = i + x;
        cout << "y=" << y << endl;

        y = x + i;
        cout << "y=" << y << endl;

        y += dbl + i + x;
        cout << "y=" << y << endl;

    } catch (const std::exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
