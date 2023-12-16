#include <lidar.h>
LIDAR::Lidar lidar;

void setup() {
  LIDAR::LidarConfig config = {
      .serial = Serial1, .motor_pin = 19, .motor_speed = 120, .timeout = 300};
  lidar.setup(config);
  LIDAR::startService(lidar);
}

void loop() {}