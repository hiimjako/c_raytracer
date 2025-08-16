#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "ray.h"
#include "geometry.h"
#include "world.h"

typedef struct {
  int    image_height;   
  int    image_width;
  double aspect_ratio;
  Point3 center;         
  Point3 pixel00_loc;   
  Vec3   pixel_delta_u;
  Vec3   pixel_delta_v;
} Camera;

Camera camera_create(double aspect_ratio, int image_width);
Color3 camera_ray_color(const Ray ray, const World* world);
void camera_render(Camera camera, const World* world);

#endif
