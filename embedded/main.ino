#include "Constants.h"
#include "Helpers.h"
#include "Sensors.h"

/*
 * Fill measurement results arrray with NaN
 *
 * @arg data Array with measurement results
*/
void cleanDataMatrix(float data[]);

/*
 * Reads data from all sensors
 *
 * @arg data     Array with measurement results
 * @arg isInside Flag signifying where sensor is
*/
void readData(float data[], bool isInside);

/* 
 * Makes measurement in specific localization
 *
 * @arg isInside Flag signifying where sensor is
 *
 * @return String with HTTP request body im quasi Json format
*/
String measurement(bool isInside);

/*
 * Arduino setup(). Begins serial port
*/
void setup() {
  Serial.begin(115200);
}

/*
 * Arduino loop(). Performs COUNTER number of measurement in TIME minutes delay. Sends HTTP POST request to host
*/
void loop() {
  long long s_time = millis();
  long long d_time = TIME * 1000;
  String requestBody = "";

  for(size_t i = 0; i < COUNTER; i++) {
    if(abs(millis() - s_time) >= d_time) {
      requestBody += measurement(OUTSIDE);
      requestBody += "\n";
      delay(500);

      requestBody += measurement(INSIDE);
      s_time = millis();
      if(i < COUNTER - 1) {
        requestBody += "\n";
      }
    }
    else {
      i--;
    }
  }

  wifiRequest(requestBody);
}

String measurement(bool isInside) {
  float measData[SENSORSIZE];

  cleanDataMatrix(measData);
  readData(measData, isInside);
  printData(measData, isInside);

  return makeRequestBody(measData, isInside);
}

void readData(float data[], bool isInside) {
  dhtRead(data, isInside);
  htuRead(data, isInside);
  bmpRead(data, isInside);
}

void cleanDataMatrix(float data[]) {
  for(size_t i = 0; i < SENSORSIZE; i++)
    data[i] = sqrt(-1);
}
