# Smart Weather Station 3.1

ESP32 and server software for weather condition station. Project allows to measure temperature, humidity and pressure, save data in MySQL database and use simple WebAPI.

## Embedded

Board:
- NodeMCU ESP32 v1.1

Sensors:
- DHT22,
- HTU21D,
- BMP280.

## App

API prepared with: https://app.cyclic.sh
<br>
MySQL database: https://db.anotherwebservice.com

## Run WebAPI

Prerequisites:
- pyenv
- python 3.10.11

Install: `bin/install`
- creates virtual env
- installs dependencies from `requirements.txt`

Run: `bin/start`
- runs a `gunicorn` server
