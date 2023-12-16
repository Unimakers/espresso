# Library

## How-to Guide

### Quick Start

```c++ title="main.cpp"
#include <lidar.h>

// declare a new instance of Lidar
LIDAR::Lidar lidar;

void setup() {

  // declare lidar configuration
  LIDAR::LidarConfig config = {
      .serial = Serial1, .motor_pin = 19, .motor_speed = 120, .timeout = 300};

  // configure our lidar object
  lidar.setup(config);

  // launch it as a service in the background
  LIDAR::startService(lidar);
}

void loop() {
  // receive a point
  LIDAR::LidarPoint point = lidar.getCurrentPoint();
  // process the point
  doSomethingWithThePoint(point);
}
```

### Configuration

To build a new LiDAR instance or service we need to pass on the configuration struct:

**LIDAR::LidarConfig**

| Attribute     | Type           | Description                                                 |
| ------------- | -------------- | ----------------------------------------------------------- |
| `serial`      | HardwareSerial | defines the hardware serial used                            |
| `motor_pin`   | int            | pin in esp32 used by lidar's motor                          |
| `motor_speed` | int            | motor speed between 120 "slow" and 360 "veryfast"           |
| `timeout`     | int            | used to skip data acquistion and move to the next operation |

```c++ title="configuration example"
  LIDAR::LidarConfig config =
  {
      .serial = Serial1,
      .motor_pin = 19,
      .motor_speed = 120,
      .timeout = 300
  };
```
