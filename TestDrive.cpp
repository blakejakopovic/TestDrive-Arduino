/*
 * Testdrive.cpp - TestDrive library v0.1.0
 * 
 * (C) Copyright 2014 Blake Jakopovic.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *     Blake V. Jakopovic
 */


#include "TestDrive.h"
#include "HardwareSerial.h"

//******************************************************************************
//* Constructors
//******************************************************************************

TestDriveClass::TestDriveClass()
{
  // Reset labels
    memcpy(labels, 0, sizeof labels);

#ifndef TD_DISABLE_RATE_LIMIT
  // Reset sample rate counters
    memcpy(sample_rate, 0, sizeof sample_rate);

  last_sample_reset = 0;
#endif
  
  last_processed = 0;
}


//******************************************************************************
//** Support Methods
//******************************************************************************

byte* floatToBytes(float num);
byte* floatToBytes2(float x, float y, float z);
void sendEvent(byte type, byte id, byte bytec, byte* bytev);


//******************************************************************************
//* Public Methods
//******************************************************************************

/** Temperature */

void TestDriveClass::sendTemperature(byte id, float celsius)
{
  sendEvent(SENSOR_TYPE_TEMPERATURE, id, sizeof(float), floatToBytes(celsius));
}

void TestDriveClass::sendTemperature(float celsius)
{
  sendTemperature(0, celsius);
}

/** Humidity */

void TestDriveClass::sendHumidity(byte id, float percent)
{
  sendEvent(SENSOR_TYPE_HUMIDITY, id, sizeof(float), floatToBytes(percent));
}

void TestDriveClass::sendHumidity(float percent)
{
  sendHumidity(0, percent);
}

/** Orientation */

// void TestDriveClass::sendOrientation(byte id, float degrees)
// {
//   sendEvent(SENSOR_TYPE_ORIENTATION, id, sizeof(float), floatToBytes(degrees));
// }

// void TestDriveClass::sendOrientation(float degrees)
// {
//   sendOrientation(0, degrees);
// }

/** Distance */

void TestDriveClass::sendDistance(byte id, float centimeters)
{
  sendEvent(SENSOR_TYPE_PROXIMITY, id, sizeof(float), floatToBytes(centimeters));
}

void TestDriveClass::sendDistance(float centimeters)
{
  sendDistance(0, centimeters);
}

/** Light */

void TestDriveClass::sendLight(byte id, float lux)
{
  sendEvent(SENSOR_TYPE_LIGHT, id, sizeof(float), floatToBytes(lux));
}

void TestDriveClass::sendLight(float lux)
{
  sendLight(0, lux);
}

/** Pressure */

void TestDriveClass::sendPressure(byte id, float hectopascal)
{
  sendEvent(SENSOR_TYPE_PRESSURE, id, sizeof(float), floatToBytes(hectopascal));
}

void TestDriveClass::sendPressure(float hectopascal)
{
  sendPressure(0, hectopascal);
}

/** Current */

void TestDriveClass::sendCurrent(byte id, float milliamps)
{
  sendEvent(SENSOR_TYPE_CURRENT, id, sizeof(float), floatToBytes(milliamps));
}

void TestDriveClass::sendCurrent(float milliamps)
{
  sendCurrent(0, milliamps);
}

/**  Voltage */

void TestDriveClass::sendVoltage(byte id, float volts)
{
  sendEvent(SENSOR_TYPE_VOLTAGE, id, sizeof(float), floatToBytes(volts));
}

void TestDriveClass::sendVoltage(float volts)
{
  sendVoltage(0, volts);
}

/**  Altitude */

void TestDriveClass::sendAltitude(byte id, float meters)
{
  sendEvent(SENSOR_TYPE_ALTITUDE, id, sizeof(float), floatToBytes(meters));
}

void TestDriveClass::sendAltitude(float meters)
{
  sendAltitude(0, meters);
}

/** Acceleration */

// void TestDriveClass::sendAcceleration(byte id, float x, float y, float z)
// {
//   sendEvent(SENSOR_TYPE_ACCELEROMETER, id, (3 * sizeof(float)), floatToBytes2(x,y,z));
// }

// void TestDriveClass::sendAcceleration(float x, float y, float z)
// {
//   sendAcceleration(0, x, y, z);
// }

/** Magnometer */

// void TestDriveClass::sendMagnetic(byte id, float x, float y, float z)
// {
//   sendEvent(SENSOR_TYPE_MAGNETIC_FIELD, id, (3 * sizeof(float)), floatToBytes2(x,y,z));
// }

