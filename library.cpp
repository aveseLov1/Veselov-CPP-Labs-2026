#include "library.hpp"
#include <iomanip>

// --- Вспомогательный метод ---

void Book::copyString(char*& dest, const char* src) {
    delete[] dest;
    if (src == nullptr) {
        dest = nullptr;
    } else {
        dest = new char[strlen(src) + 1];
        strcpy(dest, src);
    }
}

// --- Rule of Three ---

Book::~Book() {
    delete[] title;
    delete[] author;
}

Book::Book(const Book& other) : year(other.year), id(other.id) {
    copyString(title, other.title);
    copyString(author, other.author);
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        year = other.year;
        id = other.id;
        copyString(title, other.title);
        copyString(author, other.author);
    }
    return *this;
}

// --- Конструкторы ---

Book::Book() : title(nullptr), author(nullptr), year(0), id(0) {
    copyString(title, "Unknown Title");
    copyString(author, "Unknown Author");
}

Book::Book(const char* t, const char* a, int y, int i) : year(y), id(i) {
    title = nullptr;
    author = nullptr;
    copyString(title, t);
    copyString(author, a);
}

// --- Getters & Setters ---

const char* Book::getTitle() const { return title; }
const char* Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
int Book::getId() const { return id; }

void Book::setTitle(const char* t) { copyString(title, t); }
void Book::setAuthor(const char* a) { copyString(author, a); }
void Book::setYear(int y) { year = y; }
void Book::setId(int i) { id = i; }

// --- Перегрузка операторов ---

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "ID: " << book.id
       << " | Название: " << (book.title ? book.title : "N/A")
       << " | Автор: " << (book.author ? book.author : "N/A")
       << " | Год: " << book.year;
    return os;
}

std::istream& operator>>(std::istream& is, Book& book) {
    char buffer[MAX_INPUT_LEN];

    std::cout << "Введите ID: ";
    is >> book.id;
    is.ignore();

    std::cout << "Введите название: ";
    if (is.getline(buffer, MAX_INPUT_LEN)) {
        book.setTitle(buffer);
    }

    std::cout << "Введите автора: ";
    if (is.getline(buffer, MAX_INPUT_LEN)) {
        book.setAuthor(buffer);
    }

    std::cout << "Введите год издания: ";
    is >> book.year;
    is.ignore();

    return is;
}

// --- Меню и main ---

void showMenu() {
    std::cout << "\n--- Меню ---" << std::endl;
    std::cout << "1. Создать/Изменить одиночный объект" << std::endl;
    std::cout << "2. Вывести одиночный объект" << std::endl;
    std::cout << "3. Добавить книгу в массив (библиотеку)" << std::endl;
    std::cout << "4. Вывести массив книг" << std::endl;
    std::cout << "5. Выход" << std::endl;
    std::cout << "Выбор: ";
}

int main() {
    #ifdef _WIN32
    setlocale(LC_ALL, "Russian");
    #endif

    Book singleBook;
    Book library[5];
    int libraryCount = 0;

    int choice;
    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(32767, '\n');

        switch (choice) {
        case 1:
            std::cout << "\n--- Создание одиночного объекта ---" << std::endl;
            std::cin >> singleBook;
            std::cout << "Объект создан." << std::endl;
            break;

        case 2:
            std::cout << "\n--- Одиночный объект ---" << std::endl;
            std::cout << singleBook << std::endl;
            break;

        case 3:
            if (libraryCount >= 5) {
                std::cout << "Библиотека заполнена (максимум 5 книг)!" << std::endl;
            } else {
                std::cout << "\n--- Добавление книги в массив ("
                          << libraryCount + 1 << "/5) ---" << std::endl;
                std::cin >> library[libraryCount];
                libraryCount++;
                std::cout << "Книга добавлена." << std::endl;
            }
            break;

        case 4:
            std::cout << "\n--- Список книг в библиотеке ---" << std::endl;
            if (libraryCount == 0) {
                std::cout << "Библиотека пуста." << std::endl;
            } else {
                for (int i = 0; i < libraryCount; ++i) {
                    std::cout << "[" << i + 1 << "] " << library[i] << std::endl;
                }
            }
            break;

        case 5:
            std::cout << "Выход из программы." << std::endl;
            break;

        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }

    } while (choice != 5);

    return 0;
}


// #include <iostream>
// #include <cstring>
// #include <iomanip>

// using namespace std;

// // Константа для максимального размера ввода с консоли
// const int MAX_INPUT_LEN = 256;

// class Book {
// private:
//     char* title;  // Название книги (C-строка)
//     char* author; // Автор (C-строка)
//     int year;     // Год издания
//     int id;       // Инвентарный номер

//     // Вспомогательный метод для безопасного копирования строк (DRY)
//     void copyString(char*& dest, const char* src) {
//         delete[] dest; // Освобождаем старую память
//         if (src == nullptr) {
//             dest = nullptr;
//         } else {
//             dest = new char[strlen(src) + 1];
//             strcpy(dest, src);
//         }
//     }

