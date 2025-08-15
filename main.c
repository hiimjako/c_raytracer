#include "color.h"
#include "vec3.h"
#include <stdio.h>

int main(void) {
  int image_width = 256;
  int image_height = 256;

  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (int i = 0; i < image_width; i++) {
    for (int j = 0; j < image_width; j++) {
      color3 pixel_color = vec3_create((double)i / (image_width - 1),
                                       (double)j / (image_height - 1), 0.0);

      write_color(stdout, pixel_color);
    }
  }

  return 0;
}
