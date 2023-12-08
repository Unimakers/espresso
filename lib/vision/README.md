# ESPRESSO VISION

## Color Tracking (cv_trackColor)

### Description

cv_trackColor is an algorithm, it provides a simple interface that facilitate the object detection
using the color tracking technique.

### Example

Detect all plants in an image and return (X,Y) coordinates

```c
// create a new image
cv_image_t image;
// load pixels to image here
image.data = func_to_read_image();
image.height = func_image_height();
image.width = func_image_width();
image.channels = 3; // 3 for rgb, 1 for monochrome, 4 for rgba and so on...

// deterministic max points that can be detected in each image
cv_point_t plants[10000]; // a plant can be 2d point in an image,
// NOTE ! one or many pixels can represent a plant
// config
cv_config_t config = {
		// range for color tracking detection
        .min = {45, 15, 15}, // min hsv value
        .max = {120, 60, 45},	// max hsv value
		// accuracy of color detection
		// recommended 3 for 96px, 10 for 240px
        .accuracy = 3,
		// apply mask or not
        .applyMask = 0,
		// mask color
        .mask = RGB_BLACK,
		// object detected mask color
        .object = RGB_GREEN,
    };


// track color in an image as a form of object detection
// total is the number of pixels that belongs to a detected object
int total = cv_trackColor(&image, plants, config);

// function that draws crosshair on top of every plant in the list
cv_drawCrosshair(&image, plants, total, 2/*crosshair length*/);

//... do more processing here

// free the buffer here for reuse
free(image.data)
```
