#ifndef BATTERY_METER_H_
#define BATTERY_METER_H_

#include "House.h"
#include "enums.h"
#include <cstddef>


class BatteryMeter {
	
	private:
			const House* house;

	public:
		BatteryMeter(const House* house);
		virtual ~BatteryMeter() {}
		virtual std::size_t getBatteryState() const;
		//virtual std::size_t getBatteryState() const = 0;

};


#endif  // BATTERY_METER_H_
