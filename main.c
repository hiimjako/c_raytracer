#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>

int hit_sphere(const point3 center, double radius, const ray r) {
    vec3 oc = vec3_subtract(center , r.origin);
    double a = vec3_dot(r.direction, r.direction);
    double b = -2.0 * vec3_dot(r.direction, oc);
    double c = vec3_dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color3 ray_color(const ray r) {
  if (hit_sphere(vec3_create(0,0,-1), 0.5, r) == 1)
    return vec3_create(1, 0, 0);

  vec3 unit_direction = vec3_unit_vector(r.direction);
  double a = 0.5 * (vec3_y(unit_direction) + 1.0);
  double scaled_a = (1.0 - a);

  // lerp interpolation function
  vec3 start_value = vec3_create(1.0, 1.0, 1.0);
  vec3 end_value = vec3_scale(vec3_create(0.5, 0.7, 1.0), a);
  vec3 blended_value = vec3_scale(start_value, scaled_a);
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

  // Camera
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * ((double)image_width / image_height);
  point3 camera_center = vec3_create_zero();

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  vec3 viewport_u = vec3_create(viewport_width, 0, 0);
  vec3 viewport_v = vec3_create(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_u = vec3_divide(viewport_u, image_width);
  vec3 pixel_delta_v = vec3_divide(viewport_v, image_height);

  // Calculate the location of the upper left pixel.
  vec3 viewport_upper_left = vec3_subtract(
            camera_center, 
            vec3_add(
                vec3_create(0, 0, focal_length),
                vec3_add(
                    vec3_divide(viewport_u, 2),
                    vec3_divide(viewport_v, 2))
                ));

  vec3 pixel00_loc = vec3_add(
          viewport_upper_left,
          vec3_scale(
              vec3_add(pixel_delta_u, pixel_delta_v), 
              0.5));

  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++) {
    for (int i = 0; i < image_width; i++) {
      vec3 pixel_center = vec3_add(pixel00_loc, 
              vec3_add(vec3_scale(pixel_delta_u, i), vec3_scale(pixel_delta_v, j)));

      vec3 ray_direction = vec3_subtract(pixel_center, camera_center);
      ray r = ray_create(camera_center, ray_direction);
      color3 pixel_color = ray_color(r);
      write_color(stdout, pixel_color);
    }
  }

  return 0;
}
