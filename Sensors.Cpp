
#include "sensors.h"
#include "House.h"

Sensors::Sensors() {
    // Constructor implementation
}

Sensors::~Sensors() {
    // Destructor implementation
}

int Sensors::dirtLevel() const {
    // Implementation of dirtLevel method
    return 0; // Placeholder return value
}

bool Sensors::isWall(Direction d) const {
    
    /*/switch (d) 
    {
    case ("North"):
        res = (layout[getCurrX()][getCurrY()-1] == 'W');
        return true;
    
    case ("South"):
        res = (getLayout()[getCurrX()][getCurrY()+1] == 'W');
        return true;
    
    case ("East"):
        res = (getLayout()[getCurrX()+1][getCurrY()] == 'W');
        return true;

    case ("West"):
        res = (getLayout()[getCurrX()-1][getCurrY()] == 'W');
        return true;

    default:
        return false;
    }:
    /**/
    return false; 
}