// public:
//     // 1. Конструктор по умолчанию
//     Book() : title(nullptr), author(nullptr), year(0), id(0) {
//         copyString(title, "Unknown Title");
//         copyString(author, "Unknown Author");
//     }

//     // 2. Конструктор с параметрами
//     Book(const char* t, const char* a, int y, int i) : year(y), id(i) {
//         copyString(title, t);
//         copyString(author, a);
//     }

//     // 3. Конструктор копирования (Глубокое копирование)
//     Book(const Book& other) : year(other.year), id(other.id) {
//         copyString(title, other.title);
//         copyString(author, other.author);
//     }

//     // 4. Оператор присваивания
//     Book& operator=(const Book& other) {
//         if (this != &other) { // Проверка на самоприсваивание
//             year = other.year;
//             id = other.id;
//             copyString(title, other.title);
//             copyString(author, other.author);
//         }
//         return *this;
//     }

//     // 5. Деструктор
//     ~Book() {
//         delete[] title;
//         delete[] author;
//     }

//     // Getters
//     const char* getTitle() const { return title; }
//     const char* getAuthor() const { return author; }
//     int getYear() const { return year; }
//     int getId() const { return id; }

//     // Setters
//     void setTitle(const char* t) { copyString(title, t); }
//     void setAuthor(const char* a) { copyString(author, a); }
//     void setYear(int y) { year = y; }
//     void setId(int i) { id = i; }

//     // 6. Перегрузка оператора вывода (ostream)
//     friend ostream& operator<<(ostream& os, const Book& book) {
//         os << "ID: " << book.id
//            << " | Название: " << (book.title ? book.title : "N/A")
//            << " | Автор: " << (book.author ? book.author : "N/A")
//            << " | Год: " << book.year;
//         return os;
//     }

//     // 7. Перегрузка оператора ввода (istream)
//     friend istream& operator>>(istream& is, Book& book) {
//         char buffer[MAX_INPUT_LEN];

//         cout << "Введите ID: ";
//         is >> book.id;
//         is.ignore(); // Очистка буфера ввода

//         cout << "Введите название: ";
//         if (is.getline(buffer, MAX_INPUT_LEN)) {
//             book.setTitle(buffer);
//         }

//         cout << "Введите автора: ";
//         if (is.getline(buffer, MAX_INPUT_LEN)) {
//             book.setAuthor(buffer);
//         }

//         cout << "Введите год издания: ";
//         is >> book.year;
//         is.ignore();

//         return is;
//     }
// };

// // Функция для вывода меню
// void showMenu() {
//     cout << "\n--- Меню ---" << endl;
//     cout << "1. Создать/Изменить одиночный объект" << endl;
//     cout << "2. Вывести одиночный объект" << endl;
//     cout << "3. Добавить книгу в массив (библиотеку)" << endl;
//     cout << "4. Вывести массив книг" << endl;
//     cout << "5. Выход" << endl;
//     cout << "Выбор: ";
// }

// int main() {
//     // Установка локали для корректного отображения русского текста (для Windows)
//     #ifdef _WIN32
//     setlocale(LC_ALL, "Russian");
//     #endif

//     // 1. Создание одного объекта (изначально дефолтного)
//     Book singleBook;

//     // 2. Статический массив из 5 объектов
//     Book library[5];
//     int libraryCount = 0; // Счётчик заполненных ячеек

//     int choice;
//     do {
//         showMenu();
//         cin >> choice;
//         // Очистка буфера после ввода числа
//         cin.ignore(32767, '\n');

//         switch (choice) {
//         case 1:
//             cout << "\n--- Создание одиночного объекта ---" << endl;
//             cin >> singleBook;
//             cout << "Объект создан." << endl;
//             break;

//         case 2:
//             cout << "\n--- Одиночный объект ---" << endl;
//             cout << singleBook << endl;
//             break;

//         case 3:
//             if (libraryCount >= 5) {
//                 cout << "Библиотека заполнена (максимум 5 книг)!" << endl;
//             } else {
//                 cout << "\n--- Добавление книги в массив (" << libraryCount + 1 << "/5) ---" << endl;
//                 cin >> library[libraryCount];
//                 libraryCount++;
//                 cout << "Книга добавлена." << endl;
//             }
//             break;

//         case 4:
//             cout << "\n--- Список книг в библиотеке ---" << endl;
//             if (libraryCount == 0) {
//                 cout << "Библиотека пуста." << endl;
//             } else {
//                 for (int i = 0; i < libraryCount; ++i) {
//                     cout << "[" << i + 1 << "] " << library[i] << endl;
//                 }
//             }
//             break;

//         case 5:
//             cout << "Выход из программы." << endl;
//             break;

//         default:
//             cout << "Неверный выбор. Попробуйте снова." << endl;
//         }

//     } while (choice != 5);

//     return 0;
// }
