# Weather Station TestDrive Example

This example sketch reads data from a DHT22 (temperature and humidity sensor) and a BMP180 (temperature, pressure, altitude) sensor, and sends the data to a TestDrive compatible dashboard.

# Wiring
Using an Arduino Uno

* Connect your DHT22 to ground, 5v and the data line to pin 10
* Connect your BMP180 to ground, 3.3v, SDA -> pin A4, SDC -> pin A5

# Installation
* Open the sketch
* (Optional) For best results, update the `ALTITUDE` values to your current altitude in meters
* Upload the sketch using Arduino IDE to your Arduino (tested using an Arduino Uno)
* You should see the TX light flash around 4 times per second, which means data is being sent via USB Serial.

# Credits
* [Adafruit's DHT Library](https://github.com/adafruit/DHT-sensor-library)
* [Sparkfun's BMP180 Library](https://github.com/sparkfun/BMP180_Breakout)