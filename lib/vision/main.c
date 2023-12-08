#include "draw.h"
#include "vision.h"
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#include <stdio.h>
#include <time.h>

int test() {
  const char *files[4] = {"../test/1.jpg", "../test/2.jpg", "../test/3.jpg",
                          "../test/4.jpg"};
  cv_image_t image;
  for (int i = 0; i < 4; i++) {
    image.data =
        stbi_load(files[i], &image.width, &image.height, &image.channels, 3);
    if (image.data == NULL) {
      printf("couldn't load image \n");
      exit(0);
    }
    clock_t start_time = clock();
    cv_point_t points[10000];
    cv_config_t config = {
        .min = {45, 15, 15},
        .max = {120, 60, 45},
        .accuracy = 3,
        .applyMask = 0,
        .mask = RGB_BLACK,
        .object = RGB_GREEN,
    };
    int total = cv_trackColor(&image, points, config);
    cv_drawCrosshair(&image, points, total, 2);
    clock_t end_time = clock();
    double elapsed_time =
        (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    printf("elapsed time: %.1f ms - %d.png\n", elapsed_time, i);
    char str[80];
    sprintf(str, "../test/mask-%d.png", i);
    stbi_write_png(str, image.width, image.height, image.channels, image.data,
                   0);
    stbi_image_free(image.data);
  }
  return 0;
}

int main() { test(); }