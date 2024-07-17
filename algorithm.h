#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "abstract_algorithm.h"
#include "House.h"
//#include "Robot.h"
#include "battery_meter.h"
#include "wall_sensor.h"
#include "dirt_sensor.h"
#include "enums.h"
#include <vector>
#include <string>


class Algorithm : public AbstractAlgorithm {
    
    private:
        //Robot robot;
        const House *house;
        std::size_t maxSteps;
        const WallsSensor* wallSensor;
        const DirtSensor* dirtSensor;
        const BatteryMeter* batteryMeter;
        
    
    public:
        Algorithm();
        virtual ~Algorithm();
        void setMaxSteps(std::size_t maxSteps) override;
        void setWallsSensor(const WallsSensor& sensor) override;
        void setDirtSensor(const DirtSensor& sensor) override;
        void setBatteryMeter(const BatteryMeter& meter) override;
        Step nextStep() override;

        void initAlgo(const House& house);

};



#endif // ALGORITHM_H
