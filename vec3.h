#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

/*
 * Represents a 3D vector.
 */
typedef struct {
  double x, y, z;
} Vec3;

typedef Vec3 Point3;

/*
 * Creates and initializes a vec3 with the given components.
 */
inline Vec3 vec3_create(double x, double y, double z) {
  Vec3 v = {x, y, z};
  return v;
}

/*
 * Creates a new vec3 with all components set to zero.
 */
inline Vec3 vec3_create_zero() { return vec3_create(0.0, 0.0, 0.0); }

/*
 * Adds two vectors component-wise.
 */
inline Vec3 vec3_add(Vec3 u, Vec3 v) {
  return vec3_create(u.x + v.x, u.y + v.y, u.z + v.z);
}

/*
 * Subtracts two vectors component-wise.
 */
inline Vec3 vec3_subtract(Vec3 u, Vec3 v) {
  return vec3_create(u.x - v.x, u.y - v.y, u.z - v.z);
}

/*
 * Multiplies two vectors component-wise.
 */
inline Vec3 vec3_multiply(Vec3 u, Vec3 v) {
  return vec3_create(u.x * v.x, u.y * v.y, u.z * v.z);
}

/*
 * Scales a vector by a scalar value.
 */
inline Vec3 vec3_scale(Vec3 v, double t) {
  return vec3_create(t * v.x, t * v.y, t * v.z);
}

/*
 * Divides a vector by a scalar value.
 */
inline Vec3 vec3_divide(Vec3 v, double t) { return vec3_scale(v, 1.0 / t); }

/*
 * Negates a vector.
 */
inline Vec3 vec3_negate(Vec3 v) { return vec3_scale(v, -1.0); }

/*
 * Computes the dot product of two vectors.
 */
inline double vec3_dot(Vec3 u, Vec3 v) {
  return u.x * v.x + u.y * v.y + u.z * v.z;
}

/*
 * Computes the cross product of two vectors.
 */
inline Vec3 vec3_cross(Vec3 u, Vec3 v) {
  return vec3_create(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                     u.x * v.y - u.y * v.x);
}

/*
 * Computes the squared length (magnitude) of a vector.
 */
inline double vec3_length_squared(Vec3 v) { return vec3_dot(v, v); }

/*
 * Computes the length (magnitude) of a vector.
 */
inline double vec3_length(Vec3 v) { return sqrt(vec3_length_squared(v)); }

/*
 * Normalizes a vector to a unit vector.
 */
inline Vec3 vec3_unit_vector(Vec3 v) { return vec3_divide(v, vec3_length(v)); }

/*
 * Prints the components of a vector to a specified file stream.
 */
inline void vec3_print(FILE *stream, Vec3 v) {
  fprintf(stream, "%f %f %f", v.x, v.y, v.z);
}

#endif
