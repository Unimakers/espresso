#pragma once

#include <types.h>

#define LIDAR_CMD_SYNC_BYTE 0xA5
#define LIDAR_CMDFLAG_HAS_PAYLOAD 0x80

#define LIDAR_ANS_SYNC_BYTE1 0xA5
#define LIDAR_ANS_SYNC_BYTE2 0x5A

#define LIDAR_ANS_PKTFLAG_LOOP 0x1

#if defined(_WIN32)
#pragma pack(1)
#endif

typedef struct _lidar_cmd_packet_t {
  _u8 syncByte;  // must be LIDAR_CMD_SYNC_BYTE
  _u8 cmd_flag;
  _u8 size;
  _u8 data[0];
} __attribute__((packed)) lidar_cmd_packet_t;

typedef struct _lidar_ans_header_t {
  _u8 syncByte1;  // must be LIDAR_ANS_SYNC_BYTE1
  _u8 syncByte2;  // must be LIDAR_ANS_SYNC_BYTE2
  _u32 size : 30;
  _u32 subType : 2;
  _u8 type;
} __attribute__((packed)) lidar_ans_header_t;

#if defined(_WIN32)
#pragma pack()
#endif
