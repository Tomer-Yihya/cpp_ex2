#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithm>
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
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <map>


class Algorithm : public AbstractAlgorithm {
    
    private:
        // objects for the algorithm
        const House* house;
        const VacuumCleaner* robot;
        const WallsSensor* wallSensor;
        const DirtSensor* dirtSensor;
        const BatteryMeter* batteryMeter;
        
        // class variables
        int remainedSteps;
        int totalDirt;
        std::size_t maxSteps;
        
        // Flags
        bool robotIsDead = false;          // A flag that signals if the robot is dead
        bool isCargging = false;           // A flag that signals that the robot is chrgging
        bool isReturningToDocking = false; // A flag that signals that the robot is on its way to the Docking station
        bool goToDirtySpot = false;        // A flag that signals that the robot is on its way to clean
        
        //paths between points in the house layout
        std::vector<Direction> pathToDocking;   // steps of the way back to the Docking station.
        std::vector<Direction> pathToDirtySpot; // steps to the nearest dirty code
        
        // steps history
        std::vector<char> stepsListLog;            // all the steps performed by the algorithm

    public:
        Algorithm();
        virtual ~Algorithm();
        void setMaxSteps(std::size_t maxSteps) override;
        void setWallsSensor(const WallsSensor& sensor) override;
        void setDirtSensor(const DirtSensor& sensor) override;
        void setBatteryMeter(const BatteryMeter& meter) override;
        Step nextStep() override;
        void  initAlgo(House& house, VacuumCleaner& robot, WallsSensor& wallSensor, DirtSensor& dirtSensor, BatteryMeter& batteryMeter);
        
        // BFS function for minimum steps until next spot
        int minDistanceToDockingStation();
        int minDistanceToDirtySpot();

        // getters function
        Coordinates getCurrLocation() const;
        int getRemainedSteps();
        int getToatalDirt();
        
        void decreaseRemainedSteps();
        void decreaseTotalDirt();

        bool isBatteryLow(int battery, int dist_from_docking, int dist_from_dirty_spot);
        bool isAtDocking() const;
        bool isCharged() const;
        bool validLocation(int x, int y) const;
        bool locationIsDirty(int x, int y) const;

        Step chooseDirection();
        Step convertDirectionToStep(Direction d);
        Direction convertStepToDirection(Step s);
        char convertStepToChar(Step s);

        // for Debugging
        void printPathToDocking();
        void printPathToDirtySpot();
};

#endif // ALGORITHM_H
