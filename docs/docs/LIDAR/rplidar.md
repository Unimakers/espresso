# Cheatsheet

## RPLidar A2

![Image rplidar a2](https://www.robot-italy.com/media/catalog/product/cache/3/image/d43192dcd82ea942982b4b1d2a6e2479/d/f/dfr0445-image.jpg)

This is LiDAR we use at Unimakers club

## Cheatsheet - Hardware

![Image rplidar a2](http://www.seeedstudio.com/document/pics/110090081/110090081_1.jpg)
![Image rplidar a2](http://www.seeedstudio.com/document/pics/110090081/110090081_9.jpg)
![Image rplidar wiring](<https://static.cytron.io/image/catalog/products/SN-LIDAR-A2/SN-LIDAR-A2M8%20(6).jpg>)
![Image rplidar a2](<https://static.cytron.io/image/catalog/products/SN-LIDAR-A2/SN-LIDAR-A2M8%20(7).jpg>)

## Cheatsheet - Software

```c++
namespace LIDAR {

// starts lidar service
void startService(Lidar &lidar);

struct LidarPoint {
  float distance;
  float angle;
  uint8_t quality;
  bool startBit;
};

struct LidarConfig {
  // Hardware Serial, Serial1 or Serial2
  HardwareSerial &serial;

  // GPIO PIN
  int motor_pin;

  // 0 -> 360
  int motor_speed;

  //point aquisition timeout,
  // might affect freshness of the points
  int timeout;
};

class Lidar {
 public:
  Lidar();
  ~Lidar();

  // setup the lidar object
  void setup(LidarConfig &config);

  // get last processed point
  const LidarPoint &getCurrentPoint();
};
}

```
