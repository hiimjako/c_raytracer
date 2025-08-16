#ifndef MATH_H
#define MATH_H

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef PI
#define PI 3.14159265359
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

// Returns a random real in [0,1).
inline double random_double_0_1() { return rand() / (RAND_MAX + 1.0); }

// Returns a random real in [min,max).
inline double random_double_range(double min, double max) {
    return min + (max - min) * random_double_0_1();
}

typedef struct {
    double min, max;
} Interval;

Interval interval_create(double min, double max);

double interval_size(const Interval i);
bool interval_contains(const Interval i, double x);
bool interval_surrounds(const Interval i, double x);
double interval_clamp(const Interval i, double x);

#endif
