#pragma once

#include "Arduino.h"
#include "commands.h"
#include "types.h"

namespace LIDAR {
struct LidarPoint {
  float distance;
  float angle;
  uint8_t quality;
  bool startBit;
};

struct LidarConfig {
  HardwareSerial &serial;
  int motor_pin;    // GPIO PIN
  int motor_speed;  // 0 -> 360
  int timeout;      // point aquisition timeout, might affect freshness of the
                    // points
};

class Lidar {
 public:
  enum {
    LIDAR_SERIAL_BAUDRATE = 115200,
    LIDAR_TIMEOUT = 500,
  };

  Lidar();
  ~Lidar();
  // the recommended way to setup the lidar and starts as a service
  void setup(LidarConfig &config);

  void setMotorPin(int pin);
  void setLidarSpeed(int speed);

  // use setup instead with a proper configuration
  // open the given serial interface and try to connect to the lidar
  void begin(HardwareSerial &serialobj);

  // close the currently opened serial interface
  void end();

  // check whether the serial interface is opened
  bool isOpen();

  // retrieve currently received sample point
  const LidarPoint &getCurrentPoint();

  void reconnect();
  const void loop();
  // ask the lidar for its health info
  u_result getHealth(lidar_response_device_health_t &healthinfo,
                     _u32 timeout = LIDAR_TIMEOUT);

  // ask the lidar for its device info like the serial number
  u_result getDeviceInfo(lidar_response_device_info_t &info,
                         _u32 timeout = LIDAR_TIMEOUT);

  // start the measurement operation
  u_result startScan(bool force = false, _u32 timeout = LIDAR_TIMEOUT * 2);
  // stop the measurement operation
  u_result stop();

  // wait for one sample point to arrive
  u_result scan(_u32 timeout = LIDAR_TIMEOUT);

 protected:
  u_result _sendCommand(_u8 cmd, const void *payload, size_t payloadsize);
  u_result _waitResponseHeader(lidar_ans_header_t *header, _u32 timeout);

 protected:
  HardwareSerial *_bined_serialdev;
  LidarPoint _currentMeasurement;
  int _lidar_motor_pin;
  int _lidar_speed;
};
void startService(Lidar &lidar);

}  // namespace LIDAR
