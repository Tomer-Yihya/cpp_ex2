#ifndef WALL_SENSOR_H_
#define WALL_SENSOR_H_

#include "House.h"
#include "enums.h"
#include "Coordinates.h"


class WallsSensor {
	
	private:
		const House* house;

	
	public:
    	WallsSensor(const House* house);
		virtual ~WallsSensor() {}
		virtual bool isWall(Direction d) const = 0;

};

#endif  // WALL_SENSOR_H_

