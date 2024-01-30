#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

/*
 * Creates HTTP body request
 *
 * @arg data     Array with measurement results
 * @arg isInside Flag signifying where sensor is
 * 
 * @return Request body im quasi Json format
*/
String makeRequestBody(float data[], bool isInside);

/*
 * Creates HTTP POST request and sends to host
 *
 * @arg requestBody Body for HTTP request on quasi Json format
*/
void wifiRequest(String requestBody);

/* 
 * Prints measurement data to serial port
 *
 * @arg data     Array with measurement results
 * @arg isInside Flag signifying where sensor is
*/
void printData(float data[], bool isInside);

#endif
