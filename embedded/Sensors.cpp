#include "Sensors.h"
#include "Constant.h"

void dhtRead(float data[], bool isInside) {
  int dhtPin;
  if (isInside)
    dhtPin = DHT_INSIDE;
  else
    dhtPin = DHT_OUTSIDE;

  DHT dht(dhtPin, DHT22);
  dht.begin();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    return;
  }
    
  data[0] = h;    
  data[1] = t;    
  data[2]= (float)dht.computeHeatIndex(t, h, false);
}

void htuRead(float data[], bool isInside) {
  int i2cPin1,i2cPin2;
  if (isInside) {
    i2cPin1 = I2C_SDA_INSIDE;
    i2cPin2 = I2C_SCL_INSIDE;
  }
  else {
    i2cPin1 = I2C_SDA_OUTSIDE;
    i2cPin2 = I2C_SCL_OUTSIDE;
  }

  HTU21D htu;
  Wire.begin(i2cPin1, i2cPin2);

  if (!htu.begin()) {
    Wire.end();
    return;
  }
 
  htu.readSensor();
  if (isnan(htu.getHumidity()) || isnan(htu.getTemperature_C())) {
    Wire.end();
    return;
  }
  
  data[3] = htu.getHumidity();
  data[4] = htu.getTemperature_C();
  data[5] = htu.getHeatIndex_C();

  Wire.end();
}

void bmpRead(float data[], bool isInside) {
  int i2cPin1,i2cPin2;
  if (isInside) {
    i2cPin1 = I2C_SDA_INSIDE;
    i2cPin2 = I2C_SCL_INSIDE;
  }
  else {
    i2cPin1 = I2C_SDA_OUTSIDE;
    i2cPin2 = I2C_SCL_OUTSIDE;
  }

  Adafruit_BMP280 bmp(&Wire);
  Wire.begin(i2cPin1, i2cPin2);

  if (!bmp.begin(0x76)) {
    Wire.end();
    return;
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  float t = bmp.readTemperature();
  if (isnan(t)) {
    Wire.end();
    return;
  }
  
  data[6] = t;
  data[7] = bmp.readPressure() / 100;

  Wire.end();
}
