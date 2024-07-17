#include "Algorithm.h"


Algorithm::Algorithm() : maxSteps(0), wallSensor(nullptr), dirtSensor(nullptr), batteryMeter(nullptr) {}

Algorithm::~Algorithm() {}


void Algorithm::initAlgo(const House& house) {
    setMaxSteps(house.getMaxStepsAllowed());
    setWallsSensor(wallSensor(&house)); 
    setDirtSensor(DirtSensor(&house));  
    setBatteryMeter(BatteryMeter(&house));
    //setBatteryMeter(BatteryMeter(house.getBatteryCapacity()));
}



void Algorithm::setMaxSteps(std::size_t maxSteps) {
    this->maxSteps = maxSteps;
}

void Algorithm::setWallsSensor(const WallsSensor& sensor) {
    this->wallSensor = &sensor;
}

void Algorithm::setDirtSensor(const DirtSensor& sensor) {
    this->dirtSensor = &sensor;
}

void Algorithm::setBatteryMeter(const BatteryMeter& meter) {
    this->batteryMeter = &meter;
}




Step Algorithm::nextStep() {
    // Add your implementation here
    return Step();  // Return a default step for now
}
