#include "vision.h"

// compares distance between two points,
// returns true if distance is smaller than the given distance
int cv_isSameObj(struct cv_point_t *a, struct cv_point_t *b, int distance) {
  int d_x = a->x - b->x;
  int d_y = a->y - b->y;
  if (d_x < 0)
    d_x = d_x * -1;
  if (d_y < 0)
    d_y = d_y * -1;
  int d = d_x + d_y;
  if (d <= distance) {
    return 1;
  }
  return 0;
}

// swap two points
void cv_swapPt(cv_point_t *a, cv_point_t *b) {
  cv_point_t temp = *a;
  *a = *b;
  *b = temp;
}

// compare two points depending on the distance from the origin
// using manhattan distance
int cv_cmpPt(cv_point_t *a, cv_point_t *b) {
  int d_a = a->x + a->y;
  int d_b = b->x + b->y;
  if (d_a < 0)
    d_a *= -1;
  if (d_b < 0)
    d_b *= -1;
  if (d_a > d_b)
    return 1;
  return 0;
}

// bubble sort an array of points
void cv_sortPts(cv_point_t points[], int len) {
  int swapped;
  for (int i = 0; i < len - 1; i++) {
    swapped = 1;
    for (int j = 0; j < len - i - 1; j++) {
      if (cv_cmpPt(&points[j], &points[j + 1])) {
        cv_swapPt(&points[j], &points[j + 1]);
        swapped = 0;
      }
    }
    if (!swapped)
      break;
  }
}

int cv_trackColor(cv_image_t *image, cv_point_t *points, cv_config_t config) {
  cv_rgb_t avg = {0, 0, 0};
  cv_rgb_t sum = {0, 0, 0};
  cv_hsv_t hsv = {0, 0, 0};
  points[0].x = 0;
  points[0].y = 0;
  int index = 0;
  for (int by = 0; by < image->height; by += config.accuracy) {
    for (int bx = 0; bx < image->width; bx += config.accuracy) {
      sum.r = 0;
      sum.g = 0;
      sum.b = 0;
      for (int y = by; y < by + config.accuracy; y++) {
        for (int x = bx; x < bx + config.accuracy; x++) {
          int i = y * image->width * image->channels + x * image->channels + 0;
          int j = y * image->width * image->channels + x * image->channels + 1;
          int k = y * image->width * image->channels + x * image->channels + 2;
          sum.r += (int)image->data[i];
          sum.g += (int)image->data[j];
          sum.b += (int)image->data[k];
        }
      }
      avg.r = sum.r / (config.accuracy * config.accuracy);
      avg.b = sum.b / (config.accuracy * config.accuracy);
      avg.g = sum.g / (config.accuracy * config.accuracy);
      cv_convRgb2Hsv(&avg, &hsv);
      if (cv_inColorRange(&hsv, config.min, config.max)) {
        for (int y = by; y < by + config.accuracy; y++) {
          for (int x = bx; x < bx + config.accuracy; x++) {
            int i =
                y * image->width * image->channels + x * image->channels + 0;
            int j =
                y * image->width * image->channels + x * image->channels + 1;
            int k =
                y * image->width * image->channels + x * image->channels + 2;
            image->data[i] = config.object.r;
            image->data[j] = config.object.g;
            image->data[k] = config.object.b;
          }
        }
        cv_point_t object = {(bx + config.accuracy / 2),
                             (by + config.accuracy / 2)};
        // calculate the average x,y which is the center of the plant
        if (cv_isSameObj(&object, &points[index - 1], config.accuracy)) {
          points[index].x = (points[index].x + points[index - 1].x) / 2;
          points[index].y = (points[index].y + points[index - 1].y) / 2;
        } else {
          points[index].x = object.x;
          points[index].y = object.y;
          index += 1;
        };
      } else if (config.applyMask) {
        for (int y = by; y < by + config.accuracy; y++) {
          for (int x = bx; x < bx + config.accuracy; x++) {
            int i =
                y * image->width * image->channels + x * image->channels + 0;
            int j =
                y * image->width * image->channels + x * image->channels + 1;
            int k =
                y * image->width * image->channels + x * image->channels + 2;
            image->data[i] = config.mask.r;
            image->data[j] = config.mask.r;
            image->data[k] = config.mask.r;
          }
        }
      }
    }
  }
  return index;
}
