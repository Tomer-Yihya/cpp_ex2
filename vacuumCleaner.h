#ifndef VACUUMCLEANER_H
#define VACUUMCLEANER_H

#include "House.h"
#include "enums.h"
#include "Coordinates.h"
#include <vector>
#include "battery_meter.h"



class VacuumCleaner {
    private:
        House* house;
        Coordinates currentLocation;
        BatteryMeter battery;

    public:
        // constructor
        VacuumCleaner(House* house);
        
        // functions
        void charge();
        void move(Direction d);
        void clean();
        bool spotIsDirty(char ch);
        bool isCharged() const;

        // getters
        int getBatteryLevel() const;
        Coordinates getCurrentLocation() const;
        //void setCurrentLocation(int x, int y);
        //void setCurrentLocation(const Coordinates& coor);
};

#endif
