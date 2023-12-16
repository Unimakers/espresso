#pragma once

#include "protocol.h"

// Commands
//-----------------------------------------

// Commands without payload and response
#define LIDAR_CMD_STOP 0x25
#define LIDAR_CMD_SCAN 0x20
#define LIDAR_CMD_FORCE_SCAN 0x21
#define LIDAR_CMD_RESET 0x40

// Commands without payload but have response
#define LIDAR_CMD_GET_DEVICE_INFO 0x50
#define LIDAR_CMD_GET_DEVICE_HEALTH 0x52

#if defined(_WIN32)
#pragma pack(1)
#endif

// Response
// ------------------------------------------
#define LIDAR_ANS_TYPE_MEASUREMENT 0x81

#define LIDAR_ANS_TYPE_DEVINFO 0x4
#define LIDAR_ANS_TYPE_DEVHEALTH 0x6

#define LIDAR_STATUS_OK 0x0
#define LIDAR_STATUS_WARNING 0x1
#define LIDAR_STATUS_ERROR 0x2

#define LIDAR_RESP_MEASUREMENT_SYNCBIT (0x1 << 0)
#define LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT 2
#define LIDAR_RESP_MEASUREMENT_CHECKBIT (0x1 << 0)
#define LIDAR_RESP_MEASUREMENT_ANGLE_SHIFT 1

typedef struct _lidar_response_measurement_node_t {
  _u8 sync_quality;        // syncbit:1;syncbit_inverse:1;quality:6;
  _u16 angle_q6_checkbit;  // check_bit:1;angle_q6:15;
  _u16 distance_q2;
} __attribute__((packed)) lidar_response_measurement_node_t;

typedef struct _lidar_response_device_info_t {
  _u8 model;
  _u16 firmware_version;
  _u8 hardware_version;
  _u8 serialnum[16];
} __attribute__((packed)) lidar_response_device_info_t;

typedef struct _lidar_response_device_health_t {
  _u8 status;
  _u16 error_code;
} __attribute__((packed)) lidar_response_device_health_t;

#if defined(_WIN32)
#pragma pack()
#endif
