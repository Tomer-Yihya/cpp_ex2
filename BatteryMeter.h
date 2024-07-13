#include "Algorithm.h"
#include "House.h"
#include "Sensors.h"

class BatteryMeter {
    
    public:
        virtual ~BatteryMeter() {}
        virtual std::size_t getBatteryState() const = 0;
};