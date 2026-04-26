#ifndef PLACE_H
#define PLACE_H

#include <iostream>

class Place {
protected:
    static Place** container;
    static int size;
    static int capacity;

    char* name;
    double area;
    int population;

public:
    Place();
    Place(const char* name, double area, int population);
    Place(const Place& other);
    virtual ~Place();

    Place& operator=(const Place& other);

    virtual void show() const = 0;
    virtual double calculateDensity() const = 0;

    static void addToContainer(Place* place);
    static void print();
    static void remove(int index);
    static void clear();
    static void expandContainer();

    const char* getName() const { return name; }
    double getArea() const { return area; }
    int getPopulation() const { return population; }
};

#endif
