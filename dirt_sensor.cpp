#include "House.h"
#include "enums.h"
#include "dirt_sensor.h"

DirtSensor::DirtSensor(const House* house) : house(house) {}

int DirtSensor::dirtLevel() const {
	
	Coordinates temp = house->getCurrLocation();
	char c = house->getLayoutVal(temp.getX(),temp.getY());
	int res = 0;
	if(c >='0' && c <='9') {
		res += c - '0';
	}
	return res;
}

