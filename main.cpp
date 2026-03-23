#include "Planet.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

namespace {
    constexpr int INITIAL_SIZE = 10;
    constexpr int BUFFER_SIZE = 256;
}

// Прототипы функций
void showMenu();
void loadFromFile(Planet*& planets, int& size, int& capacity);
void saveToFile(const Planet* planets, int size);
void addPlanet(Planet*& planets, int& size, int& capacity);
void removePlanet(Planet*& planets, int& size);
void sortPlanets(Planet* planets, int size);
int findPlanet(const Planet* planets, int size);
void editPlanet(Planet* planets, int size);
void displayPlanets(const Planet* planets, int size);
void resizeArray(Planet*& planets, int& capacity, int newCapacity);

// Функция для расширения массива
void resizeArray(Planet*& planets, int& capacity, int newCapacity) {
    Planet* newArray = new Planet[newCapacity];
    int minSize = std::min(capacity, newCapacity);
    for (int i = 0; i < minSize; ++i) {
        newArray[i] = std::move(planets[i]);
    }
    delete[] planets;
    planets = newArray;
    capacity = newCapacity;
}

// Отображение меню
void showMenu() {
    std::cout << "\n===== PLANET DATABASE MENU =====\n";
    std::cout << "1. Load data from file\n";
    std::cout << "2. Save data to file\n";
    std::cout << "3. Add planet\n";
    std::cout << "4. Remove planet\n";
    std::cout << "5. Sort planets\n";
    std::cout << "6. Find planet\n";
    std::cout << "7. Edit planet\n";
    std::cout << "8. Display all planets\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

// Загрузка из файла
void loadFromFile(Planet*& planets, int& size, int& capacity) {
    char filename[BUFFER_SIZE];
    std::cout << "Enter filename to load: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    int newSize = 0;
    file >> newSize;
    file.ignore();

    if (newSize > capacity) {
        resizeArray(planets, capacity, newSize);
    }

    size = 0;
    for (int i = 0; i < newSize; ++i) {
        char name[BUFFER_SIZE];
        double mass;

        file.getline(name, BUFFER_SIZE);
        file >> mass;
        file.ignore();

        if (file.fail()) break;

        planets[size].setName(name);
        planets[size].setMass(mass);
        ++size;
    }

    file.close();
    std::cout << "Loaded " << size << " planets from " << filename << std::endl;
}

// Сохранение в файл
void saveToFile(const Planet* planets, int size) {
    char filename[BUFFER_SIZE];
    std::cout << "Enter filename to save: ";
    std::cin >> filename;

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot create file " << filename << std::endl;
        return;
    }

    file << size << std::endl;
    for (int i = 0; i < size; ++i) {
        file << planets[i].getName() << std::endl;
        file << planets[i].getMass() << std::endl;
    }

    file.close();
    std::cout << "Saved " << size << " planets to " << filename << std::endl;
}

// Добавление планеты
void addPlanet(Planet*& planets, int& size, int& capacity) {
    if (size >= capacity) {
        resizeArray(planets, capacity, capacity * 2);
        std::cout << "Array expanded to capacity " << capacity << std::endl;
    }

    std::cin >> planets[size];
    ++size;
    std::cout << "Planet added successfully.\n";
}

// Удаление планеты
void removePlanet(Planet*& planets, int& size) {
    if (size == 0) {
        std::cout << "No planets to remove.\n";
        return;
    }

    char name[BUFFER_SIZE];
    std::cout << "Enter name of planet to remove: ";
    std::cin >> name;

    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (std::strcmp(planets[i].getName(), name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cout << "Planet not found.\n";
        return;
    }

    // Сдвиг элементов
    for (int i = index; i < size - 1; ++i) {
        planets[i] = std::move(planets[i + 1]);
    }
    --size;

    std::cout << "Planet removed successfully.\n";
}

// Сортировка планет (по массе)
void sortPlanets(Planet* planets, int size) {
    if (size <= 1) {
        std::cout << "Not enough planets to sort.\n";
        return;
    }

    std::cout << "Sort by:\n";
    std::cout << "1. Name\n";
    std::cout << "2. Mass\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Пузырьковая сортировка по имени
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (std::strcmp(planets[j].getName(), planets[j + 1].getName()) > 0) {
                    std::swap(planets[j], planets[j + 1]);
                }
            }
        }
        std::cout << "Sorted by name.\n";
    } else if (choice == 2) {
        // Пузырьковая сортировка по массе
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (planets[j].getMass() > planets[j + 1].getMass()) {
                    std::swap(planets[j], planets[j + 1]);
                }
            }
        }
        std::cout << "Sorted by mass.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

// Поиск планеты
int findPlanet(const Planet* planets, int size) {
    if (size == 0) {
        std::cout << "No planets to search.\n";
        return -1;
    }

    char name[BUFFER_SIZE];
    std::cout << "Enter planet name to find: ";
    std::cin >> name;

    for (int i = 0; i < size; ++i) {
        if (std::strcmp(planets[i].getName(), name) == 0) {
            std::cout << "Found: " << planets[i] << std::endl;
            return i;
        }
    }

    std::cout << "Planet not found.\n";
    return -1;
}

// Редактирование планеты
void editPlanet(Planet* planets, int size) {
    int index = findPlanet(planets, size);
    if (index == -1) return;

    std::cout << "Editing planet: " << planets[index] << std::endl;
    std::cout << "Enter new data:\n";
    std::cin >> planets[index];
    std::cout << "Planet updated successfully.\n";
}

// Отображение всех планет
void displayPlanets(const Planet* planets, int size) {
    if (size == 0) {
        std::cout << "No planets to display.\n";
        return;
    }

    std::cout << "\n===== PLANET LIST =====\n";
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << ". " << planets[i] << std::endl;
    }
    std::cout << "Total: " << size << " planets\n";
}

// Главная функция
int main() {
    Planet* planets = new Planet[INITIAL_SIZE];
    int size = 0;
    int capacity = INITIAL_SIZE;
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                loadFromFile(planets, size, capacity);
                break;
            case 2:
                saveToFile(planets, size);
                break;
            case 3:
                addPlanet(planets, size, capacity);
                break;
            case 4:
                removePlanet(planets, size);
                break;
            case 5:
                sortPlanets(planets, size);
                break;
            case 6:
                findPlanet(planets, size);
                break;
            case 7:
                editPlanet(planets, size);
                break;
            case 8:
                displayPlanets(planets, size);
                break;
            case 9:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    delete[] planets;
    return 0;
}
