#ifndef SENSORS_H
#define SENSORS_H


#include "enums.h"
#include "dirt_sensor.h"
#include "wall_sensor.h"
#include "Battery_meter.h"


class Sensors : public DirtSensor, public WallsSensor {
    public:
        Sensors();
        virtual ~Sensors();

        // DirtSensor implementation
        int dirtLevel() const override;

        // WallsSensor implementation
        bool isWall(Direction d) const override;
        
        // Additional members and methods can be added here
};

#endif // SENSORS_H_
