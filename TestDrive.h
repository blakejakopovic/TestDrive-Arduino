/*
 * Testdrive.h - TestDrive library v0.1.0
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

#ifndef TestDrive_h
#define TestDrive_h

// Requires Firmata ~2.4.0
#include "Firmata.h"

/** Versioning */
#define TESTDRIVE_MAJOR_VERSION   0 // for non-compatible changes
#define TESTDRIVE_MINOR_VERSION   1 // for backwards compatible changes
#define TESTDRIVE_BUGFIX_VERSION  0 // for bugfix releases

/** Event Types */
#define SYSEX_TYPE_EVENT             0x01
#define SYSEX_TYPE_LABEL             0x02
#define SYSEX_TYPE_LOG               0x03

/** Event Kinds */
typedef enum
{
  SENSOR_TYPE_ACCELEROMETER        = 0x01,
  SENSOR_TYPE_MAGNETIC_FIELD,
  SENSOR_TYPE_ORIENTATION,
  SENSOR_TYPE_GYROSCOPE,
  SENSOR_TYPE_LIGHT,
  SENSOR_TYPE_PRESSURE,
  SENSOR_TYPE_PROXIMITY,
  SENSOR_TYPE_HUMIDITY,
  SENSOR_TYPE_TEMPERATURE,
  SENSOR_TYPE_VOLTAGE,
  SENSOR_TYPE_CURRENT,
  SENSOR_TYPE_COLOR,
  SENSOR_TYPE_ALTITUDE
} sensor_t;

/** Labels */

#define MAX_LABEL_COUNT 10
#define MAX_LABEL_LENGTH 20 // +1 string termination

/** Rate Limits */
// If you want to disable rate limiting uncomment
// #define TD_DISABLE_RATE_LIMIT
#define MAX_SAMPLE_RATE 50 // Hz per kind per id

/** Processing */

#define MAX_PROCESS_RATE 5000 // ms

class TestDriveClass : public FirmataClass
{
public:
    /* Constructors */
    TestDriveClass();
    
    /* Methods */
    // void sendAcceleration(byte id, float x, float y, float z);
    // void sendAcceleration(float x, float y, float z);    // m/s^2
    
    // void sendMagnetic(byte id, float x, float y, float z);
    // void sendMagnetic(float x, float y, float z);        // uT (micro-Testla)
    
    // void sendOrientation(byte id, float degrees);
    // void sendOrientation(float degrees);                 // degrees
    
    // void sendGyro(byte id, float x, float y, float z);
    // void sendGyro(float x, float y, float z);            // rad/s
    
    void sendTemperature(byte id, float celsius);
    void sendTemperature(float celsius);                 // celsius
    
    void sendDistance(byte id, float centimeters);
    void sendDistance(float centimeters);                // cm
    
    void sendLight(byte id, float lux);
    void sendLight(float lux);                           // SI lux
    
    void sendPressure(byte id, float hectopascal);
    void sendPressure(float hectopascal);                // hPa (hectopascals)
    
    void sendHumidity(float percent);
    void sendHumidity(byte id, float percent);           // percent
    
    void sendCurrent(byte id, float milliamps);
    void sendCurrent(float milliamps);                   // mA
    
    void sendVoltage(byte id, float volts);
    void sendVoltage(float volts);                       // V

    void sendAltitude(byte id, float meters);            // meters
    void sendAltitude(float meters);
    
    // void sendColor(byte id, float r, float g, float b);
    // void sendColor(float r, float g, float b);  // RGB

    void setLabel(byte id, char* label);

    void sendLog(byte id, char* msg);
    void sendLog(char* msg);

    void process();

private:
    /* private variables ---------------------------- */
    char labels[MAX_LABEL_COUNT][MAX_LABEL_LENGTH+1];
#ifndef TD_DISABLE_RATE_LIMIT
    unsigned int sample_rate[15][MAX_LABEL_COUNT];
    unsigned long last_sample_reset;
#endif
    unsigned long last_processed;

    /* private methods ------------------------------ */
    byte* floatToBytes(float num);
    byte* floatToBytes2(float x, float y, float z);

    void setLabel(byte id, char* label, bool update);

    bool rateLimited(byte kind, byte id);

    void sendEvent(byte kind, byte id, byte bytec, byte* bytev);
};

extern TestDriveClass TestDrive;

#endif /* TestDrive_h */