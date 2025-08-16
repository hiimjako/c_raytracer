#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

/*
 * Represents a 3D vector.
 */
typedef struct {
  double x, y, z;
} vec3;

typedef vec3 point3;

/*
 * Creates and initializes a vec3 with the given components.
 */
inline vec3 vec3_create(double x, double y, double z) {
  vec3 v = {x, y, z};
  return v;
}

/*
 * Creates a new vec3 with all components set to zero.
 */
inline vec3 vec3_create_zero() { return vec3_create(0.0, 0.0, 0.0); }

/*
 * Adds two vectors component-wise.
 */
inline vec3 vec3_add(vec3 u, vec3 v) {
  return vec3_create(u.x + v.x, u.y + v.y, u.z + v.z);
}

/*
 * Subtracts two vectors component-wise.
 */
inline vec3 vec3_subtract(vec3 u, vec3 v) {
  return vec3_create(u.x - v.x, u.y - v.y, u.z - v.z);
}

/*
 * Multiplies two vectors component-wise.
 */
inline vec3 vec3_multiply(vec3 u, vec3 v) {
  return vec3_create(u.x * v.x, u.y * v.y, u.z * v.z);
}

/*
 * Scales a vector by a scalar value.
 */
inline vec3 vec3_scale(vec3 v, double t) {
  return vec3_create(t * v.x, t * v.y, t * v.z);
}

/*
 * Divides a vector by a scalar value.
 */
inline vec3 vec3_divide(vec3 v, double t) { return vec3_scale(v, 1.0 / t); }

/*
 * Negates a vector.
 */
inline vec3 vec3_negate(vec3 v) { return vec3_scale(v, -1.0); }

/*
 * Computes the dot product of two vectors.
 */
inline double vec3_dot(vec3 u, vec3 v) {
  return u.x * v.x + u.y * v.y + u.z * v.z;
}

/*
 * Computes the cross product of two vectors.
 */
inline vec3 vec3_cross(vec3 u, vec3 v) {
  return vec3_create(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                     u.x * v.y - u.y * v.x);
}

/*
 * Computes the squared length (magnitude) of a vector.
 */
inline double vec3_length_squared(vec3 v) { return vec3_dot(v, v); }

/*
 * Computes the length (magnitude) of a vector.
 */
inline double vec3_length(vec3 v) { return sqrt(vec3_length_squared(v)); }

/*
 * Normalizes a vector to a unit vector.
 */
inline vec3 vec3_unit_vector(vec3 v) { return vec3_divide(v, vec3_length(v)); }

/*
 * Prints the components of a vector to a specified file stream.
 */
inline void vec3_print(FILE *stream, vec3 v) {
  fprintf(stream, "%f %f %f", v.x, v.y, v.z);
}

#endif
