#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include "House.h"
#include "abstract_algorithm.h"
#include "MyAlgorithm.h"
#include "VacuumCleaner.h"
#include "MyBatteryMeter.h"
#include "MyWallSensor.h"
#include "MyDirtSensor.h"
#include "enums.h"
#include <fstream>


enum Status { FINISHED, WORKING, DEAD };


class MySimulator {
    private:
        House house;
        MyAlgorithm* algorithm;
        VacuumCleaner robot; 
        MyWallsSensor wallSensor;
        MyDirtSensor dirtSensor; 
        MyBatteryMeter batteryMeter;
        const std::string outputFilePath;
        std::vector<Step> stepsLog;
        Status status = WORKING;
        std::string houseFilePath;

    public:
        MySimulator();
        bool readHouseFile(const std::string& houseFilePath);
        void setAlgorithm(MyAlgorithm& algo);
        void run();
        void writeOutput() const;
        std::string getOutputFileName(const std::string& filePath) const;
        
        // print function - Debugging
        void printLocation();
        void printLayout();
        void printStepStatus();
        void printGraphStatus(int remainedSteps, int battery);
};

#endif // MYSIMULATOR_H

