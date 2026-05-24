#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>
#include <functional>

#include "MyStack.h"

// ==================== ЗАДАНИЕ 2 ====================
// Разложение числа на простые множители с использованием стека
void Multipliers(int n, MyStack<int>& stack) {
    int num = n;
    int divisor = 2;

    while (num > 1) {
        while (num % divisor == 0) {
            stack.push(divisor);
            num /= divisor;
        }
        divisor++;
    }
}

// ==================== ЗАДАНИЕ 4.2 ====================
// Шаблонная функция для вывода содержимого контейнера
template <typename Container>
void printContainer(const Container& cont) {
    for (const auto& elem : cont) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Специализация для map
template <typename K, typename V>
void printContainer(const std::map<K, V>& cont) {
    for (const auto& pair : cont) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
}

// ==================== ЗАДАНИЕ 4.1 ====================
// Функтор для сортировки по убыванию
struct DescendingFunctor {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

int main() {
    // ========== ЗАДАНИЕ 2 ==========
    std::cout << "========== ЗАДАНИЕ 2: Разложение на множители ==========" << std::endl;

    MyStack<int> stack;
    int N = 3960;
    Multipliers(N, stack);

    // Вывод по убыванию (от вершины ко дну)
    std::cout << N << " = ";
    stack.print();
    std::cout << std::endl;

    // Вывод по возрастанию (от дна к вершине)
    MyStack<int> tempStack;
    MyStack<int> reverseStack;

    // Копируем в обратном порядке
    while (!stack.isEmpty()) {
        int value;
        stack.pop(value);
        tempStack.push(value);
    }

    // Восстанавливаем исходный стек и создаём стек для возрастающего порядка
    std::cout << N << " = ";
    bool first = true;
    while (!tempStack.isEmpty()) {
        int value;
        tempStack.pop(value);
        if (!first) std::cout << " * ";
        std::cout << value;
        first = false;
        stack.push(value); // восстанавливаем исходный стек
    }
    std::cout << std::endl;

    // ========== ЗАДАНИЕ 3.1: Работа с vector ==========
    std::cout << "\n========== ЗАДАНИЕ 3.1: Работа с vector ==========" << std::endl;

    // 3.1.1 Перенос в vector (от дна к вершине - возрастающий порядок)
    std::vector<int> vec;

    // Сначала получаем все элементы в обратном порядке (от вершины ко дну)
    std::vector<int> tempVec;
    while (!stack.isEmpty()) {
        int value;
        stack.pop(value);
        tempVec.push_back(value);
    }

    // Восстанавливаем стек и заполняем вектор в возрастающем порядке
    for (auto it = tempVec.rbegin(); it != tempVec.rend(); ++it) {
        vec.push_back(*it);
        stack.push(*it); // восстанавливаем стек
    }

    std::cout << "Исходный вектор (возрастающий): ";
    printContainer(vec);

    // 3.1.2 Использование алгоритмов STL

    // Сортировка по убыванию (с использованием функтора)
    std::sort(vec.begin(), vec.end(), DescendingFunctor());
    std::cout << "Вектор после сортировки по убыванию: ";
    printContainer(vec);

    // Подсчёт количества элементов, равных заданному значению (например, 2)
    int countTwo = std::count(vec.begin(), vec.end(), 2);
    std::cout << "Количество двоек: " << countTwo << std::endl;

    // Преобразование каждого элемента в квадрат
    std::vector<int> squares;
    std::transform(vec.begin(), vec.end(), std::back_inserter(squares),
                   [](int x) { return x * x; });
    std::cout << "Квадраты элементов: ";
    printContainer(squares);

    // Вывод через for_each
    std::cout << "Вывод через for_each: ";
    std::for_each(vec.begin(), vec.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;

    // ========== ЗАДАНИЕ 3.2: Работа с list ==========
    std::cout << "\n========== ЗАДАНИЕ 3.2: Работа с list ==========" << std::endl;

    // 3.2.1 Перенос в list (в возрастающем порядке)
    std::list<int> lst;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        lst.push_back(*it);
    }

    std::cout << "Исходный список: ";
    printContainer(lst);

    // 3.2.2 Удаление всех элементов с заданным значением (удаляем двойки)
    lst.remove_if([](int x) { return x == 2; });
    std::cout << "Список после удаления двоек: ";
    printContainer(lst);

    // Поиск элемента
    auto itFind = std::find(lst.begin(), lst.end(), 5);
    if (itFind != lst.end()) {
        std::cout << "Поиск элемента 5: найден" << std::endl;
    } else {
        std::cout << "Поиск элемента 5: не найден" << std::endl;
    }

    // Подсчёт количества элементов > 3
    int countGreater3 = std::count_if(lst.begin(), lst.end(), [](int x) { return x > 3; });
    std::cout << "Количество элементов > 3: " << countGreater3 << std::endl;

    // ========== ЗАДАНИЕ 3.3: Работа с map ==========
    std::cout << "\n========== ЗАДАНИЕ 3.3: Работа с map ==========" << std::endl;

    // 3.3.1 Создание map (множитель -> количество)
    std::map<int, int> factorMap;

    // Восстанавливаем исходные множители (возрастающий порядок)
    std::vector<int> originalFactors;
    for (auto it = tempVec.rbegin(); it != tempVec.rend(); ++it) {
        originalFactors.push_back(*it);
    }

    for (int factor : originalFactors) {
        factorMap[factor]++;
    }

    // 3.3.2 Использование алгоритмов
    std::cout << "Содержимое map (множитель -> количество):" << std::endl;
    printContainer(factorMap);

    // Поиск элемента по ключу
    auto findKey = factorMap.find(3);
    if (findKey != factorMap.end()) {
        std::cout << "Поиск ключа 3: найден, количество = " << findKey->second << std::endl;
    } else {
        std::cout << "Поиск ключа 3: не найден" << std::endl;
    }

    // Подсчёт количества элементов с количеством > 1
    int countMoreThanOne = std::count_if(factorMap.begin(), factorMap.end(),
                                          [](const std::pair<int, int>& p) { return p.second > 1; });
    std::cout << "Количество множителей, встречающихся более 1 раза: " << countMoreThanOne << std::endl;

    // ========== ЗАДАНИЕ 3.4: Работа с несколькими контейнерами ==========
    std::cout << "\n========== ЗАДАНИЕ 3.4: Работа с несколькими контейнерами ==========" << std::endl;

    // 3.4.1 Создание двух векторов
    std::cout << "Вектор множителей: ";
    printContainer(originalFactors);

    std::cout << "Вектор квадратов: ";
    printContainer(squares);

    // 3.4.2 Вычисление скалярного произведения
    int dotProduct = std::inner_product(originalFactors.begin(), originalFactors.end(),
                                         squares.begin(), 0);
    std::cout << "Скалярное произведение: " << dotProduct << std::endl;

    // 3.4.3 Создание вектора сумм
    std::vector<int> sums;
    std::transform(originalFactors.begin(), originalFactors.end(),
                   squares.begin(), std::back_inserter(sums),
                   [](int a, int b) { return a + b; });
    std::cout << "Вектор сумм: ";
    printContainer(sums);

    // ========== ЗАДАНИЕ 4.3 ==========
    std::cout << "\n========== ЗАДАНИЕ 4.3: Произведение множителей ==========" << std::endl;
    int product = std::accumulate(originalFactors.begin(), originalFactors.end(),
                                   1, std::multiplies<int>());
    std::cout << "Произведение всех множителей: " << product << " (должно быть " << N << ")" << std::endl;

    return 0;
}
