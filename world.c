#include "world.h"
#include "math.h"

World *world_create() {
    World *list = (World *)malloc(sizeof(World));
    if (list == NULL)
        return NULL;

    list->data = (Sphere *)malloc(sizeof(Sphere) * 2);
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    list->size = 0;
    list->capacity = 2;

    return list;
}

void world_destroy(World *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

void world_add(World *list, Sphere object) {
    if (list == NULL)
        return;

    if (list->size == list->capacity) {
        list->capacity *= 2;
        Sphere *new_data =
            (Sphere *)realloc(list->data, sizeof(Sphere) * list->capacity);
        if (new_data == NULL) {
            // Handle realloc failure
            fprintf(stderr, "Failed to reallocate hittable list\n");
            return;
        }
        list->data = new_data;
    }
    list->data[list->size++] = object;
}

bool world_hit(const World *list, const Ray ray, Interval ray_t, Hit *hit) {
    if (list == NULL)
        return false;

    Hit temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (size_t i = 0; i < list->size; ++i) {
        Sphere sphere = list->data[i];
        if (geometry_sphere_intersect(
                ray, sphere, interval_create(ray_t.min, closest_so_far),
                &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *hit = temp_rec;
        }
    }
    return hit_anything;
}
