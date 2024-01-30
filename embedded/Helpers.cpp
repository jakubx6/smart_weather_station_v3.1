#include "Helpers.h"
#include "Constants.h"

String makeRequestBody(float data[], bool isInside) {
  char *sensorName[SENSORSIZE] = {"dht_humidity", "dht_temperature", "dht_heatindex", "htu_humidity", "htu_temperature", "htu_heatindex", "bmp_temperature", "bmp_preasure"};
  String requestContent = "{\"localization\": ";

  if(isInside)
    requestContent += "\"in\", ";
  else
    requestContent += "\"out\", ";

  for(size_t i = 0; i < SENSORSIZE; i++) {
    requestContent += "\"";
    requestContent += sensorName[i];
    requestContent += "\": ";
    requestContent += isnan(data[i]) ? "null" : String(data[i]);
    if(i < SENSORSIZE - 1)
      requestContent += ", ";
    else
      requestContent += "}";
  }

  return requestContent;
}

void wifiRequest(String requestBody) {
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  int counter = 0;
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");

    counter++;
    if(counter == 30) {
      break;
      Serial.println("WiFi Disconnected");
    }

    delay(500);
  }

  if(WiFi.status()== WL_CONNECTED){
    Serial.println("WiFi Connected");
    HTTPClient http;
    
    http.begin(hostUri);
    http.addHeader("Content-Type", "text/plain");
    http.addHeader("Token", token);
    Serial.println(requestBody);
    int httpsResponseCode = http.POST(requestBody);
  
    Serial.print("HTTPS Response code: ");
    Serial.println(http.errorToString(httpsResponseCode).c_str());

    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void printData(float data[], bool isInside) {
  if(isInside)
    Serial.println("Results inside");
  else
    Serial.println("Results outside");
    
  Serial.print(F("Humidity: "));
  Serial.print(data[0]);
  Serial.print(F("%  Temperature: "));
  Serial.print(data[1]);
  Serial.print(F("°C Heat index: "));
  Serial.print(data[2]);
  Serial.println(F("°C "));

  Serial.print(F("Humidity: "));
  Serial.print(data[3]);
  Serial.print(F("%  Temperature: "));
  Serial.print(data[4]);
  Serial.print(F("°C Heat index: "));
  Serial.print(data[5]);
  Serial.println(F("°C "));

  Serial.print(F("Temperature: "));
  Serial.print(data[6]);
  Serial.print(F("°C Preasure: "));
  Serial.print(data[7]);
  Serial.println(F(" hPa "));
  Serial.println("===============================================");
}