#include "MySimulator.h"
#include <iostream>


bool MySimulator::readHouseFile(const std::string& houseFilePath) {
    return house.loadFromFile(houseFilePath);
}

void MySimulator::setAlgorithm(MyAlgorithm& algo) {
    algorithm = &algo;
    // Initialize the algorithm with house settings
    algorithm->setMaxSteps(house.maxSteps);
    // Assume sensors are initialized here
    // algorithm->setWallsSensor(wallsSensor);
    // algorithm->setDirtSensor(dirtSensor);
    // algorithm->setBatteryMeter(batteryMeter);
}

void MySimulator::run() {
    // Simulation logic
    // Example: while some condition, call algorithm->nextStep()
    std::cout << "Simulation started." << std::endl;
}

