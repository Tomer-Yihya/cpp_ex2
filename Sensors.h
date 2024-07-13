#ifndef SENSORS_H
#define SENSORS_H


#include "Direction.h"
#include "WallsSensor.h"
#include "DirtSensor.h"
#include "BatteryMeter.h"



class ConcreteWallsSensor : public WallsSensor {
    public:
        bool isWall(Direction d) const override;
};

class ConcreteDirtSensor : public DirtSensor {
    public:
        int dirtLevel() const override;
};

class ConcreteBatteryMeter : public BatteryMeter {
    public:
        std::size_t getBatteryState() const override;
};

#endif // SENSORS_H
