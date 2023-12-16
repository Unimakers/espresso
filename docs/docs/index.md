## Overview

```none


 ______                                     _______          _ _    _ _
|  ____|                                   |__   __|        | | |  (_) |
| |__   ___ _ __  _ __ ___  ___ ___  ___      | | ___   ___ | | | ___| |_
|  __| / __| '_ \| '__/ _ \/ __/ __|/ _ \     | |/ _ \ / _ \| | |/ / | __|
| |____\__ \ |_) | | |  __/\__ \__ \ (_) |    | | (_) | (_) | |   <| | |_
|______|___/ .__/|_|  \___||___/___/\___/     |_|\___/ \___/|_|_|\_\_|\__|
           | |
           |_|


```

## What is this library ?

Espresso is a Simple and lightweight yet effective robotics toolkit and a package of libraries aimed to stop reinvinting the wheel when building robotics software, it is designed specifically to run on Espressif's SOCs (ESP32-ESP32-S3), it includes common algorithm used in robotics, from controlling servos to object detection

## Why the name ?

Who doesn't love the life juice aka coffee, and espresso is helluva an efficient drink, thus the name esp32 + espresso

## How can i use it in my program ?

Well unfortunately you can't, it's not yet optimized and stable yet to be used by other people,
But, you can always look at the code, it's simple and no magic stuff, CTRL+C / CTRL+V is your friend.
The modules are decoupled from each other so you only copy the library you want.

## Why building a new library only for ESP32 ?

The only best bang for buck microcontroller out there is ESP32 (looking at you stm32).
WiFi/BT + two of more than enough cpu cores + active community + great docs < than 5$ thats too good to be true that just happens to be true.

## What features would be included in this library ?

I just wish if we have limitless time, I would implement anything i could think of, but here is an non exhaustive list of features that will be included in the next following month (freezed features) and some of my wishlist.

| Feature          | Status   |
| ---------------- | -------- |
| LiDAR            | Oct-Dec  |
| Steppers         | Oct-Dec  |
| Servos           | Oct-Dec  |
| I2C Bus          | Oct-Dec  |
| EQL              | Done     |
| Color Tracking   | Done     |
| TFlite inference | WishList |
| Mesh Network     | WishList |
| OLED Display     | WishList |
| TFT Display      | WishList |
