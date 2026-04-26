#ifndef CITY_H
#define CITY_H

#include "region.hpp"

class City : public Region {
private:
    int foundationYear;
    double budget;
    int urbanDistrictsCount;

public:
    City();
    City(const char* name, double area, int population,
         const char* capital, int districts, const char* governor,
         int year, double budget, int urbanDistricts);
    City(const City& other);
    ~City();

    City& operator=(const City& other);

    void show() const override;
    double calculateDensity() const override;

    // ДОБАВЛЕНЫ getter'ы для доступа из Megapolis
    int getFoundationYear() const { return foundationYear; }
    double getBudget() const { return budget; }
    int getUrbanDistrictsCount() const { return urbanDistrictsCount; }
};

#endif
