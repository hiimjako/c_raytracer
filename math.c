#include "math.h"

Interval interval_create(double min, double max) {
    return (Interval){min, max};
}

double interval_size(const Interval i) { return i.max - i.min; }

bool interval_contains(const Interval i, double x) {
    return i.min <= x && x <= i.max;
}

bool interval_surrounds(const Interval i, double x) {
    return i.min < x && x < i.max;
}

double interval_clamp(const Interval i, double x) {
    if (x < i.min)
        return i.min;
    if (x > i.max)
        return i.max;
    return x;
}

const Interval INTERVAL_EMPTY = {+INFINITY, -INFINITY};
const Interval INTERVAL_UNIVERSE = {-INFINITY, +INFINITY};
