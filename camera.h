#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include "ray.h"
#include "world.h"
#include <stdint.h>
#include <stdio.h>

typedef struct {
    int image_height;
    int image_width;
    double aspect_ratio;
    double samples_per_pixel;
    double pixel_samples_scale;
    Point3 center;
    Point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
} Camera;

Camera camera_create(double aspect_ratio, int image_width,
                     int samples_per_pixel);
Color3 camera_ray_color(const Ray ray, const World *world);
Ray camera_get_ray(Camera camera, int i, int j);

#endif
