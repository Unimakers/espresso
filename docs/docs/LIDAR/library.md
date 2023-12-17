# Library

## How-to Guide

### Quick Start

```c++ title="main.cpp"
#include <lidar.hpp>

// declare a new instance of Lidar
lidar::Lidar Lidar;

void setup() {

  // declare lidar configuration
  lidar::LidarConfig config = {
      .serial = Serial1, .motor_pin = 19, .motor_speed = 120, .timeout = 300};

  // configure our lidar object
  Lidar.setup(config);

  // launch it as a service in the background
  lidar::startService(Lidar);
}

void loop() {
  // receive a point
  lidar::LidarPoint point = Lidar.getCurrentPoint();
  // process the point
  doSomethingWithThePoint(point);
}
```

### Configuration

To build a new LiDAR instance or service we need to pass on the configuration struct:

==**lidar::LidarConfig**==

| Attribute     | Type           | Description                                                 |
| ------------- | -------------- | ----------------------------------------------------------- |
| `serial`      | HardwareSerial | defines the hardware serial used                            |
| `motor_pin`   | int            | pin in esp32 used by lidar's motor                          |
| `motor_speed` | int            | motor speed between 120 "slow" and 360 "veryfast"           |
| `timeout`     | int            | used to skip data acquistion and move to the next operation |

```c++ title="syntax"
  lidar::LidarConfig config =
  {
      .serial = Serial1,
      .motor_pin = 19,
      .motor_speed = 120,
      .timeout = 300
  };
```

### Read a point

function used to read the point: ==**LIDAR::Lidar.getCurrentPoint()**==

==**lidar::LidarPoint**==

| Attribute  | Type     | Description                                                      |
| ---------- | -------- | ---------------------------------------------------------------- |
| `distance` | float    | distance from lidar to surface in mm                             |
| `angle`    | float    | relative angle at which the point was detected in degrees        |
| `quality`  | int      | quality of the point ranges from 1 low quality - 15 high quality |
| `bool`     | startBit | not implemented                                                  |

```c++ title="syntax"
  lidar::LidarPoint point = Lidar.getCurrentPoint();
```
