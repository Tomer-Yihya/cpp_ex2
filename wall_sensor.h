#ifndef WALL_SENSOR_H_
#define WALL_SENSOR_H_

#include "House.h"
#include "VacuumCleaner.h"
#include "enums.h"


class WallsSensor {
	
	private:
		const House* house;
		const VacuumCleaner* robot;

	public:
    	WallsSensor(const House* house, const VacuumCleaner* robot);
		virtual ~WallsSensor() {}
		virtual bool isWall(Direction d) const;
		//virtual bool isWall(Direction d) const = 0;

};

#endif  // WALL_SENSOR_H_

