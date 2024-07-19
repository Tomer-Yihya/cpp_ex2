#include "battery_meter.h"

BatteryMeter::BatteryMeter(int batteryCapacity) : batteryCapacity(batteryCapacity), battery(batteryCapacity)
{}

std::size_t BatteryMeter::getBatteryState() const {
    return static_cast<std::size_t>(battery);
}

void BatteryMeter::increaseBattery() {
    if (battery < batteryCapacity) {
        battery += batteryCapacity / 20;
        // edge case
        if (battery > batteryCapacity) {
            battery = batteryCapacity;
        }
    }
}

void BatteryMeter::decreaseBattery() {
    battery--;
}

bool BatteryMeter::isCharged() const {
    return battery == batteryCapacity;
}

void BatteryMeter::charge() {
    if (battery < batteryCapacity) {
        battery += batteryCapacity / 20;

        // edge case
        if (battery > batteryCapacity) {
            battery = batteryCapacity;
        }
    }
}
