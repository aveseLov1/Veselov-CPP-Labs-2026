#include "place.hpp"
#include <cstring>
#include <iostream>

Place** Place::container = nullptr;
int Place::size = 0;
int Place::capacity = 0;

Place::Place() : name(nullptr), area(0.0), population(0) {
    std::cout << "Place() constructor called" << std::endl;
}

Place::Place(const char* name, double area, int population)
    : area(area), population(population) {
    std::cout << "Place(const char*, double, int) constructor called" << std::endl;
    if (name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    } else {
        this->name = nullptr;
    }
}

Place::Place(const Place& other)
    : area(other.area), population(other.population) {
    std::cout << "Place(const Place&) copy constructor called" << std::endl;
    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    } else {
        name = nullptr;
    }
}

Place::~Place() {
    std::cout << "~Place() destructor called" << std::endl;
    if (name) {
        delete[] name;
    }
}

Place& Place::operator=(const Place& other) {
    std::cout << "Place::operator= called" << std::endl;
    if (this != &other) {
        if (name) {
            delete[] name;
        }
        area = other.area;
        population = other.population;
        if (other.name) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        } else {
            name = nullptr;
        }
    }
    return *this;
}

void Place::expandContainer() {
    int newCapacity = (capacity == 0) ? 2 : capacity * 2;
    Place** newContainer = new Place*[newCapacity];

    for (int i = 0; i < size; ++i) {
        newContainer[i] = container[i];
    }

    if (container) {
        delete[] container;
    }

    container = newContainer;
    capacity = newCapacity;

    std::cout << "Container expanded to capacity: " << capacity << std::endl;
}

void Place::addToContainer(Place* place) {
    std::cout << "\n--- addToContainer ---" << std::endl;
    std::cout << "Current size: " << size << ", capacity: " << capacity << std::endl;

    if (size == capacity) {
        expandContainer();
    }

    container[size] = place;
    size++;

    std::cout << "Added. New size: " << size << ", capacity: " << capacity << std::endl;
}

void Place::print() {
    if (size == 0) {
        std::cout << "Container is empty" << std::endl;
        return;
    }

    std::cout << "\n=== All Places (" << size << " total) ===" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "Index " << i << ": ";
        container[i]->show();
    }
    std::cout << std::endl;
}

void Place::remove(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Invalid index! Index must be between 0 and " << size - 1 << std::endl;
        return;
    }

    std::cout << "\n--- remove ---" << std::endl;
    std::cout << "Removing place at index " << index << std::endl;

    delete container[index];

    for (int i = index; i < size - 1; ++i) {
        container[i] = container[i + 1];
    }

    size--;

    std::cout << "Removed. New size: " << size << ", capacity: " << capacity << std::endl;
}

void Place::clear() {
    std::cout << "\n--- clear ---" << std::endl;

    for (int i = 0; i < size; ++i) {
        delete container[i];
    }

    if (container) {
        delete[] container;
        container = nullptr;
    }

    size = 0;
    capacity = 0;
    std::cout << "Container cleared" << std::endl;
}
