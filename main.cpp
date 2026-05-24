#include <iostream>
#include <sstream>
#include "Term.h"
#include "Polynomial.h"

using namespace std;

void demonstrateTerm() {
    cout << "\n========== Демонстрация работы класса Term ==========\n" << endl;

    Term t1;
    Term t2(5);
    Term t3(3, 2);
    Term t4(-2, 3);
    Term t5(1, 1);
    Term t6(-1, 4);

    cout << "t1 (по умолчанию): " << t1 << endl;
    cout << "t2 (5): " << t2 << endl;
    cout << "t3 (3x^2): " << t3 << endl;
    cout << "t4 (-2x^3): " << t4 << endl;
    cout << "t5 (x): " << t5 << endl;
    cout << "t6 (-x^4): " << t6 << endl;

    Term t7(2, 2);
    Term t8 = t3 + t7;
    cout << "\nСложение: " << t3 << " + " << t7 << " = " << t8 << endl;

    Term t9 = t4;
    cout << "Присваивание: t9 = t4 -> " << t9 << endl;

    cout << "\nВведите терм (например, 3x^2 или -5x или 7): ";
    Term t10;
    cin >> t10;
    cout << "Вы ввели: " << t10 << endl;

    cout << "\nСравнение степеней: " << t3 << " и " << t7 << " имеют одинаковую степень? ";
    cout << ((t3 == t7) ? "Да" : "Нет") << endl;
}

void demonstratePolynomial() {
    cout << "\n========== Демонстрация работы класса Polynomial ==========\n" << endl;

    Polynomial p1;
    Polynomial p2(7);
    Polynomial p3(Term(4, 3));

    cout << "p1 (пустой): " << p1 << endl;
    cout << "p2 (константа 7): " << p2 << endl;
    cout << "p3 (один терм 4x^3): " << p3 << endl;

    p1.addTerm(Term(3, 2));
    p1.addTerm(Term(-1, 2));
    p1.addTerm(Term(5, 0));
    p1.addTerm(Term(2, 1));
    cout << "\nПосле добавления термов: " << p1 << endl;

    cout << "\nВведите полином (например: 3x^2 - x^2 + 5x^5 - 4x^3 + x^2 - 7):" << endl;
    Polynomial p4;
    cin >> p4;
    cout << "Введенный полином: " << p4 << endl;

    Polynomial p5(Term(5, 2));
    Polynomial p6 = p1 + p5;
    cout << "\nСложение: " << p1 << " + " << p5 << " = " << p6 << endl;

    Polynomial p7 = p1 - p5;
    cout << "Вычитание: " << p1 << " - " << p5 << " = " << p7 << endl;

    Polynomial p8(Term(2, 1));
    Polynomial p9(Term(3, 2));
    Polynomial p10 = p8 * p9;
    cout << "\nУмножение: " << p8 << " * " << p9 << " = " << p10 << endl;

    Polynomial p11(Term(3, 2));
    p11.addTerm(Term(5, 0));
    Polynomial p12(Term(5, 0));
    p12.addTerm(Term(3, 2));
    cout << "\nСравнение: " << p11 << " == " << p12 << " ? " << ((p11 == p12) ? "Да" : "Нет") << endl;

    Polynomial p13;
    p13.addTerm(Term(2, 2));
    p13.addTerm(Term(3, 1));
    p13.addTerm(Term(1, 0));
    double x = 2.0;
    cout << "\nВычисление " << p13 << " при x = " << x << ": " << p13.evaluate(x) << endl;

    p13.removeTerm(1);
    cout << "После удаления члена со степенью 1: " << p13 << endl;

    cout << "\nТекущий порядок (по убыванию): " << p13 << endl;
    p13.setOrder(true);
    cout << "Порядок по возрастанию: " << p13 << endl;
    p13.setOrder(false);
    cout << "Порядок по убыванию: " << p13 << endl;

    Polynomial p14(Term(2, 1));
    p14 += Polynomial(Term(3, 2));
    cout << "\np14 += 3x^2: " << p14 << endl;

    p14 -= Polynomial(Term(1, 1));
    cout << "p14 -= x: " << p14 << endl;

    p14 *= Polynomial(Term(2, 0));
    cout << "p14 *= 2: " << p14 << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "Лабораторная работа №7: Полиномы" << endl;
    cout << "========================================" << endl;

    demonstrateTerm();
    demonstratePolynomial();

    cout << "\n========================================" << endl;
    cout << "Программа завершена успешно!" << endl;
    cout << "========================================" << endl;

    return 0;
}
