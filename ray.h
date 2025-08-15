#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
  vec3 origin;
  vec3 direction;
} ray;

/**
 * Creates and initializes a ray from an origin point and a direction vector.
 */
inline ray ray_create(vec3 origin, vec3 direction) {
  ray r = {origin, direction};
  return r;
}

/**
 * Computes the point on the ray at a given parameter 't'.
 * This is equivalent to `origin + t*direction`.
 */
inline vec3 ray_at(ray r, double t) {
  vec3 scaled_direction = vec3_scale(r.direction, t);
  return vec3_add(r.origin, scaled_direction);
}

#endif
