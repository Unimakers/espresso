#include "colors.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define max3(a, b, c) max(max(a, b), c)
#define min3(a, b, c) min(min(a, b), c)

void cv_convRgb2Hsv(cv_rgb_t *rgb, cv_hsv_t *hsv) {
  rgb->r = rgb->r / 255;
  rgb->g = rgb->g / 255;
  rgb->b = rgb->b / 255;
  float maxc = max3(rgb->r, rgb->g, rgb->b);
  float minc = min3(rgb->r, rgb->g, rgb->b);
  float hue = 0.0;
  if (maxc == rgb->r) {
    hue = (rgb->g - rgb->b) / (maxc - minc);
  }
  if (maxc == rgb->g) {
    hue = 2.0 + (rgb->b - rgb->r) / (maxc - minc);
  }
  if (maxc == rgb->b) {
    hue = 4.0 + (rgb->r - rgb->g) / (maxc - minc);
  }
  hue = hue * 60;
  if (hue < 0)
    hue = hue + 360;
  hsv->h = hue;
  hsv->s = ((maxc - minc) / maxc) * 100;
  hsv->v = maxc * 100;
}

// returns true if the desired color is detected
int cv_inColorRange(cv_hsv_t *hsv, cv_hsv_t min, cv_hsv_t max) {
  if (hsv->s > min.s && hsv->s < max.s) {
    if (hsv->v > min.v && hsv->v < max.v) {
      if (hsv->h > min.h && hsv->h < max.h) {
        return 1;
      }
    }
  }
  return 0;
}