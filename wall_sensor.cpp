#include "wall_sensor.h"


WallsSensor::WallsSensor(const House* house) : house(house) {}

bool WallsSensor::isWall(Direction d) const {
	
	Coordinates temp = house->getCurrLocation();
	switch (d) {
			case (Direction::North):
				temp = temp.getCoordinatesN(); // Coordinates(x,y-1)
				break;;

			case (Direction::East):
				temp = temp.getCoordinatesE(); // Coordinates(x+1,y)
				break;

			case (Direction::South):
				temp = temp.getCoordinatesS(); // Coordinates(x,y+1)
				break;

			case (Direction::West):
				temp = temp.getCoordinatesW(); // Coordinates(x-1,y)
				break;
	}
	//return (house->getLayoutVal(temp.getX(),temp.getY()) == 'W');
	bool res = house->getLayoutVal(temp.getX(),temp.getY()) == 'W';
	return res;
}

