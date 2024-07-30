#ifndef MY_WALL_SENSOR_H_
#define MY_WALL_SENSOR_H_

#include "House.h"
#include "VacuumCleaner.h"
#include "wall_sensor.h"


class MyWallsSensor : public WallsSensor{
	
	private:
		const House* house;
		const VacuumCleaner* robot;
		Coordinates currLocation;


	public:
		MyWallsSensor(const House* house, const VacuumCleaner* robot);
		virtual ~MyWallsSensor() {}
		virtual bool isWall(Direction d) const override;
		void move(Direction d);

};


#endif  // MY_WALL_SENSOR_H_

