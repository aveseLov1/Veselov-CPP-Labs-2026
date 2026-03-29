// #include <iostream>
// #include "fraction.hpp"

// int main() {
//     try {
//         Fraction z;
//         std::cout << "Введите дробь: ";
//         std::cin >> z;
//         std::cout << "1. Ввод дроби с клавиатуры\n";
//         std::cout << "z = " << z << std::endl;

//         Fraction fr1(10, 14);
//         Fraction fr2;
//         Fraction fr3("-1 4/8");

//         std::cout << "2. Проверка конструкторов\n";
//         std::cout << "fr1 = " << fr1 << std::endl;
//         std::cout << "fr2 = " << fr2 << std::endl;
//         std::cout << "fr3 = " << fr3 << std::endl;

//         Fraction x(z);
//         std::cout << "3. Проверка копирующего конструктора\n";
//         std::cout << "x = " << x << std::endl;

//         std::cout << "4. Арифметические операции (дробь + дробь)" << std::endl;
//         Fraction y = x + fr1;
//         std::cout << "y = x + fr1 = " << y << std::endl;

//         y += fr3;
//         std::cout << "y += fr3 -> " << y << std::endl;

//         std::cout << "5. Арифметика с целыми числами" << std::endl;
//         int i = 5;
//         // Используем конструктор с двумя параметрами для int
//         y = x + Fraction(i, 1);
//         std::cout << "y = x + i = " << y << std::endl;

//         y = Fraction(i, 1) + x;
//         std::cout << "y = i + x = " << y << std::endl;

//         y += Fraction(i, 1);
//         std::cout << "y += i -> " << y << std::endl;

//         std::cout << "6. Арифметика с double" << std::endl;
//         double d = -1.25;
//         Fraction f = Fraction(d);  // Явное преобразование double -> Fraction
//         std::cout << "f = " << f << std::endl;

//         y = x + Fraction(d);
//         std::cout << "y = x + d = " << y << std::endl;

//         y = Fraction(d) + x;
//         std::cout << "y = d + x = " << y << std::endl;

//         y += Fraction(d);
//         std::cout << "y += d -> " << y << std::endl;

//         y += Fraction(d) + Fraction(i, 1);
//         std::cout << "y += d + i -> " << y << std::endl;

//     } catch (const std::exception& e) {
//         std::cerr << "Ошибка: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }




#include <iostream>
#include <iomanip>
#include "fraction.hpp"

using namespace std;

int main() {
    // ввод дроби с клавиатуры
    cout << "Введите дробь: \n";
    Fraction z;
    cin >> z;
    cout << "z=" << z << endl;

    // проверка конструкторов
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

    // проверка перегруженной операции "+"
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

    return 0;
}
