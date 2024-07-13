#include "Algorithm.h"
#include "House.h"
#include "Sensors.h"
#include "Direction.h"
#include "DirtSensor.h"


class DirtSensor {
    
    public:
        virtual ~DirtSensor() {}
        virtual int dirtLevel() const = 0;
};