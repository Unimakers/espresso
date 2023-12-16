#pragma once

#include "Arduino.h"
#include "commands.h"
#include "types.h"

struct RPLidarMeasurement {
  float distance;
  float angle;
  uint8_t quality;
  bool startBit;
};

class RPLidar {
 public:
  enum {
    RPLIDAR_SERIAL_BAUDRATE = 115200,
    RPLIDAR_DEFAULT_TIMEOUT = 500,
  };

  RPLidar();
  ~RPLidar();

  // open the given serial interface and try to connect to the RPLIDAR
  void begin(HardwareSerial &serialobj);

  // close the currently opened serial interface
  void end();

  // check whether the serial interface is opened
  bool isOpen();

  // ask the RPLIDAR for its health info
  u_result getHealth(rplidar_response_device_health_t &healthinfo,
                     _u32 timeout = RPLIDAR_DEFAULT_TIMEOUT);

  // ask the RPLIDAR for its device info like the serial number
  u_result getDeviceInfo(rplidar_response_device_info_t &info,
                         _u32 timeout = RPLIDAR_DEFAULT_TIMEOUT);

  // stop the measurement operation
  u_result stop();

  // start the measurement operation
  u_result startScan(bool force = false,
                     _u32 timeout = RPLIDAR_DEFAULT_TIMEOUT * 2);

  // wait for one sample point to arrive
  u_result waitPoint(_u32 timeout = RPLIDAR_DEFAULT_TIMEOUT);

  // retrieve currently received sample point

  const RPLidarMeasurement &getCurrentPoint() { return _currentMeasurement; }

 protected:
  u_result _sendCommand(_u8 cmd, const void *payload, size_t payloadsize);
  u_result _waitResponseHeader(rplidar_ans_header_t *header, _u32 timeout);

 protected:
  HardwareSerial *_bined_serialdev;
  RPLidarMeasurement _currentMeasurement;
};
