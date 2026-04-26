#include "megapolis.hpp"
#include <cstring>
#include <iostream>

Megapolis::Megapolis()
    : City(), hasMetro(false), airportsCount(0), gdp(0.0),
      satelliteCities(nullptr), satellitesCount(0) {
    std::cout << "Megapolis() constructor called" << std::endl;
}

// Обычный конструктор
Megapolis::Megapolis(const char* name, double area, int population,
                     const char* capital, int districts, const char* governor,
                     int year, double budget, int urbanDistricts,
                     bool metro, int airports, double gdp)
    : City(name, area, population, capital, districts, governor,
           year, budget, urbanDistricts)
    , hasMetro(metro)
    , airportsCount(airports)
    , gdp(gdp)
    , satelliteCities(nullptr)
    , satellitesCount(0) {

    std::cout << "Megapolis constructor called for: " << name << std::endl;

    satelliteCities = new char*[3];
    satelliteCities[0] = new char[strlen("Korolev") + 1];
    strcpy(satelliteCities[0], "Korolev");
    satelliteCities[1] = new char[strlen("Mytishchi") + 1];
    strcpy(satelliteCities[1], "Mytishchi");
    satelliteCities[2] = new char[strlen("Lyubertsy") + 1];
    strcpy(satelliteCities[2], "Lyubertsy");
    satellitesCount = 3;
}

// ИСПРАВЛЕННЫЙ копирующий конструктор - правильный порядок!
Megapolis::Megapolis(const Megapolis& other)
    : City(other)
    , hasMetro(other.hasMetro)           // ← 1-е поле в классе
    , airportsCount(other.airportsCount) // ← 2-е поле в классе
    , gdp(other.gdp)                     // ← 3-е поле в классе
    , satelliteCities(nullptr)           // ← 4-е поле в классе
    , satellitesCount(other.satellitesCount) { // ← 5-е поле в классе

    std::cout << "Megapolis copy constructor called" << std::endl;

    if (other.satelliteCities && satellitesCount > 0) {
        satelliteCities = new char*[satellitesCount];
        for (int i = 0; i < satellitesCount; ++i) {
            satelliteCities[i] = new char[strlen(other.satelliteCities[i]) + 1];
            strcpy(satelliteCities[i], other.satelliteCities[i]);
        }
    }
}

Megapolis::~Megapolis() {
    std::cout << "~Megapolis() destructor called" << std::endl;
    if (satelliteCities) {
        for (int i = 0; i < satellitesCount; ++i) {
            delete[] satelliteCities[i];
        }
        delete[] satelliteCities;
    }
}

Megapolis& Megapolis::operator=(const Megapolis& other) {
    std::cout << "Megapolis::operator= called" << std::endl;
    if (this != &other) {
        City::operator=(other);

        if (satelliteCities) {
            for (int i = 0; i < satellitesCount; ++i) {
                delete[] satelliteCities[i];
            }
            delete[] satelliteCities;
        }

        hasMetro = other.hasMetro;
        airportsCount = other.airportsCount;
        gdp = other.gdp;
        satellitesCount = other.satellitesCount;

        if (other.satelliteCities && satellitesCount > 0) {
            satelliteCities = new char*[satellitesCount];
            for (int i = 0; i < satellitesCount; ++i) {
                satelliteCities[i] = new char[strlen(other.satelliteCities[i]) + 1];
                strcpy(satelliteCities[i], other.satelliteCities[i]);
            }
        } else {
            satelliteCities = nullptr;
        }
    }
    return *this;
}

void Megapolis::show() const {
    std::cout << "Megapolis: " << (getName() ? getName() : "Unknown")
              << ", Area: " << getArea() << " sq.km"
              << ", Population: " << getPopulation()
              << ", Capital: " << (getCapital() ? getCapital() : "Unknown")
              << ", Governor: " << (getGovernor() ? getGovernor() : "Unknown")
              << ", Founded: " << getFoundationYear()
              << ", Budget: " << getBudget() << " million rub"
              << ", Metro: " << (hasMetro ? "Yes" : "No")
              << ", Airports: " << airportsCount
              << ", GDP: " << gdp << " billion rub"
              << ", Satellite cities: " << satellitesCount
              << ", Density: " << calculateDensity() << " people/sq.km" << std::endl;
}

double Megapolis::calculateDensity() const {
    double baseDensity = City::calculateDensity();
    return baseDensity * 1.5;
}
