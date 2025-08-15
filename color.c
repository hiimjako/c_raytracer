#include "color.h"

void write_color(FILE *stream, const color3 pixel_color) {
  double r = vec3_x(pixel_color);
  double g = vec3_y(pixel_color);
  double b = vec3_z(pixel_color);

  // Translate the [0,1] component values to the byte range [0,255].
  int rbyte = (int)255.999 * r;
  int gbyte = (int)255.999 * g;
  int bbyte = (int)255.999 * b;

  fprintf(stream, "%d %d %d\n", rbyte, gbyte, bbyte);
}
