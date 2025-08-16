#include "camera.h"
#include "geometry.h"
#include "math.h"
#include "ray.h"
#include "renderer.h"
#include "vec3.h"
#include "world.h"
#include <time.h>

double hit_sphere(const Point3 center, double radius, const Ray r) {
    Vec3 oc = vec3_subtract(center, r.origin);
    double a = vec3_length_squared(r.direction);
    double h = vec3_dot(r.direction, oc);
    double c = vec3_length_squared(oc) - radius * radius;
    double discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant)) / a;
    }
}

int main(void) {
    srand(time(0));

    // World
    World *world = world_create();
    world_add(world, geometry_sphere_create(vec3_create(0, 0, -1), 0.5));
    world_add(world, geometry_sphere_create(vec3_create(0, -100.5, -1), 100));

    Camera camera = camera_create(16.0 / 9.0, 400, 100);
    Renderer *renderer = create_kitty_renderer();

    render(camera, world, renderer);
    destroy_renderer(renderer);
    world_destroy(world);

    return 0;
}
