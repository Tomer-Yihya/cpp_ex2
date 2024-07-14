#include "algorithm.h"


Algorithm::Algorithm() : maxSteps(0), wallsSensor(nullptr), dirtSensor(nullptr), batteryMeter(nullptr) {}

Algorithm::~Algorithm() {}

void Algorithm::setMaxSteps(std::size_t maxSteps) {
    this->maxSteps = maxSteps;
}

void Algorithm::setWallsSensor(const WallsSensor& sensor) {
    this->wallsSensor = &sensor;
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
