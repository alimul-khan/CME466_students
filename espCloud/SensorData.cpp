#include "SensorData.h"
#include <cstdlib>

float generateTemperature() {
    return 10.00 + (rand() % 4300) / 100.0; // Random temp (10.00 - 53.00)
}

float generateHumidity() {
    return 20.00 + (rand() % 6100) / 100.0; // Random humidity (20.00 - 81.00)
}
