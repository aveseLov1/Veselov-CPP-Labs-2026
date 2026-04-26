#include "city.hpp"
#include <cstring>
#include <iostream>

City::City()
    : Region(), foundationYear(0), budget(0.0), urbanDistrictsCount(0) {
    std::cout << "City() constructor called" << std::endl;
}

City::City(const char* name, double area, int population,
           const char* capital, int districts, const char* governor,
           int year, double budget, int urbanDistricts)
    : Region(name, area, population, capital, districts, governor)
    , foundationYear(year)
    , budget(budget)
    , urbanDistrictsCount(urbanDistricts) {

    std::cout << "City constructor called for: " << name << std::endl;
}

City::City(const City& other)
    : Region(other)
    , foundationYear(other.foundationYear)
    , budget(other.budget)
    , urbanDistrictsCount(other.urbanDistrictsCount) {

    std::cout << "City copy constructor called" << std::endl;
}

City::~City() {
    std::cout << "~City() destructor called" << std::endl;
}

City& City::operator=(const City& other) {
    std::cout << "City::operator= called" << std::endl;
    if (this != &other) {
        Region::operator=(other);
        foundationYear = other.foundationYear;
        budget = other.budget;
        urbanDistrictsCount = other.urbanDistrictsCount;
    }
    return *this;
}

void City::show() const {
    std::cout << "City: " << (getName() ? getName() : "Unknown")
              << ", Area: " << getArea() << " sq.km"
              << ", Population: " << getPopulation()
              << ", Capital: " << (capital ? capital : "Unknown")
              << ", Districts: " << districtsCount
              << ", Governor: " << (governor ? governor : "Unknown")
              << ", Founded: " << foundationYear
              << ", Budget: " << budget << " million rub"
              << ", Urban districts: " << urbanDistrictsCount
              << ", Density: " << calculateDensity() << " people/sq.km" << std::endl;
}

double City::calculateDensity() const {
    double baseDensity = Region::calculateDensity();
    // Города обычно имеют более высокую плотность
    return baseDensity * 1.2;
}