// void TestDriveClass::sendMagnetic(float x, float y, float z)
// {
//   sendMagnetic(0, x, y, z);
// }

/** Gyroscope */

// void TestDriveClass::sendGyro(byte id, float x, float y, float z)
// {
//   sendEvent(SENSOR_TYPE_GYROSCOPE, id, (3 * sizeof(float)), floatToBytes2(x,y,z));
// }

// void TestDriveClass::sendGyro(float x, float y, float z)
// {
//   sendGyro(0, x, y, z);
// }

/** Color */

// void TestDriveClass::sendColor(byte id, float r, float g, float b)
// {
//   sendEvent(SENSOR_TYPE_COLOR, id, (3 * sizeof(float)), floatToBytes2(r,g,b));
// }

// void TestDriveClass::sendColor(float r, float g, float b)
// {
//   sendColor(0, r, g, b);
// }


/** Label */

void TestDriveClass::setLabel(byte id, char* label)
{
  setLabel(id, label, true);
}

/** Log */

void TestDriveClass::sendLog(byte id, char* msg)
{
  byte i;
  startSysex();
  write(SYSEX_TYPE_LOG);
  write(id);
  for(i=0; i<strlen(msg); i++) {
    sendValueAsTwo7bitBytes(msg[i]);
  }
  endSysex();
}

void TestDriveClass::sendLog(char* msg)
{
  sendLog(0, msg);
}

void TestDriveClass::process()
{
  int i;
  unsigned long now = millis();

  // Check processing rate limiting
  if (last_processed + MAX_PROCESS_RATE < now) {

    // Update last processed
    last_processed = now;

    // Loop over labels
    for(i=0; i<MAX_LABEL_COUNT; i++)
    {
      // Check if label is set
      if (strcmp(labels[i], "") != 0) {
        setLabel(i, labels[i], false);
      }
    }
  }
}


//******************************************************************************
//* Private Methods
//******************************************************************************

/** Label */

void TestDriveClass::setLabel(byte id, char* label, bool update)
{
  // Update internal label value
  if (update) {
    strncpy(labels[id], label, MAX_LABEL_LENGTH);
  }

  byte i;
  startSysex();
  write(SYSEX_TYPE_LABEL);
  write(id);
  for(i=0; i<strlen(label); i++) {
    sendValueAsTwo7bitBytes(label[i]);
  }
  endSysex();
}

/** Encoding */

byte* TestDriveClass::floatToBytes2(float x, float y, float z)
{
  union floats2bytes { struct {float x; float y; float z;} v;
                       unsigned char b[3*sizeof(float)]; };
  
  floats2bytes f2b;
  f2b.v.x = x;
  f2b.v.y = y;
  f2b.v.z = z;

  byte buff[3 * sizeof(float)];
  memcpy(buff, f2b.b, 3 * sizeof(float));

  return (byte*)buff;
}

byte* TestDriveClass::floatToBytes(float num)
{
  union float2bytes { float f; unsigned char b[sizeof(float)]; };
  float2bytes f2b;
  f2b.f = num;

  byte buff[sizeof(float)];
  memcpy(buff, f2b.b, sizeof(float));

  return (byte*)buff;
}

/** Rate Limiting */
#ifndef TD_DISABLE_RATE_LIMIT
bool TestDriveClass::rateLimited(byte kind, byte id)
{
  unsigned long now = millis();

  // Check processing rate limiting
  if (last_sample_reset + 1000 < now)
  {
    // Update last sample time
    last_sample_reset = now;

    // Reset sample rate counters
    memcpy(sample_rate, 0, sizeof sample_rate);
  }

  // Increment sample rate counter
  sample_rate[kind][id] += 1;
  
  // Check if rate limit reached
  if (sample_rate[kind][id] > MAX_SAMPLE_RATE) {
    // TODO: Add sendLog message to notify user (might be too noisey)
    return true;
  }

  return false;
}
#endif

/** Events */

void TestDriveClass::sendEvent(byte kind, byte id, byte bytec, byte* bytev)
{
#ifndef TD_DISABLE_RATE_LIMIT
  // NOOP if rate limit reached
  if (rateLimited(kind, id)) return;
#endif

  byte i;
  startSysex();
  write(SYSEX_TYPE_EVENT);
  write(kind);
  write(id);
  for(i=0; i<bytec; i++) {
    sendValueAsTwo7bitBytes(bytev[i]);
  }
  endSysex();
}

// make one instance for the user to use
TestDriveClass TestDrive;