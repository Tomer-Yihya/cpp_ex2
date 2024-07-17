#include "battery_meter.h"


BatteryMeter::BatteryMeter(const House* house) : house(house) {}

std::size_t BatteryMeter::getBatteryState() const {
    int res = house->getBattery();
    return (size_t)res;
}
