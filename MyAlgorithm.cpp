#include "House.h"
#include "MyAlgorithm.h"

void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    this->maxSteps = maxSteps;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& sensor) {
    // Initialize walls sensor
}

void MyAlgorithm::setDirtSensor(const DirtSensor& sensor) {
    // Initialize dirt sensor
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& meter) {
    // Initialize battery meter
}

Step MyAlgorithm::nextStep() {
    // Implement algorithm to determine next step
    return Step::Stay;
}
