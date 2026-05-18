#include <iostream>
#include <string>
#include "containers/Container.h"
#include "containers/Set.h"

int main() {

    // ===== Container =====
    Container<std::string> v("Hello!");
    v.push("Привет!");
    v.push("World");
    v.push("Test");

    std::cout << "Вектор v: " << v << std::endl;

    // Проверка поиска
    int index = v.find("World");
    std::cout << "Индекс элемента 'World': " << index << std::endl;

    v.push("Another");
    v.push("Example");

    std::cout << "Вектор v после добавления: " << v << std::endl;

    Container<std::string> v1 = v;
    std::cout << "Копия v1: " << v1 << std::endl;

    v1.pop(2);
    std::cout << "v1 после удаления элемента с индексом 2: " << v1 << std::endl;


    // ===== Set<char*> =====
    Set<char*> s("Yes"), s1("Hello!"), s2;

    s.push("Привет!");
    s.push("No");
    s.push("World");

    std::cout << "\nМножество s: " << s << std::endl;

    // Проверка наличия элемента
    if (s.is_element("No"))
        std::cout << "'No' есть в множестве s\n";

    s1.push("Cat");
    s1.push("Dog");
    s1.push("Привет!");

    std::cout << "Множество s1: " << s1 << std::endl;

    // Разность
    s2 = s1 - s;
    std::cout << "s2 = s1 - s: " << s2 << std::endl;

    // Объединение
    s2 = s1 + s;
    std::cout << "s2 = s1 + s: " << s2 << std::endl;

    // Пересечение
    s2 = s1 * s;
    std::cout << "s2 = s1 * s: " << s2 << std::endl;

    // Сравнение
    Set<char*> s3 = s2;
    std::cout << "s3: " << s3 << std::endl;

    if (s3 == s2)
        std::cout << "s3 == s2\n";
    else
        std::cout << "s3 != s2\n";


    // ===== Set<int> =====
    Set<int> one(1);
    one.push(2);
    one.push(3);
    one.push(5);

    Set<int> two;
    two.push(2);
    two.push(3);
    two.push(10);

    std::cout << "\none: " << one << std::endl;
    std::cout << "two: " << two << std::endl;

    one -= two;
    std::cout << "one -= two: " << one << std::endl;


    // ===== Set<double> =====
    Set<double> one1(1.5);
    one1.push(2.0);
    one1.push(3.99);

    Set<double> two1;
    two1.push(2.0);
    two1.push(3.98);
    two1.push(10.0);

    std::cout << "\none1: " << one1 << std::endl;
    std::cout << "two1: " << two1 << std::endl;

    one1 -= two1;
    std::cout << "one1 -= two1: " << one1 << std::endl;


    // ===== Set<string> =====
    Set<std::string> stroka;
    stroka.push("Привет!");
    stroka.push("Hello");
    stroka.push("Привет!"); // дубликат

    std::cout << "\nStroka: " << stroka << std::endl;

    if (!stroka.is_element("Bye"))
        std::cout << "'Bye' отсутствует в stroka\n";

    return 0;
}
