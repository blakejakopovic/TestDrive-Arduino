# TestDrive Arduino Library

This library adds Arduino support for the TestDrive Dashboard. It provides a simple API with support for common sensor data.

**This library is designed to work with the [TestDrive Dashboard](https://github.com/blakejakopovic/TestDrive) desktop application to provide a real-time dashboard view for your Arduino projects.**

## Demo!

To view the demo dashboard, please visit [http://blakejakopovic.github.io/TestDrive/](http://blakejakopovic.github.io/TestDrive/). The demo uses simulated sensor readings, however your dashboard will be automatically customised based on the data you send it.

## Key Features
* Simple integration into existing projects
* Light weight
* Easy to use
* Supports many sensor readings, including **Temperature, Distance, Light, Pressure, Altitude, Humidity, Current and Voltage** (with Acceleration, Magnetic, Orientation, Gyro, Color and others coming soon)
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
  my_temp = 23.5; // celsius

  // Update sensor reading using TestDrive
  TestDrive.sendTemperature(my_temp);

  // Delay 250ms before reading sensors again
  delay(250);
}
```

## Examples
* [Getting Started](https://github.com/blakejakopovic/TestDrive-Arduino/tree/master/examples/GettingStarted)

## Future
* Support for more sensor types, with more contextual (Mapping, 3D, etc) dashboard visualisations.
* Support for TCP, for both Ethernet and Wifi data transport

## Thank you
* [Firmata](http://firmata.org/wiki/Main_Page)

## Contributing
All contributions welcome.

Developers should take a look at the [DEVELOPER.md](https://github.com/blakejakopovic/TestDrive-Arduino/blob/master/DEVELOPER.md) document for how to setup their environment.

## License

Copyright © 2014 Blake Jakopovic

Distributed under the Eclipse Public License either version 1.0 or (at
your option) any later version.