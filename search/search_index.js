var __index = {"config":{"lang":["en"],"separator":"[\\s\\-]+","pipeline":["stopWordFilter"]},"docs":[{"location":"index.html","title":"Home","text":""},{"location":"index.html#overview","title":"Overview","text":"<pre><code> ______                                     _______          _ _    _ _\n|  ____|                                   |__   __|        | | |  (_) |\n| |__   ___ _ __  _ __ ___  ___ ___  ___      | | ___   ___ | | | ___| |_\n|  __| / __| '_ \\| '__/ _ \\/ __/ __|/ _ \\     | |/ _ \\ / _ \\| | |/ / | __|\n| |____\\__ \\ |_) | | |  __/\\__ \\__ \\ (_) |    | | (_) | (_) | |   &lt;| | |_\n|______|___/ .__/|_|  \\___||___/___/\\___/     |_|\\___/ \\___/|_|_|\\_\\_|\\__|\n           | |\n           |_|\n</code></pre>"},{"location":"index.html#what-is-this-library","title":"What is this library ?","text":"<p>Espresso is a Simple and lightweight yet effective robotics toolkit and a package of libraries aimed to stop reinvinting the wheel when building robotics software, it is designed specifically to run on Espressif's SOCs (ESP32-ESP32-S3), it includes common algorithm used in robotics, from controlling servos to object detection</p>"},{"location":"index.html#why-the-name","title":"Why the name ?","text":"<p>Who doesn't love the life juice aka coffee, and espresso is helluva an efficient drink, thus the name esp32 + espresso</p>"},{"location":"index.html#how-can-i-use-it-in-my-program","title":"How can i use it in my program ?","text":"<p>Well unfortunately you can't, it's not yet optimized and stable yet to be used by other people, But, you can always look at the code, it's simple and no magic stuff, CTRL+C / CTRL+V is your friend. The modules are decoupled from each other so you only copy the library you want.</p>"},{"location":"index.html#why-building-a-new-library-only-for-esp32","title":"Why building a new library only for ESP32 ?","text":"<p>The only best bang for buck microcontroller out there is ESP32 (looking at you stm32). WiFi/BT + two of more than enough cpu cores + active community + great docs &lt; than 5$ thats too good to be true that just happens to be true.</p>"},{"location":"index.html#what-features-would-be-included-in-this-library","title":"What features would be included in this library ?","text":"<p>I just wish if we have limitless time, I would implement anything i could think of, but here is an non exhaustive list of features that will be included in the next following month (freezed features) and some of my wishlist.</p> Feature Status LiDAR Oct-Dec Steppers Oct-Dec Servos Oct-Dec I2C Bus Oct-Dec EQL Done Color Tracking Done TFlite inference WishList Mesh Network WishList OLED Display WishList TFT Display WishList"},{"location":"LIDAR/index.html","title":"Quick-Info","text":""},{"location":"LIDAR/index.html#what-is-a-lidar","title":"What is a LiDAR ?","text":"<p>LiDAR is a remote sensing technology that uses laser beams to measure distances and create detailed 3D maps of objects and environments.</p> <p>It stands for Light Detection and Ranging.</p> <p>By emitting laser pulses and analyzing the reflected light, LiDAR determines the range, elevation, and spatial information of various surfaces and objects.</p>"},{"location":"LIDAR/index.html#some-use-cases-of-lidar","title":"Some use cases of LiDAR","text":"<p>LiDAR can be used in autonomous robots/vehicules to detect and measure the distance to surrounding objects, enabling real-time obstacle avoidance and enhancing overall safety.</p> <p></p> <p>In forestry applications, LiDAR can help create detailed and precise 3D maps of forests, enabling efficient forest management strategies, including monitoring tree growth and health, assessing fire risks, and optimizing logging operations.</p> <p></p> <p>LiDAR scanning can aid in archaeological excavations, allowing researchers to non-invasively create 3D models of sites, helping with documentation, preservation, and analysis of cultural heritage, artifacts, and structures.</p> <p></p>"},{"location":"LIDAR/library.html","title":"Library","text":""},{"location":"LIDAR/library.html#how-to-guide","title":"How-to Guide","text":""},{"location":"LIDAR/library.html#quick-start","title":"Quick Start","text":"main.cpp<pre><code>#include &lt;lidar.hpp&gt;\n\n// declare a new instance of Lidar\nlidar::Lidar Lidar;\n\nvoid setup() {\n\n  // declare lidar configuration\n  lidar::LidarConfig config = {\n      .serial = Serial1, .motor_pin = 19, .motor_speed = 120, .timeout = 300};\n\n  // configure our lidar object\n  Lidar.setup(config);\n\n  // launch it as a service in the background\n  lidar::startService(Lidar);\n}\n\nvoid loop() {\n  // receive a point\n  lidar::LidarPoint point = Lidar.getCurrentPoint();\n  // process the point\n  doSomethingWithThePoint(point);\n}\n</code></pre>"},{"location":"LIDAR/library.html#configuration","title":"Configuration","text":"<p>To build a new LiDAR instance or service we need to pass on the configuration struct:</p> <p>lidar::LidarConfig</p> Attribute Type Description <code>serial</code> HardwareSerial defines the hardware serial used <code>motor_pin</code> int pin in esp32 used by lidar's motor <code>motor_speed</code> int motor speed between 120 \"slow\" and 360 \"veryfast\" <code>timeout</code> int used to skip data acquistion and move to the next operation syntax<pre><code>  lidar::LidarConfig config =\n  {\n      .serial = Serial1,\n      .motor_pin = 19,\n      .motor_speed = 120,\n      .timeout = 300\n  };\n</code></pre>"},{"location":"LIDAR/library.html#read-a-point","title":"Read a point","text":"<p>function used to read the point: LIDAR::Lidar.getCurrentPoint()</p> <p>lidar::LidarPoint</p> Attribute Type Description <code>distance</code> float distance from lidar to surface in mm <code>angle</code> float relative angle at which the point was detected in degrees <code>quality</code> int quality of the point ranges from 1 low quality - 15 high quality <code>bool</code> startBit not implemented syntax<pre><code>  lidar::LidarPoint point = Lidar.getCurrentPoint();\n</code></pre>"},{"location":"LIDAR/rplidar.html","title":"Cheatsheet","text":""},{"location":"LIDAR/rplidar.html#rplidar-a2","title":"RPLidar A2","text":"<p>This is LiDAR we use at Unimakers club</p>"},{"location":"LIDAR/rplidar.html#cheatsheet-hardware","title":"Cheatsheet - Hardware","text":""},{"location":"LIDAR/rplidar.html#cheatsheet-software","title":"Cheatsheet - Software","text":"<pre><code>namespace lidar {\n\n// starts lidar service\nvoid startService(Lidar &amp;lidar);\n\nstruct LidarPoint {\n  float distance;\n  float angle;\n  uint8_t quality;\n  bool startBit;\n};\n\nstruct LidarConfig {\n  // Hardware Serial, Serial1 or Serial2\n  HardwareSerial &amp;serial;\n\n  // GPIO PIN\n  int motor_pin;\n\n  // 0 -&gt; 360\n  int motor_speed;\n\n  //point aquisition timeout,\n  // might affect freshness of the points\n  int timeout;\n};\n\nclass Lidar {\n public:\n  Lidar();\n  ~Lidar();\n\n  // setup the lidar object\n  void setup(LidarConfig &amp;config);\n\n  // get last processed point\n  const LidarPoint &amp;getCurrentPoint();\n};\n}\n</code></pre>"},{"location":"LIDAR/src_def.html","title":"Source definition","text":"<pre><code>#pragma once\n\n#include \"Arduino.h\"\n#include \"commands.hpp\"\n#include \"types.hpp\"\n\nnamespace lidar {\n\nstruct LidarPoint {\n  float distance;\n  float angle;\n  uint8_t quality;\n  bool startBit;\n};\n\nstruct LidarConfig {\n  HardwareSerial &amp;serial;\n  int motor_pin;    // GPIO PIN\n  int motor_speed;  // 0 -&gt; 360\n  int timeout;      // point aquisition timeout, might affect freshness of the\n                    // points\n};\n\nclass Lidar {\n public:\n  enum {\n    LIDAR_SERIAL_BAUDRATE = 115200,\n    LIDAR_TIMEOUT = 500,\n  };\n\n  Lidar();\n  ~Lidar();\n\n  // the recommended way to setup the lidar and starts as a service\n  void setup(LidarConfig &amp;config);\n\n  void setMotorPin(int pin);\n  void setLidarSpeed(int speed);\n\n  // use setup instead with a proper configuration\n  // open the given serial interface and try to connect to the lidar\n  void begin(HardwareSerial &amp;serialobj);\n\n  // close the currently opened serial interface\n  void end();\n\n  // check whether the serial interface is opened\n  bool isOpen();\n\n  // retrieve currently received sample point\n  const LidarPoint &amp;getCurrentPoint();\n\n  // try to reconnect in case of failure\n  void reconnect();\n\n  // data acquisition loop\n  const void loop();\n\n  // ask the lidar for its health info\n  u_result getHealth(lidar_response_device_health_t &amp;healthinfo,\n                     _u32 timeout = LIDAR_TIMEOUT);\n\n  // ask the lidar for its device info like the serial number\n  u_result getDeviceInfo(lidar_response_device_info_t &amp;info,\n                         _u32 timeout = LIDAR_TIMEOUT);\n\n  // start the measurement operation\n  u_result startScan(bool force = false, _u32 timeout = LIDAR_TIMEOUT * 2);\n\n  // stop the measurement operation\n  u_result stop();\n\n  // wait for one sample point to arrive\n  u_result scan(_u32 timeout = LIDAR_TIMEOUT);\n\n protected:\n  u_result _sendCommand(_u8 cmd, const void *payload, size_t payloadsize);\n  u_result _waitResponseHeader(lidar_ans_header_t *header, _u32 timeout);\n\n protected:\n  HardwareSerial *_bined_serialdev;\n  LidarPoint _currentMeasurement;\n  int _lidar_motor_pin;\n  int _lidar_speed;\n};\n\n// starts lidar service\nvoid startService(Lidar &amp;lidar);\n\n}  // namespace LIDAR\n</code></pre>"},{"location":"architecture/overview.html","title":"Overview","text":""},{"location":"architecture/overview.html#diagram-wip","title":"Diagram (WIP)","text":"<p>this is just a test of flowchart the flowchart below doesn't make any sense</p> <pre><code>flowchart LR\n    TaskManager --&gt; LiDAR_Task\n    TaskManager --&gt; Movement_Task\n    TaskManager --&gt; Executor_Task\n    TaskManager --&gt; Network_Task\n    TaskManager --&gt; Vision_Task\n    EQL[\"EQL Processor\"] --&gt; Movement_Task\n    Executor_Task &lt;--&gt; Network_Task\n    Executor_Task &lt;--&gt; Vision_Task\n    Executor_Task &lt;--&gt; LiDAR_Task</code></pre>"}]}