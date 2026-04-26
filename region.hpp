#ifndef REGION_H
#define REGION_H

#include "place.hpp"

class Region : public Place {
protected:
    char* capital;
    int districtsCount;
    char* governor;

public:
    Region();
    Region(const char* name, double area, int population,
           const char* capital, int districts, const char* governor);
    Region(const Region& other);
    virtual ~Region();

    Region& operator=(const Region& other);

    void show() const override;
    double calculateDensity() const override;

    // getter'ы
    const char* getCapital() const { return capital; }
    int getDistrictsCount() const { return districtsCount; }
    const char* getGovernor() const { return governor; }
};

#endif
