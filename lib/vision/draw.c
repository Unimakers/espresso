// #include "draw.h"

// void cv_drawCrosshair(cv_image_t *image, cv_point_t *plants, int len,
//                       int crosshair_size) {
//   for (int i = 0; i < len; i++) {
//     for (int e = 0; e < crosshair_size; e++) {
//       int x = plants[i].x - e;
//       int y = plants[i].y - e;
//       int x1 = plants[i].x + e;
//       int y1 = plants[i].y + e;
//       int i = y * image->width * image->channels + x * image->channels + 0;
//       int j = y * image->width * image->channels + x * image->channels + 1;
//       int k = y * image->width * image->channels + x * image->channels + 2;
//       int i1 = y1 * image->width * image->channels + x1 * image->channels + 0;
//       int j1 = y1 * image->width * image->channels + x1 * image->channels + 1;
//       int k1 = y1 * image->width * image->channels + x1 * image->channels + 2;
//       int i2 = y * image->width * image->channels + x1 * image->channels + 0;
//       int j2 = y * image->width * image->channels + x1 * image->channels + 1;
//       int k2 = y * image->width * image->channels + x1 * image->channels + 2;
//       int i3 = y1 * image->width * image->channels + x * image->channels + 0;
//       int j3 = y1 * image->width * image->channels + x * image->channels + 1;
//       int k3 = y1 * image->width * image->channels + x * image->channels + 2;
//       image->data[i] = 255;
//       image->data[j] = 0;
//       image->data[k] = 0;
//       image->data[i1] = 255;
//       image->data[j1] = 0;
//       image->data[k1] = 0;
//       image->data[i2] = 255;
//       image->data[j2] = 0;
//       image->data[k2] = 0;
//       image->data[i3] = 255;
//       image->data[j3] = 0;
//       image->data[k3] = 0;
//     }
//   }
// }
