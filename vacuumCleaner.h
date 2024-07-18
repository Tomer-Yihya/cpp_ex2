#ifndef VACUUMCLEANER_H
#define VACUUMCLEANER_H

#include "House.h"
#include "enums.h"
#include "Coordinates.h"
#include <vector>



class VacuumCleaner {
    private:
        House* house;
        int battery;
        int batteryCapacity;
        Coordinates currentLocation;

    public:
        // constructor
        VacuumCleaner(House* house);
        
        // functions
        void charge();
        void move(Direction d);
        void clean();
        bool spotIsDirty(char ch);

        // getters
        int getBatteryLevel() const;
        int getBatteryCapacity() const;
        Coordinates getCurrentLocation() const;
};

#endif
