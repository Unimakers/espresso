# Setup

## How-to Guide

### Simple Example

```c++ title="main.cpp"
#include <lidar.h>

LIDAR::Lidar lidar;

void setup() {
  LIDAR::LidarConfig config = {
      .serial = Serial1, .motor_pin = 19, .motor_speed = 120, .timeout = 300};

  lidar.setup(config);

  LIDAR::startService(lidar);

  LIDAR::LidarPoint point = lidar.getCurrentPoint(); // receive a point

  // process the point
  doSomethingWithThePoint(point);
}

void loop() {}
```
