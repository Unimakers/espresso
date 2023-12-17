#include <lidar.h>
lidar::Lidar Lidar;

void setup() {
  lidar::LidarConfig config = {
      .serial = Serial1, .motor_pin = 19, .motor_speed = 120, .timeout = 300};
  Lidar.setup(config);
  lidar::startService(Lidar);

  // How to get a point?
  Lidar.getCurrentPoint();
}

void loop() {}