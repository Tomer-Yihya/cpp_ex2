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
        enum Status { FINISHED, WORKING, DEAD };
        Status status = WORKING;

    public:
        MySimulator();
        bool readHouseFile(const std::string& houseFilePath);
        void setAlgorithm(Algorithm& algo);
        void run();

        // print function - Debugging
        void printLocation();
        void printLayout();
        void printStepStatus();


        void writeOutput(std::string outputFilePath) const;
};

#endif // MYSIMULATOR_H

