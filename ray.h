#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

/**
 * Creates and initializes a ray from an origin point and a direction vector.
 */
inline Ray ray_create(Vec3 origin, Vec3 direction) {
    Ray r = {origin, direction};
    return r;
}

/**
 * Computes the point on the ray at a given parameter 't'.
 * This is equivalent to `origin + t*direction`.
 */
inline Vec3 ray_at(Ray r, double t) {
    Vec3 scaled_direction = vec3_scale(r.direction, t);
    return vec3_add(r.origin, scaled_direction);
}

#endif
