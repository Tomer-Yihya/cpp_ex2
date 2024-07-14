#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "abstract_algorithm.h"
#include "House.h"
#include "sensors.h"
#include "enums.h"
#include "battery_meter.h"
#include <cstddef>

class Algorithm : public AbstractAlgorithm {
public:
    Algorithm();
    virtual ~Algorithm();

    void setMaxSteps(std::size_t maxSteps) override;
    void setWallsSensor(const WallsSensor& sensor) override;
    void setDirtSensor(const DirtSensor& sensor) override;
    void setBatteryMeter(const BatteryMeter& meter) override;
    Step nextStep() override;

private:
    std::size_t maxSteps;
    const WallsSensor* wallsSensor;
    const DirtSensor* dirtSensor;
    const BatteryMeter* batteryMeter;
    // Add any additional private members and methods you need here
};

#endif // ALGORITHM_H__
