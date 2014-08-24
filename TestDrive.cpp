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
//** Support Methods
//******************************************************************************

byte* floatToBytes(float num);
byte* floatToBytes2(float x, float y, float z);
void sendEvent(byte type, byte id, byte bytec, byte* bytev);
void resetSampleRates();


//******************************************************************************
//* Constructors
//******************************************************************************

TestDriveClass::TestDriveClass()
{
  // Reset labels
  memset(TestDriveClass::labels, 0, sizeof(TestDriveClass::labels));

#ifndef TD_DISABLE_RATE_LIMIT
  resetSampleRates();

  last_sample_reset = 0;
  rate_limit_logged = false;
#endif
  
  last_processed = 0;

  memset(TestDriveClass::monitors, 0, sizeof(TestDriveClass::monitors));
  monitorc = 0;
}


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

void TestDriveClass::monitorTemperature(byte id, float *celsius)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_TEMPERATURE, id, 1, celsius);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorTemperature(float *celsius)
{
  monitorTemperature(0, celsius);
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

void TestDriveClass::monitorHumidity(byte id, float *percent)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_HUMIDITY, id, 1, percent);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorHumidity(float *percent)
{
  monitorTemperature(0, percent);
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

void TestDriveClass::monitorDistance(byte id, float *centimeters)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_PROXIMITY, id, 1, centimeters);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorDistance(float *centimeters)
{
  monitorTemperature(0, centimeters);
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

void TestDriveClass::monitorLight(byte id, float *lux)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_LIGHT, id, 1, lux);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorLight(float *lux)
{
  monitorTemperature(0, lux);
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

void TestDriveClass::monitorPressure(byte id, float *hectopascal)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_PRESSURE, id, 1, hectopascal);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorPressure(float *hectopascal)
{
  monitorTemperature(0, hectopascal);
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

void TestDriveClass::monitorCurrent(byte id, float *milliamps)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_CURRENT, id, 1, milliamps);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorCurrent(float *milliamps)
{
  monitorTemperature(0, milliamps);
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

void TestDriveClass::monitorVoltage(byte id, float *volts)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_VOLTAGE, id, 1, volts);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorVoltage(float *volts)
{
  monitorTemperature(0, volts);
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

void TestDriveClass::monitorAltitude(byte id, float *meters)
{
  monitor_entry_t entry;
  entry = makeMonitorEntry(SENSOR_TYPE_ALTITUDE, id, 1, meters);
  registerMonitorEntry(entry);
}

void TestDriveClass::monitorAltitude(float *meters)
{
  monitorTemperature(0, meters);
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
  startSysexType(SYSEX_TYPE_LOG);
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

#ifndef TD_DISABLE_RATE_LIMIT
    // Reset rate limit logged
    rate_limit_logged = false;
#endif

    // Loop over labels
    for(i=0; i<MAX_LABEL_COUNT; i++)
    {
      // Check if label is set
      if (strcmp(labels[i], "") != 0) {
        setLabel(i, labels[i], false);
      }
    }

    // Loop over monitored variables
    for(i=0; i<MAX_MONITOR_COUNT; i++)
    {
      monitor_entry_t *e = &monitors[i];
      
      if (e->kind > 0)
      { 
        switch(e->size) {
          case 1:
            sendEvent(e->kind, e->id, sizeof(float), floatToBytes(*(e->vals[0])));
            break;
          case 3:
            sendEvent(e->kind, e->id, (3*sizeof(float)), floatToBytes2(*(e->vals[0]), *(e->vals[1]), *(e->vals[2])));
            break;
        }
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
  startSysexType(SYSEX_TYPE_LABEL);
  write(id);
  for(i=0; i<strlen(label); i++) {
    sendValueAsTwo7bitBytes(label[i]);
  }
  endSysex();
}

/** Encoding */

byte* TestDriveClass::floatToBytes2(float x, float y, float z)
{
  byte buff[3*sizeof(float)];
  memcpy(buff, &x, sizeof(float));
  memcpy(buff + sizeof(float), &y, sizeof(float));
  memcpy(buff + 2*sizeof(float), &z, sizeof(float));

  return buff;
}

byte* TestDriveClass::floatToBytes(float num)
{
  byte buff[sizeof(float)];
  memcpy(buff, &num, sizeof(float));

  return buff;
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
    resetSampleRates();
  }

  // Increment sample rate counter
  sample_rate[kind][id] += 1;
  
  // Check if rate limit reached
  if (sample_rate[kind][id] > MAX_SAMPLE_RATE) {

    Serial.println();
    Serial.print(sample_rate[kind][id]);
    Serial.print(" > ");
    Serial.println(MAX_SAMPLE_RATE);

    if (!rate_limit_logged) {
      sendLog("TestDrive rate limited");
    }

    return true;
  }

  return false;
}
#endif

/** Events */

void TestDriveClass::sendEvent(sensor_t kind, byte id, byte bytec, byte* bytev)
{
#ifndef TD_DISABLE_RATE_LIMIT
  // NOOP if rate limit reached
  if (rateLimited(kind, id)) return;
#endif

  byte i;
  startSysexType(SYSEX_TYPE_EVENT);
  write(kind);
  write(id);
  for(i=0; i<bytec; i++) {
    sendValueAsTwo7bitBytes(bytev[i]);
  }
  endSysex();
}


/** Sysex */
void TestDriveClass::startSysexType(sysex_t type)
{
  startSysex();
  write(type);
}

/** Monitoring */

monitor_entry_t 
TestDriveClass::makeMonitorEntry(sensor_t kind, byte id, byte size, float *val)
{
  monitor_entry_t entry;
  entry.kind    = kind;
  entry.id      = id;
  entry.size    = size;
  entry.vals[0] = &*val;

  return entry;
}

void TestDriveClass::registerMonitorEntry(monitor_entry_t entry)
{
  if (monitorc < MAX_MONITOR_COUNT) {
    /* add new entry and increment count */
    memcpy(&monitors[monitorc++], &entry, sizeof(monitor_entry_t));
  }
}

/** Utilities */
#ifndef TD_DISABLE_RATE_LIMIT
void TestDriveClass::resetSampleRates()
{
  // unsigned int sample_rate[15][MAX_LABEL_COUNT] = {};
  // memset(sample_rate, 0, sizeof(sample_rate));
  memset(TestDriveClass::sample_rate, 0, sizeof(TestDriveClass::sample_rate));
}
#endif

// make one instance for the user to use
TestDriveClass TestDrive;