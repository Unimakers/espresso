#pragma once

namespace vision {

struct Image {
  unsigned char *data;
  int width;
  int height;
  int channels;
};

struct Point {
  int x;
  int y;
};

class Color {
  void RGB(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
  };
  void HSV(int h, int s, int v) {
    this->h = h;
    this->s = s;
    this->v = v;
  }

 protected:
  int r = 0;
  int g = 0;
  int b = 0;
  int h = 0;
  int s = 0;
  int v = 0;
};

struct colorTrackerConfig {
  Color max;
  Color min;
  bool apply_mask;
  int accuracy;
  Color mask;
  Color object;
  Color crosshair;
};

class Vision {
 public:
  void TrackColor();
  void DetectObject();

 private:
  void sortPoints();
  void comparePoints();
};

}  // namespace vision

// int cv_isSameObj(struct cv_point_t *a, struct cv_point_t *b, int distance);

// void cv_swapPt(cv_point_t *a, cv_point_t *b);

// int cv_cmpPt(cv_point_t *a, cv_point_t *b);

// void cv_sortPts(cv_point_t points[], int len);

// int cv_trackColor(cv_image_t *image, cv_point_t *points, cv_config_t config);