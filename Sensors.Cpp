#include "Sensors.h"
#include "House.h"

bool ConcreteWallsSensor::isWall(Direction d) const {
    //enum class Direction { North, East, South, West };
    bool res = false;
    switch (d) 
    {
    case ("North"):
        res = (getLayout()[getCurrX()][getCurrY()-1] == 'W');
        break;
    
    case ("South"):
        res = (getLayout()[getCurrX()][getCurrY()+1] == 'W');
        break;
    
    case ("East"):
        res = (getLayout()[getCurrX()+1][getCurrY()] == 'W');
        break;

    case ("West"):
        res = (getLayout()[getCurrX()-1][getCurrY()] == 'W');
        break;

    default:
        return res;
        break;
    }:
    
}

int ConcreteDirtSensor::dirtLevel() const {
    return getLayout()[getCurrX()][getCurrY()];
}

std::size_t ConcreteBatteryMeter::getBatteryState() const {
    return getBattery();
}

