#include "MyBatteryMeter.h"

MyBatteryMeter::MyBatteryMeter(int batteryCapacity) : batteryCapacity(batteryCapacity), battery(batteryCapacity) {}


std::size_t MyBatteryMeter::getBatteryState() const {
    return static_cast<std::size_t>(battery);
}


void MyBatteryMeter::increaseBattery() {
    if (battery < batteryCapacity) {
        battery += batteryCapacity / 20;
        // edge case
        if (battery > batteryCapacity) {
            battery = batteryCapacity;
        }
    }
}


void MyBatteryMeter::decreaseBattery() {
    battery--;
}


bool MyBatteryMeter::isCharged() const {
    return battery == batteryCapacity;
}


void MyBatteryMeter::charge() {
    if (battery < batteryCapacity) {
        battery += (double)batteryCapacity / 20;
        // edge case
        if (battery > batteryCapacity) {
            battery = batteryCapacity;
        }
    }
    std::cout << "battery = " << battery << std::endl;
}

