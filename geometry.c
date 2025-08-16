#include "geometry.h"
#include "math.h"
#include "vec3.h"

void geometry_hit_set_face_normal(Hit *hit, const Ray ray,
                                  const Vec3 outward_normal) {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    hit->front_face = vec3_dot(ray.direction, outward_normal) < 0;
    hit->normal =
        hit->front_face ? outward_normal : vec3_scale(outward_normal, -1);
}

Sphere geometry_sphere_create(Vec3 center, double radius) {
    Sphere s = {center, .radius = MAX(0, radius)};
    return s;
}

bool geometry_sphere_intersect(const Ray ray, const Sphere sphere,
                               Interval ray_t, Hit *hit) {
    Vec3 oc = vec3_subtract(sphere.center, ray.origin);
    double a = vec3_length_squared(ray.direction);
    double h = vec3_dot(ray.direction, oc);
    double c = vec3_length_squared(oc) - sphere.radius * sphere.radius;
    double discriminant = h * h - a * c;

    if (discriminant < 0)
        return false;

    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (h - sqrtd) / a;
    if (!interval_surrounds(ray_t, root)) {
        root = (h + sqrtd) / a;
        if (!interval_surrounds(ray_t, root)) {
            return false;
        }
    }

    hit->t = root;
    hit->point = ray_at(ray, hit->t);
    Vec3 outward_normal =
        vec3_divide(vec3_subtract(hit->point, sphere.center), sphere.radius);
    geometry_hit_set_face_normal(hit, ray, outward_normal);

    return true;
}
