#pragma once

#include "colors.h"

typedef struct cv_image_t {
  unsigned char *data;
  int width;
  int height;
  int channels;
} cv_image_t;

typedef struct cv_point_t {
  int x;
  int y;
} cv_point_t;

typedef struct cv_config_t {
  cv_hsv_t max;
  cv_hsv_t min;
  int applyMask;
  int accuracy;
  cv_rgb_t mask;
  cv_rgb_t object;
  cv_rgb_t crosshair;
} cv_config_t;

int cv_isSameObj(struct cv_point_t *a, struct cv_point_t *b, int distance);

void cv_swapPt(cv_point_t *a, cv_point_t *b);

int cv_cmpPt(cv_point_t *a, cv_point_t *b);

void cv_sortPts(cv_point_t points[], int len);

int cv_trackColor(cv_image_t *image, cv_point_t *points, cv_config_t config);