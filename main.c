#include "color.h"
#include "geometry.h"
#include "ray.h"
#include "vec3.h"
#include "world.h"
#include <stdio.h>
#include "math.h"

double hit_sphere(const Point3 center, double radius, const Ray r) {
    Vec3 oc = vec3_subtract(center , r.origin);
    double a = vec3_length_squared(r.direction);
    double h = vec3_dot(r.direction, oc);
    double c = vec3_length_squared(oc) - radius*radius; 
    double discriminant = h*h - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant) ) / a;
    }
}

Color3 ray_color(const Ray ray, const World* world) {
  Hit hit;
  if (world_hit(world, ray, interval_create(0, INFINITY), &hit)) {
    return vec3_scale(vec3_add(hit.normal, vec3_create(1, 1, 1)), 0.5);
  } 

  Vec3 unit_direction = vec3_unit_vector(ray.direction);
  double a = 0.5 * (unit_direction.y + 1.0);
  double scaled_a = (1.0 - a);

  // lerp interpolation function
  Vec3 start_value = vec3_create(1.0, 1.0, 1.0);
  Vec3 end_value = vec3_scale(vec3_create(0.5, 0.7, 1.0), a);
  Vec3 blended_value = vec3_scale(start_value, scaled_a);
  blended_value = vec3_add(blended_value, end_value);
  return blended_value;
}

int main(void) {
  // Image
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // Calculate the image height, and ensure that it's at least 1.
  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;
  
  // World
  World* world = world_create();
  world_add(world, geometry_sphere_create(vec3_create(0, 0, -1), 0.5));
  world_add(world, geometry_sphere_create(vec3_create(0, -100.5, -1), 100));

  // Camera
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * ((double)image_width / image_height);
  Point3 camera_center = vec3_create_zero();

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  Vec3 viewport_u = vec3_create(viewport_width, 0, 0);
  Vec3 viewport_v = vec3_create(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  Vec3 pixel_delta_u = vec3_divide(viewport_u, image_width);
  Vec3 pixel_delta_v = vec3_divide(viewport_v, image_height);

  // Calculate the location of the upper left pixel.
  Vec3 viewport_upper_left = vec3_subtract(
            camera_center, 
            vec3_add(
                vec3_create(0, 0, focal_length),
                vec3_add(
                    vec3_divide(viewport_u, 2),
                    vec3_divide(viewport_v, 2))
                ));

  Vec3 pixel00_loc = vec3_add(
          viewport_upper_left,
          vec3_scale(
              vec3_add(pixel_delta_u, pixel_delta_v), 
              0.5));

  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++) {
    for (int i = 0; i < image_width; i++) {
      Vec3 pixel_center = vec3_add(pixel00_loc, 
              vec3_add(vec3_scale(pixel_delta_u, i), vec3_scale(pixel_delta_v, j)));

      Vec3 ray_direction = vec3_subtract(pixel_center, camera_center);
      Ray r = ray_create(camera_center, ray_direction);
      Color3 pixel_color = ray_color(r, world);
      write_color(stdout, pixel_color);
    }
  }

  world_destroy(world);

  return 0;
}
