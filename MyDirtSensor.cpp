#include "MyDirtSensor.h"


MyDirtSensor::MyDirtSensor(const House* house, const VacuumCleaner* robot) : house(house), robot(robot) {
    currLocation = house->getDockingCoordinates();
}


int MyDirtSensor::dirtLevel() const {
	
	Coordinates temp = robot->getCurrentLocation();
	char c = house->getLayoutVal(temp.getX(),temp.getY());
	int res = 0;
	if(c >='0' && c <='9') {
		res += c - '0';
	}

	return res;
}


void MyDirtSensor::move(Direction d) { 
    switch (d) {
        case Direction::North:
            currLocation = currLocation.getCoordinatesN();
            return;
        case Direction::South:
            currLocation = currLocation.getCoordinatesS();
            return;
        case Direction::West:
            currLocation = currLocation.getCoordinatesW();
            return;
        case Direction::East:
            currLocation = currLocation.getCoordinatesE();
            return;
    }
    
}

