#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
#include <stack>
#include "abstract_algorithm.h"
#include "House.h"
#include "vacuumCleaner.h"
#include "battery_meter.h"
#include "wall_sensor.h"
#include "dirt_sensor.h"
#include "enums.h"
#include "Coordinates.h"


class Algorithm : public AbstractAlgorithm {
    
    private:
        const House* house;
        const VacuumCleaner* robot;
        const WallsSensor* wallSensor;
        const DirtSensor* dirtSensor;
        const BatteryMeter* batteryMeter;
        int remainedSteps;
        int totalDirt;
        std::size_t maxSteps;

        std::vector<std::string> actions = {"MOVE", "CLEAN", "CHARGE", "FINISH"};
        bool isCargging = false;
        bool isReturningToDocking = false;
        int moveCounter = 0;
        std::stack<Direction> pathToDocking; // LIFO queue.
    
    public:
        Algorithm();
        virtual ~Algorithm();
        void setMaxSteps(std::size_t maxSteps) override;
        void setWallsSensor(const WallsSensor& sensor) override;
        void setDirtSensor(const DirtSensor& sensor) override;
        void setBatteryMeter(const BatteryMeter& meter) override;
        Step nextStep() override;


        void  initAlgo(House& house, VacuumCleaner& robot, WallsSensor& wallSensor, 
                  DirtSensor& dirtSensor, BatteryMeter& batteryMeter);
        
        int minDistanceToDockingStation();

        Coordinates getCurrLocation() const;
        int getRemainedSteps();
        int getToatalDirt();

        bool isAtDocking() const;
        bool isCharged() const;
        void decreaseRemainedSteps();
        void decreaseTotalDirt();

        std::string chooseAction();
        Direction chooseDirection();
        bool nextStepDirty(Direction d);
        void emptyQueue();
        void printQueue();
        int getQueueSize();

};

#endif // ALGORITHM_H
