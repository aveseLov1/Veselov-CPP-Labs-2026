#include "place.hpp"
#include "region.hpp"
#include "city.hpp"
#include "megapolis.hpp"
#include <iostream>
#include <cstring>

void showMenu() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "     PLACES MANAGEMENT SYSTEM" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Add Region" << std::endl;
    std::cout << "2. Add City" << std::endl;
    std::cout << "3. Add Megapolis" << std::endl;
    std::cout << "4. Show all places" << std::endl;
    std::cout << "5. Remove place by index" << std::endl;
    std::cout << "6. Clear all places" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Choice: ";
}

void addRegion() {
    char name[100];
    double area;
    int population;
    char capital[100];
    int districts;
    char governor[100];

    std::cin.ignore();
    std::cout << "\n--- Add New Region ---" << std::endl;
    std::cout << "Enter region name: ";
    std::cin.getline(name, 100);
    std::cout << "Enter area (sq.km): ";
    std::cin >> area;
    std::cout << "Enter population: ";
    std::cin >> population;
    std::cin.ignore();
    std::cout << "Enter capital city: ";
    std::cin.getline(capital, 100);
    std::cout << "Enter number of districts: ";
    std::cin >> districts;
    std::cin.ignore();
    std::cout << "Enter governor name: ";
    std::cin.getline(governor, 100);

    Region* region = new Region(name, area, population, capital, districts, governor);
    Place::addToContainer(region);
    std::cout << "Region added successfully!" << std::endl;
}

void addCity() {
    char name[100];
    double area;
    int population;
    char capital[100];
    int districts;
    char governor[100];
    int year;
    double budget;
    int urbanDistricts;

    std::cin.ignore();
    std::cout << "\n--- Add New City ---" << std::endl;
    std::cout << "Enter city name: ";
    std::cin.getline(name, 100);
    std::cout << "Enter area (sq.km): ";
    std::cin >> area;
    std::cout << "Enter population: ";
    std::cin >> population;
    std::cin.ignore();
    std::cout << "Enter capital status (city name): ";
    std::cin.getline(capital, 100);
    std::cout << "Enter number of districts: ";
    std::cin >> districts;
    std::cin.ignore();
    std::cout << "Enter mayor name: ";
    std::cin.getline(governor, 100);
    std::cout << "Enter foundation year: ";
    std::cin >> year;
    std::cout << "Enter budget (million rub): ";
    std::cin >> budget;
    std::cout << "Enter number of urban districts: ";
    std::cin >> urbanDistricts;

    City* city = new City(name, area, population, capital, districts, governor,
                          year, budget, urbanDistricts);
    Place::addToContainer(city);
    std::cout << "City added successfully!" << std::endl;
}

void addMegapolis() {
    char name[100];
    double area;
    int population;
    char capital[100];
    int districts;
    char governor[100];
    int year;
    double budget;
    int urbanDistricts;
    bool metro;
    int airports;
    double gdp;

    std::cin.ignore();
    std::cout << "\n--- Add New Megapolis ---" << std::endl;
    std::cout << "Enter megapolis name: ";
    std::cin.getline(name, 100);
    std::cout << "Enter area (sq.km): ";
    std::cin >> area;
    std::cout << "Enter population: ";
    std::cin >> population;
    std::cin.ignore();
    std::cout << "Enter capital status: ";
    std::cin.getline(capital, 100);
    std::cout << "Enter number of districts: ";
    std::cin >> districts;
    std::cin.ignore();
    std::cout << "Enter mayor name: ";
    std::cin.getline(governor, 100);
    std::cout << "Enter foundation year: ";
    std::cin >> year;
    std::cout << "Enter budget (million rub): ";
    std::cin >> budget;
    std::cout << "Enter number of urban districts: ";
    std::cin >> urbanDistricts;
    std::cout << "Has metro? (1 - Yes, 0 - No): ";
    std::cin >> metro;
    std::cout << "Enter number of airports: ";
    std::cin >> airports;
    std::cout << "Enter GDP (billion rub): ";
    std::cin >> gdp;

    Megapolis* megapolis = new Megapolis(name, area, population, capital, districts, governor,
                                          year, budget, urbanDistricts, metro, airports, gdp);
    Place::addToContainer(megapolis);
    std::cout << "Megapolis added successfully!" << std::endl;
}

int main() {
    int choice;

    std::cout << "================================================" << std::endl;
    std::cout << "PLACES MANAGEMENT SYSTEM - VARIANT 8" << std::endl;
    std::cout << "Inheritance hierarchy:" << std::endl;
    std::cout << "  Place (abstract)" << std::endl;
    std::cout << "     ↑" << std::endl;
    std::cout << "  Region" << std::endl;
    std::cout << "     ↑" << std::endl;
    std::cout << "  City" << std::endl;
    std::cout << "     ↑" << std::endl;
    std::cout << "  Megapolis" << std::endl;
    std::cout << "================================================" << std::endl;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                addRegion();
                break;
            case 2:
                addCity();
                break;
            case 3:
                addMegapolis();
                break;
            case 4:
                Place::print();
                break;
            case 5: {
                int index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                Place::remove(index);
                break;
            }
            case 6:
                Place::clear();
                std::cout << "All places cleared!" << std::endl;
                break;
            case 7:
                std::cout << "Exiting program..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    } while (choice != 7);

    Place::clear();
    std::cout << "Program terminated. Goodbye!" << std::endl;

    return 0;
}
