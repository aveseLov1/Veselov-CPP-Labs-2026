#include "Planet.hpp"
#include <cstring>
#include <algorithm>

// Конструктор по умолчанию
Planet::Planet() noexcept : name(nullptr), mass(0.0) {}

// Конструктор с параметрами
Planet::Planet(const char* name, double mass) : mass(mass) {
    if (name) {
        this->name = new char[std::strlen(name) + 1];
        std::strcpy(this->name, name);
    } else {
        this->name = nullptr;
    }
}

// Конструктор копирования
Planet::Planet(const Planet& other) : mass(other.mass) {
    if (other.name) {
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
    } else {
        name = nullptr;
    }
}

// Конструктор перемещения
Planet::Planet(Planet&& other) noexcept
    : name(other.name), mass(other.mass) {
    other.name = nullptr;
    other.mass = 0.0;
}

// Деструктор
Planet::~Planet() {
    delete[] name;
}

// Оператор присваивания (copy-and-swap)
Planet& Planet::operator=(const Planet& other) noexcept {
    std::swap(name, other.name);
    std::swap(mass, other.mass);
    return *this;
}

// Геттеры
const char* Planet::getName() const {
    return name ? name : "";
}

double Planet::getMass() const {
    return mass;
}

// Сеттеры
void Planet::setName(const char* newName) {
    delete[] name;
    if (newName) {
        name = new char[std::strlen(newName) + 1];
        std::strcpy(name, newName);
    } else {
        name = nullptr;
    }
}

void Planet::setMass(double newMass) {
    mass = newMass;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Planet& p) {
    os << "Planet: " << (p.name ? p.name : "Unknown")
       << ", Mass: " << p.mass << " Earth masses";
    return os;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& is, Planet& p) {
    char buffer[256];
    double m;

    std::cout << "Enter planet name: ";
    is >> buffer;
    std::cout << "Enter planet mass (Earth masses): ";
    is >> m;

    p.setName(buffer);
    p.setMass(m);

    return is;
}
