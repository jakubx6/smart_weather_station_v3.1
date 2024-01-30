#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"

/*
 * Parameters and pinout
*/
#define SENSORSIZE      (8)
#define COUNTER         (5)
#define TIME            (60)
#define DHT_OUTSIDE     (4)
#define DHT_INSIDE      (16)
#define I2C_SDA_OUTSIDE (22)
#define I2C_SCL_OUTSIDE (23)
#define I2C_SDA_INSIDE  (18)
#define I2C_SCL_INSIDE  (19)
#define INSIDE          (true)
#define OUTSIDE         (false)

static const char* ssid     = "";
static const char* password = "";
static const char* hostUri  = "";
static const char* token    = "";

#endif
