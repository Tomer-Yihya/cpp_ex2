#include "VacuumCleaner.h"


// constructor
VacuumCleaner::VacuumCleaner(House* house) {
    this->house = house;
    battery = house->getBattery(); 
    batteryCapacity = house->getBatteryCapacity();
    currentLocation = house->getDockingCoordinates();
}


void VacuumCleaner::charge() {
    if (battery < batteryCapacity) {
        battery += batteryCapacity / 20;
        
        // edge case
        if (battery > batteryCapacity) {
            battery = batteryCapacity;
        }
    }
}


void VacuumCleaner::move(Direction d) {
    if (battery <= 0) { return; }

    switch (d) {
        case Direction::North:
            currentLocation = currentLocation.getCoordinatesN();
            break;
        case Direction::East:
            currentLocation = currentLocation.getCoordinatesE();
            break;
        case Direction::South:
            currentLocation = currentLocation.getCoordinatesS();
            break;
        case Direction::West:
            currentLocation = currentLocation.getCoordinatesW();
            break;
    }
    battery--;
}


void VacuumCleaner::clean() {
    house->decreseDirtLevel(currentLocation.getY(),currentLocation.getX());
    battery--;
}


bool VacuumCleaner::spotIsDirty(char ch) {
    int dirtLevel = (ch - '0');
    return dirtLevel > 0 && dirtLevel <= 9;
}


int VacuumCleaner::getBatteryLevel() const {
    return battery;
}


int VacuumCleaner::getBatteryCapacity() const {
    return batteryCapacity;
}


Coordinates VacuumCleaner::getCurrentLocation() const {
    return currentLocation;
}

