/*
 * Testdrive.h - TestDrive Arduino library
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

#include "lib/FirmataMaster/Firmata.h"

// Firmata version check
#if FIRMATA_MAJOR_VERSION != 2 || FIRMATA_MINOR_VERSION != 4
  #error "TestDrive requires Firmata version 2.4.x to run."
#endif


/** Event Types */
#define SYSEX_TYPE_EVENT             0x01
#define SYSEX_TYPE_LABEL             0x02
#define SYSEX_TYPE_LOG               0x03

/** Event Kinds */
typedef enum
{
  SENSOR_TYPE_ACCELEROMETER         = 0x01,
  SENSOR_TYPE_MAGNETIC_FIELD        = 0x02,
  SENSOR_TYPE_ORIENTATION           = 0x03,
  SENSOR_TYPE_GYROSCOPE             = 0x04,
  SENSOR_TYPE_LIGHT                 = 0x05,
  SENSOR_TYPE_PRESSURE              = 0x06,

  SENSOR_TYPE_PROXIMITY             = 0x08,

  SENSOR_TYPE_HUMIDITY              = 0x12,
  SENSOR_TYPE_TEMPERATURE           = 0x13,
  SENSOR_TYPE_VOLTAGE               = 0x15,
  SENSOR_TYPE_CURRENT               = 0x16,
  SENSOR_TYPE_COLOR                 = 0x17
};


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
    
    // void sendColor(byte id, float r, float g, float b);
    // void sendColor(float r, float g, float b);  // RGB

    void setLabel(byte id, char* label);

    void sendLog(byte id, char* msg);
    void sendLog(char* msg);

private:
    /* private methods ------------------------------ */
    byte* floatToBytes(float num);
    byte* floatToBytes2(float x, float y, float z);

    void sendEvent(byte type, byte id, byte bytec, byte* bytev);
};

extern TestDriveClass TestDrive;

#endif /* TestDrive_h */