#ifndef DIRT_SENSOR_H_
#define DIRT_SENSOR_H_

#include "House.h"
#include "VacuumCleaner.h"
#include "enums.h"
#include "Coordinates.h"


class DirtSensor {
	
	private:
		const House* house;
		const VacuumCleaner* robot;


	public:
		DirtSensor(const House* house, const VacuumCleaner* robot);
		virtual ~DirtSensor() {}
		virtual int dirtLevel() const;
		//virtual int dirtLevel() const = 0;

};


#endif  // DIRT_SENSOR_H_
