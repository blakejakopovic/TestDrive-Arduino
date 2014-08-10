# TestDrive Arduino Library
===

This library adds Arduino support for the TestDrive dashboard. It provides a simple API, and supports for many common sensor types.

**This library is build to work with [TestDrive Dashboard](#) to provide a real-time dashboard for your Arduino projects.**

## Key Features
* Simple integration into existing projects
* Light weight
* Easy to use
* Supports many sensor readings, including **Acceleration, Magnetic, Orientation, Gyro, Temperature, Distance, Light, Pressure, Humidity, Current, Voltage, and Color**
* Supports sensor labels (eg. Bedroom, Kitchen, Front Left, Front Right)
* Ability to control update frequency

## Getting Started
```arduino
#include <TestDrive.h>

// Variable to store temperature reading
float my_temp;

void setup() {
  // Initialise TestDrive (using a USB serial connection)
  TestDrive.begin();
}

void loop()
{
  // Read temperature
  my_temp = 22.5; // celsius

  // Update sensor reading using TestDrive
  TestDrive.sendTemperature(my_temp);

  // Delay 250ms before reading sensors again
  delay(250);
}
```

## Examples
* [Getting Started](#)
* [Weather Station](#)

## Future
* Support for more sensor types, with better dashboard visualisations.
* Support for TCP, for both Ethernet and Wifi data transport

## Thank you
* [Firmata](http://firmata.org/wiki/Main_Page)

## Contributing
All contributions welcome.

## License

Copyright © 2014 Blake Jakopovic

Distributed under the Eclipse Public License either version 1.0 or (at
your option) any later version.