#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "abstract_algorithm.h"
#include "Graph.h"
#include "MyWallSensor.h"
#include "MyDirtSensor.h"
#include "VacuumCleaner.h"
#include "Coordinates.h"
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <limits>
#include <utility>
#include <map>


class MyAlgorithm : public AbstractAlgorithm {
    
    private:
        // objects for the algorithm
        Graph graph;
        VacuumCleaner* robot;
        const WallsSensor* wallSensor;
        const DirtSensor* dirtSensor;
        const BatteryMeter* batteryMeter;
        // Coordinates lastCleannigSpot;
        
        // class variables
        int remainedSteps;
        int totalDirt;
        std::size_t maxSteps;
        
        // Flags
        bool robotIsDead = false;     // A flag that signals if the robot is dead
        bool isCargging = false;      // A flag that signals that the robot is chrgging
        
        //path between points in the graph
        std::vector<Direction> pathToDocking;   // steps of the way back to the Docking station.
        std::vector<Direction> pathToDirtySpot; // steps to the nearest dirty code
        std::vector<Direction> pathToNewSpot; // steps to the nearest new code
        
        // steps history
        std::vector<char> stepsListLog;            // all the steps performed by the algorithm

    public:
        MyAlgorithm();
        virtual ~MyAlgorithm();
        void setMaxSteps(std::size_t maxSteps) override;
        void setWallsSensor(const WallsSensor& sensor) override;
        void setDirtSensor(const DirtSensor& sensor) override;
        void setBatteryMeter(const BatteryMeter& meter) override;
        void setStepsAndTotalDirt(int steps, int dirt);
        Step nextStep() override;
        void addWalls();
        Step returningToDocking();
        Step returningToClean();
        Step goToNewSpot();
        void initAlgo(VacuumCleaner& robot, WallsSensor& wallSensor, DirtSensor& dirtSensor, BatteryMeter& batteryMeter);
        
        // A shadow of the robot's movement at home
        void move(Step step);
        Coordinates moveCoordinates (Coordinates coor, Direction d);
        
        // BFS function for minimum steps until next spot
        int minDistanceToDockingStation();
        int minDistanceToDirtySpot();
        int minDistanceToNewSpot();

        // getters function
        Coordinates getCurrLocation() const;
        int getRemainedSteps();
        int getToatalDirt();
        char getCharFromStepsLog(int index);
        int getStepsLogSize();
        
        void decreaseRemainedSteps();
        void decreaseTotalDirt();

        bool isBatteryLow(int battery, int dist_from_docking);
        bool isAtDocking() const;
        bool isCharged() const;
        bool validLocation(Coordinates coor) const;
        bool locationIsDirty(Coordinates coor) const;


        Step convertDirectionToStep(Direction d);
        Direction convertStepToDirection(Step s);
        char convertStepToChar(Step s);

        // for Debugging
        void printGraph();
        void printStepsLog();
        void printPathToDocking();
        void printPathToDirtySpot();
};

#endif // ALGORITHM_H
