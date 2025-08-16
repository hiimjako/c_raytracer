#ifndef WORLD_H
#define WORLD_H

#include "geometry.h"
#include "math.h"

typedef struct {
    Sphere *data;
    size_t size;
    size_t capacity;
} World;

World *world_create();
void world_destroy(World *list);
void world_add(World *list, Sphere object);
bool world_hit(const World *list, const Ray r, Interval ray_t, Hit *hit);

#endif
