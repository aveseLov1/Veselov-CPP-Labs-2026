#ifndef MEGAPOLIS_H
#define MEGAPOLIS_H

#include "city.hpp"

class Megapolis : public City {
private:
    bool hasMetro;           // ← 1-е поле (порядок важен!)
    int airportsCount;       // ← 2-е поле
    double gdp;              // ← 3-е поле
    char** satelliteCities;  // ← 4-е поле
    int satellitesCount;     // ← 5-е поле

public:
    Megapolis();
    Megapolis(const char* name, double area, int population,
              const char* capital, int districts, const char* governor,
              int year, double budget, int urbanDistricts,
              bool metro, int airports, double gdp);
    Megapolis(const Megapolis& other);
    ~Megapolis();

    Megapolis& operator=(const Megapolis& other);

    void show() const override;
    double calculateDensity() const override;
};

#endif
