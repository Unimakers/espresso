#include <lidar.hpp>
lidar::Lidar Lidar;

void setup()
{
    lidar::LidarConfig config = {
        .serial = Serial1, .motor_pin = 3, .motor_speed = 120, .timeout = 300
    };
    Lidar.setup(config);
    lidar::startService(Lidar);

    Lidar.getCurrentPoint();
}

void loop() { }