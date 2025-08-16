#include "color.h"

void write_color(FILE *stream, const Color3 pixel_color) {
  double r = pixel_color.x;
  double g = pixel_color.y;
  double b = pixel_color.z;

  // Translate the [0,1] component values to the byte range [0,255].
  int rbyte = (int)255.999 * r;
  int gbyte = (int)255.999 * g;
  int bbyte = (int)255.999 * b;

  fprintf(stream, "%d %d %d\n", rbyte, gbyte, bbyte);
}
