#include "region.hpp"
#include <cstring>
#include <iostream>

Region::Region() : Place(), capital(nullptr), districtsCount(0), governor(nullptr) {
    std::cout << "Region() constructor called" << std::endl;
}

Region::Region(const char* name, double area, int population,
               const char* capital, int districts, const char* governor)
    : Place(name, area, population), districtsCount(districts) {
    std::cout << "Region constructor called for: " << name << std::endl;
    if (capital) {
        this->capital = new char[strlen(capital) + 1];
        strcpy(this->capital, capital);
    } else {
        this->capital = nullptr;
    }
    if (governor) {
        this->governor = new char[strlen(governor) + 1];
        strcpy(this->governor, governor);
    } else {
        this->governor = nullptr;
    }
}

Region::Region(const Region& other)
    : Place(other), districtsCount(other.districtsCount) {
    std::cout << "Region(const Region&) copy constructor called" << std::endl;
    if (other.capital) {
        capital = new char[strlen(other.capital) + 1];
        strcpy(capital, other.capital);
    } else {
        capital = nullptr;
    }
    if (other.governor) {
        governor = new char[strlen(other.governor) + 1];
        strcpy(governor, other.governor);
    } else {
        governor = nullptr;
    }
}

Region::~Region() {
    std::cout << "~Region() destructor called" << std::endl;
    if (capital) {
        delete[] capital;
    }
    if (governor) {
        delete[] governor;
    }
}

Region& Region::operator=(const Region& other) {
    std::cout << "Region::operator= called" << std::endl;
    if (this != &other) {
        Place::operator=(other);
        if (capital) {
            delete[] capital;
        }
        if (governor) {
            delete[] governor;
        }
        districtsCount = other.districtsCount;
        if (other.capital) {
            capital = new char[strlen(other.capital) + 1];
            strcpy(capital, other.capital);
        } else {
            capital = nullptr;
        }
        if (other.governor) {
            governor = new char[strlen(other.governor) + 1];
            strcpy(governor, other.governor);
        } else {
            governor = nullptr;
        }
    }
    return *this;
}

void Region::show() const {
    std::cout << "Region: " << (name ? name : "Unknown")
              << ", Area: " << area << " sq.km"
              << ", Population: " << population
              << ", Capital: " << (capital ? capital : "Unknown")
              << ", Districts: " << districtsCount
              << ", Governor: " << (governor ? governor : "Unknown")
              << ", Density: " << calculateDensity() << " people/sq.km" << std::endl;
}

double Region::calculateDensity() const {
    if (area > 0) {
        return population / area;
    }
    return 0;
}
