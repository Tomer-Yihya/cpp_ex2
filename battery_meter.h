#ifndef BATTERY_METER_H_
#define BATTERY_METER_H_

#include "House.h"
#include "enums.h"
#include <cstddef>


class BatteryMeter {

	private:
		int battery;
		int batteryCapacity;

	public:
		BatteryMeter(int batteryCapacity);
		virtual ~BatteryMeter() {}
		virtual std::size_t getBatteryState() const;
		//virtual std::size_t getBatteryState() const = 0;
		void charge();
		void increaseBattery();
		void decreaseBattery();
		bool isCharged() const;
};

#endif  // BATTERY_METER_H_
