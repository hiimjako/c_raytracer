#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

typedef vec3 color3;

void write_color(FILE *stream, const color3 pixel_color);

#endif
