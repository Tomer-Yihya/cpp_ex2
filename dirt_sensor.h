#ifndef DIRT_SENSOR_H_
#define DIRT_SENSOR_H_

#include "House.h"
#include "enums.h"
#include "dirt_sensor.h"


class DirtSensor {
public:
	virtual ~DirtSensor() {}
	virtual int dirtLevel() const = 0;
};

#endif  // DIRT_SENSOR_H_
