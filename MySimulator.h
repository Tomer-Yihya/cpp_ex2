#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include "House.h"
#include "abstract_algorithm.h"
#include "Algorithm.h"
#include "vacuumCleaner.h"
#include "battery_meter.h"
#include "wall_sensor.h"
#include "dirt_sensor.h"
#include "enums.h"
#include <vector>
#include <string>
#include "Coordinates.h"
#include <iostream>
#include <fstream>


enum Status { FINISHED, WORKING, DEAD };


class MySimulator {
    private:
        House house;
        Algorithm* algorithm;
        VacuumCleaner robot; 
        WallsSensor wallSensor;
        DirtSensor dirtSensor; 
        BatteryMeter batteryMeter;
        const std::string outputFilePath;
        std::vector<Step> stepsLog;
        Status status = WORKING;

    public:
        MySimulator();
        bool readHouseFile(const std::string& houseFilePath);
        void setAlgorithm(Algorithm& algo);
        void run();

        void writeOutput(std::string outputFilePath) const;
        
        // print function - Debugging
        void printLocation();
        void printLayout();
        void printStepStatus();
};

#endif // MYSIMULATOR_H

