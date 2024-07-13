#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "AbstractAlgorithm.h"
#include "House.h"
#include "Sensors.h"
#include "Direction.h"
#include "WallsSensor.h"
#include "DirtSensor.h"
#include "BatteryMeter.h"
#include <cstddef>

class MyAlgorithm : public AbstractAlgorithm {
    
    private:
        std::size_t maxSteps;
        // Sensors and other attributes
    
    public:
        void setMaxSteps(std::size_t maxSteps) override;
        void setWallsSensor(const WallsSensor&) override;
        void setDirtSensor(const DirtSensor&) override;
        void setBatteryMeter(const BatteryMeter&) override;
        Step nextStep() override;

};

#endif // MYALGORITHM_H
