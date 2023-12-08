#pragma once

#include "vision.h"

void cv_drawCrosshair(struct cv_image_t *image, struct cv_point_t *points,
                      int len, int crosshair_size);