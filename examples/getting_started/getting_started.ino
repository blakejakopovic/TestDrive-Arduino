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