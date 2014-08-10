#include <TestDrive.h>


#include "DHT.h"

// Connect DHT22 data wire to pin 12
DHT dht(10, DHT22);
float dht_temp, dht_humidity;


#include "SFE_BMP180.h"
#include <Wire.h>

#define ALTITUDE 0.0 // Define current altitude in meters
char status;
double bmp_temp, bmp_pressure;


void setup() {
  // Initialize TestDrive
  TestDrive.begin();

  // Initialize sensors
  dht.begin();
  pressure.begin();
}

void loop()
{
  // Set text labels for device IDs
  TestDrive.setLabel(1, "DHT22");   // id = 1
  TestDrive.setLabel(2, "BMP180");  // id = 2


  // Read DHT22 Temperature and Humidity
  // Note: Using device ID = 1
  dht_temp = dht.readTemperature();
  if (!isnan(dht_temp)) {
    TestDrive.sendTemperature(1, dht_temp);
  }

  dht_humidity = dht.readHumidity();
  if (!isnan(dht_humidity)) { 
    TestDrive.sendHumidity(1, dht_humidity);
  }


  // Read BMP180 Temperature and Pressure
  // Note: Using device ID = 2
  // Note: The pressure calculation depends on temperature

  // Ask for pressure caclulation
  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait until the sensor is ready
    delay(status);

    // Read Temperature
    status = pressure.getTemperature(bmp_temp);
    TestDrive.sendTemperature(2, (int)bmp_temp);
    
    if (status != 0)
    {
      // Ask for pressure caclulation
      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait until the sensor is ready
        delay(status);

        // Read Pressure
        status = pressure.getPressure(bmp_pressure, bmp_temp);
        if (status != 0)
        {
          TestDrive.sendPressure(2, (int)bmp_pressure);
        }
      }
    }
  }

  // Delay 250ms before reading sensors again
  delay(250);
}