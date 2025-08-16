#include "camera.h"
#include "math.h"
#include "ray.h"
#include "vec3.h"

Camera camera_create(double aspect_ratio, int image_width,
                     int samples_per_pixel) {
    // Calculate the image height, and ensure that it's at least 1.
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * ((double)image_width / image_height);

    double pixel_samples_scale = 1.0 / samples_per_pixel;
    Point3 center = vec3_create_zero();

    // Calculate the vectors across the horizontal and down the vertical
    // viewport edges.
    Vec3 viewport_u = vec3_create(viewport_width, 0, 0);
    Vec3 viewport_v = vec3_create(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vec3 pixel_delta_u = vec3_divide(viewport_u, image_width);
    Vec3 pixel_delta_v = vec3_divide(viewport_v, image_height);

    // Calculate the location of the upper left pixel.
    Vec3 viewport_upper_left =
        vec3_subtract(center, vec3_add(vec3_create(0, 0, focal_length),
                                       vec3_add(vec3_divide(viewport_u, 2),
                                                vec3_divide(viewport_v, 2))));

    Vec3 pixel00_loc =
        vec3_add(viewport_upper_left,
                 vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

    Camera camera = {
        image_height,      image_width,         aspect_ratio,
        samples_per_pixel, pixel_samples_scale, center,
        pixel00_loc,       pixel_delta_u,       pixel_delta_v,
    };

    return camera;
}

Color3 camera_ray_color(const Ray ray, const World *world) {
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

Vec3 sample_square() {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
    // square.
    return vec3_create(random_double_0_1() - 0.5, random_double_0_1() - 0.5, 0);
}

Ray camera_get_ray(Camera camera, int i, int j) {
    // Construct a camera ray originating from the origin and directed at
    // randomly sampled point around the pixel location i, j.

    Vec3 offset = sample_square();
    Vec3 pixel_sample =
        vec3_add(camera.pixel00_loc,
                 vec3_add(vec3_scale(camera.pixel_delta_u, i + offset.x),
                          vec3_scale(camera.pixel_delta_v, j + offset.y)));

    Vec3 ray_origin = camera.center;
    Vec3 ray_direction = vec3_subtract(pixel_sample, ray_origin);

    return ray_create(ray_origin, ray_direction);
}
