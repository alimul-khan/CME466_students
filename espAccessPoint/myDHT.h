#ifndef MYDH_H
#define MYDHT_H

#include <Arduino.h>

extern float humidity;
extern float temperature;
extern float temperatureF;

void initDHT();
void getTempHumidity();

#endif
