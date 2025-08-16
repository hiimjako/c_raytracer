#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "math.h"
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    Point3 point;
    Vec3 normal;
    double t;
    bool front_face;
} Hit;

void geometry_hit_set_face_normal(Hit *hit, const Ray ray,
                                  const Vec3 outward_normal);

typedef struct {
    Vec3 center;
    double radius;
} Sphere;

Sphere geometry_sphere_create(Vec3 center, double radius);
bool geometry_sphere_intersect(const Ray ray, const Sphere sphere,
                               Interval ray_t, Hit *hit);

#endif
