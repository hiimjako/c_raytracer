#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <float.h> 
#include <stdbool.h>

#ifndef PI
#define PI 3.14159265359
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

typedef struct {
    double min, max;
} Interval;

Interval interval_create(double min, double max);

double interval_size(const Interval i);
bool interval_contains(const Interval i, double x);
bool interval_surrounds(const Interval i, double x);

#endif
