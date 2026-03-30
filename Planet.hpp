#ifndef PLANET_HPP
#define PLANET_HPP

#include <iostream>
#include <cstring>

class Planet {
private:
    char* name;
    double mass;

public:
    // Конструкторы и деструктор
    Planet() noexcept;
    explicit Planet(const char* name, double mass);
    Planet(const Planet& other);
    Planet(Planet&& other) noexcept;
    ~Planet();

    // ✅ Оператор присваивания — параметр по значению!
    Planet& operator=(Planet other) noexcept;

    // Методы доступа
    const char* getName() const;
    double getMass() const;
    void setName(const char* name);
    void setMass(double mass);

    // Перегрузка потокового ввода-вывода
    friend std::ostream& operator<<(std::ostream& os, const Planet& p);
    friend std::istream& operator>>(std::istream& is, Planet& p);
};

#endif // PLANET_HPP
