#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "DHT.h"
#include "HTU21D.h"
#include "Adafruit_BMP280.h"

/*
 * Makes measurement with DHT22 sensor
 *
 * @arg data     Array with measurement results
 * @arg isInside Flag signifying where sensor is
*/
void dhtRead(float data[], bool isInside);

/*
 * Makes measurement with HTU21Dsensor
 *
 * @arg data     Array with measurement results
 * @arg isInside Flag signifying where sensor is
*/
void htuRead(float data[], bool isInside);

/*
 * Makes measurement with BMP280 sensor
 *
 * @arg data     Array with measurement results
 * @arg isInside Flag signifying where sensor is
*/
void bmpRead(float data[], bool isInside);

#endif
