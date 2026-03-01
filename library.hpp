#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>
#include <cstring>

const int MAX_INPUT_LEN = 256;

class Book {
private:
    char* title;
    char* author;
    int year;
    int id;

    // Вспомогательный метод для копирования строк (DRY)
    void copyString(char*& dest, const char* src);

public:
    // Rule of Three
    ~Book();
    Book(const Book& other);
    Book& operator=(const Book& other);

    // Конструкторы
    Book();
    Book(const char* t, const char* a, int y, int i);

    // Getters
    const char* getTitle() const;
    const char* getAuthor() const;
    int getYear() const;
    int getId() const;

    // Setters
    void setTitle(const char* t);
    void setAuthor(const char* a);
    void setYear(int y);
    void setId(int i);

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
};

#endif // LIBRARY_HPP
