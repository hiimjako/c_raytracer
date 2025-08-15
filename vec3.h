#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

/*
 * Represents a 3D vector.
 */
typedef struct {
  double e[3];
} vec3;

inline double vec3_x(vec3 v) { return v.e[0]; }
inline double vec3_y(vec3 v) { return v.e[1]; }
inline double vec3_z(vec3 v) { return v.e[2]; }

/*
 * Creates and initializes a vec3 with the given components.
 */
inline vec3 vec3_create(double e0, double e1, double e2) {
  vec3 v = {{e0, e1, e2}};
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
  return vec3_create(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

/*
 * Subtracts two vectors component-wise.
 */
inline vec3 vec3_subtract(vec3 u, vec3 v) {
  return vec3_create(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

/*
 * Multiplies two vectors component-wise.
 */
inline vec3 vec3_multiply(vec3 u, vec3 v) {
  return vec3_create(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

/*
 * Scales a vector by a scalar value.
 */
inline vec3 vec3_scale(vec3 v, double t) {
  return vec3_create(t * v.e[0], t * v.e[1], t * v.e[2]);
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
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

/*
 * Computes the cross product of two vectors.
 */
inline vec3 vec3_cross(vec3 u, vec3 v) {
  return vec3_create(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                     u.e[2] * v.e[0] - u.e[0] * v.e[2],
                     u.e[0] * v.e[1] - u.e[1] * v.e[0]);
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
  fprintf(stream, "%f %f %f", v.e[0], v.e[1], v.e[2]);
}

#endif
