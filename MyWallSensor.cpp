#include "MyWallSensor.h"


MyWallsSensor::MyWallsSensor(const House* house, const VacuumCleaner* robot) : 
    house(house), robot(robot) {
        currLocation = house->getDockingCoordinates();
    }


bool MyWallsSensor::isWall(Direction d) const {
    
    Coordinates temp = robot->getCurrentLocation();
    
    switch (d) {
        case Direction::North:
            temp = temp.getCoordinatesN();  // Coordinates(x,y-1)
            break;
        case Direction::East:
            temp = temp.getCoordinatesE();  // Coordinates(x+1,y)
            break;
        case Direction::South:
            temp = temp.getCoordinatesS();  // Coordinates(x,y+1)
            break;
        case Direction::West:
            temp = temp.getCoordinatesW();  // Coordinates(x-1,y)
            break;
    }
    
    bool res = house->getLayoutVal(temp.getX(), temp.getY()) == 'W';
	return res;
}


void MyWallsSensor::move(Direction d) { 
    
    switch (d) {
        case Direction::North:
            currLocation = currLocation.getCoordinatesN();
            break;
        case Direction::South:
            currLocation = currLocation.getCoordinatesS();
            break;
        case Direction::West:
            currLocation = currLocation.getCoordinatesW();
            break;
        case Direction::East:
            currLocation = currLocation.getCoordinatesE();
            break;
    }
}