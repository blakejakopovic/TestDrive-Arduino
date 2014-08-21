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

#include "Firmata.h" // requires ~v2.4.0


/** Versioning */
#define TESTDRIVE_MAJOR_VERSION   0 // for non-compatible changes
#define TESTDRIVE_MINOR_VERSION   1 // for backwards compatible changes
#define TESTDRIVE_BUGFIX_VERSION  0 // for bugfix releases


/** Event Types */
typedef enum 
{
  SYSEX_TYPE_EVENT                 = 0x01,
  SYSEX_TYPE_LABEL,
  SYSEX_TYPE_LOG
} sysex_t;


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
#define MAX_LABEL_COUNT              10
#define MAX_LABEL_LENGTH             20

/** Rate Limits */
// To disable rate limiting uncomment
// #define TD_DISABLE_RATE_LIMIT true

#define MAX_SAMPLE_RATE              10  // Hz per kind per id


/** Monitoring */
#define MAX_MONITOR_COUNT            10

typedef struct 
{
  sensor_t  kind;
  byte      id;
  byte      size;
  float     *vals[3];
} monitor_entry_t;


/** Processing */

#define MAX_PROCESS_RATE              5000  // ms


/** TestDrive Class */

class TestDriveClass : public FirmataClass
{
public:
    /** constructors ---------------------------- */
    TestDriveClass();
    
    /** public methods ---------------------------- */

    /* Acceleration  --  m/s^2  (meters/second^2) */
    // void sendAcceleration(byte id, float x, float y, float z);
    // void sendAcceleration(float x, float y, float z);
    
    /* Magnitism  --  uT (micro-Testla) */
    // void sendMagnetic(byte id, float x, float y, float z);
    // void sendMagnetic(float x, float y, float z);
    
    /* Orientation  --  degree */
    // void sendOrientation(byte id, float degrees);
    // void sendOrientation(float degrees);
    
    /* Gyroscope  --  rad/s (radians/second)*/
    // void sendGyro(byte id, float x, float y, float z);
    // void sendGyro(float x, float y, float z);
    
    /* Temperature  --  C (celsius) */
    void monitorTemperature(byte id, float *celsius);
    void monitorTemperature(float *celsius);

    void sendTemperature(byte id, float celsius);
    void sendTemperature(float celsius);
    
    /* Distance  --  cm (centimeters) */
    void monitorDistance(byte id, float *centimeters);
    void monitorDistance(float *centimeters);

    void sendDistance(byte id, float centimeters);
    void sendDistance(float centimeters);
    
    /* Light  --  SI lux */
    void monitorLight(byte id, float *lux);
    void monitorLight(float *lux);

    void sendLight(byte id, float lux);
    void sendLight(float lux);
    
    /* Pressure  --  hPa (hectopascals) */
    void monitorPressure(byte id, float *hectopascal);
    void monitorPressure(float *hectopascal);

    void sendPressure(byte id, float hectopascal);
    void sendPressure(float hectopascal);
    
    /* Humidity  --  % (relative) */
    void monitorHumidity(byte id, float *percent);
    void monitorHumidity(float *percent);

    void sendHumidity(float percent);
    void sendHumidity(byte id, float percent);
    
    /* Current  -- mA (milliamps) */
    void monitorCurrent(byte id, float *milliamps);
    void monitorCurrent(float *milliamps);

    void sendCurrent(byte id, float milliamps);
    void sendCurrent(float milliamps);
    
    /* Voltage -- V (volts) */
    void monitorVoltage(byte id, float *volts);
    void monitorVoltage(float *volts);

    void sendVoltage(byte id, float volts);
    void sendVoltage(float volts);

    /* Altitude  --  m (meters) */
    void monitorAltitude(byte id, float *meters);
    void monitorAltitude(float *meters);
    
    void sendAltitude(byte id, float meters);
    void sendAltitude(float meters);
    
    /* Color  --  RGB (255,255,255)*/
    // void sendColor(byte id, float r, float g, float b);
    // void sendColor(float r, float g, float b);

    /* Labels */
    void setLabel(byte id, char* label);

    /* Logging */
    void sendLog(byte id, char* msg);
    void sendLog(char* msg);

    /* Processing */
    void process();

private:
    /** private variables ---------------------------- */
    
    /* Labels */
    char labels[MAX_LABEL_COUNT][MAX_LABEL_LENGTH+1];

    /* Rate limiting */
#ifndef TD_DISABLE_RATE_LIMIT
    unsigned int sample_rate[15][MAX_LABEL_COUNT];
    unsigned long last_sample_reset;
    bool rate_limit_logged;
#endif

    /* Monitoring */
    monitor_entry_t monitors[MAX_MONITOR_COUNT];
    byte monitorc;

    /* Processing */
    unsigned long last_processed;

    /* private methods ------------------------------ */
    byte* floatToBytes(float num);
    byte* floatToBytes2(float x, float y, float z);

    /* Labels */
    void setLabel(byte id, char* label, bool update);

    /* Rate limiting */
    bool rateLimited(byte kind, byte id);

    /* Monitoring */
    monitor_entry_t 
      makeMonitorEntry(sensor_t kind, byte id, byte size, float *val);
    void registerMonitorEntry(monitor_entry_t entry);

    /* Events */
    void sendEvent(sensor_t kind, byte id, byte bytec, byte* bytev);

    /* Sysex */
    void startSysexType(sysex_t type);

    /* Utilities */
#ifndef TD_DISABLE_RATE_LIMIT
    void resetSampleRates();
#endif
};

extern TestDriveClass TestDrive;

#endif /* TestDrive_h */