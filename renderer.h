#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "math.h"
#include "vec3.h"

// Renderer interface
typedef struct {
    void (*begin_render)(int width, int height, void *context);
    void (*write_pixel)(const Color3 *pixel_color, void *context);
    void (*end_render)(void *context);
    void (*cleanup)(void *context);
    void *context;
} Renderer;

Renderer *create_ppm_renderer(FILE *output_stream);
Renderer *create_kitty_renderer(void);
Renderer *create_kitty_chunked_renderer(void);

void render(Camera camera, const World *world, Renderer *renderer);
void destroy_renderer(Renderer *renderer);

#endif
