#include "renderer.h"
#include "camera.h"
#include "vec3.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * PPM Renderer Implementation
 */
typedef struct {
    FILE *stream;
    int pixels_written;
} PPMContext;

void ppm_begin_render(int width, int height, void *context) {
    PPMContext *ctx = (PPMContext *)context;
    fprintf(ctx->stream, "P3\n%d %d\n255\n", width, height);
    ctx->pixels_written = 0;
}

void ppm_write_pixel(const Color3 *pixel_color, void *context) {
    PPMContext *ctx = (PPMContext *)context;
    double r = pixel_color->x;
    double g = pixel_color->y;
    double b = pixel_color->z;

    // Translate the [0,1] component values to the byte range [0,255]
    const Interval intensity = interval_create(0.000, 0.999);
    int rbyte = (int)(256 * interval_clamp(intensity, r));
    int gbyte = (int)(256 * interval_clamp(intensity, g));
    int bbyte = (int)(256 * interval_clamp(intensity, b));

    fprintf(ctx->stream, "%d %d %d\n", rbyte, gbyte, bbyte);
    ctx->pixels_written++;
}

void ppm_end_render(void *context) {
    PPMContext *ctx = (PPMContext *)context;
    fflush(ctx->stream);
}

void ppm_cleanup(void *context) { free(context); }

Renderer *create_ppm_renderer(FILE *output_stream) {
    Renderer *renderer = malloc(sizeof(Renderer));
    PPMContext *context = malloc(sizeof(PPMContext));

    if (!renderer || !context) {
        free(renderer);
        free(context);
        return NULL;
    }

    context->stream = output_stream;
    context->pixels_written = 0;

    renderer->begin_render = ppm_begin_render;
    renderer->write_pixel = ppm_write_pixel;
    renderer->end_render = ppm_end_render;
    renderer->cleanup = ppm_cleanup;
    renderer->context = context;

    return renderer;
}

/*
 *  Kitty Graphics Protocol Utility Functions
 */
static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "0123456789+/";

char *base64_encode(const unsigned char *data, size_t input_length) {
    size_t output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_length + 1);
    if (encoded_data == NULL)
        return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 0 * 6) & 0x3F];
    }

    // Add padding
    size_t mod = input_length % 3;
    if (mod) {
        encoded_data[output_length - 1] = '=';
        if (mod == 1) {
            encoded_data[output_length - 2] = '=';
        }
    }

    encoded_data[output_length] = '\0';
    return encoded_data;
}

/*
 * Simple Kitty Renderer Implementation
 */
typedef struct {
    unsigned char *image_data;
    size_t buffer_size;
    size_t current_index;
    int width;
    int height;
} KittyContext;

void kitty_begin_render(int width, int height, void *context) {
    KittyContext *ctx = (KittyContext *)context;
    ctx->width = width;
    ctx->height = height;
    ctx->buffer_size = width * height * 3; // RGB
    ctx->image_data = malloc(ctx->buffer_size);
    ctx->current_index = 0;

    if (!ctx->image_data) {
        fprintf(stderr, "Failed to allocate image buffer\n");
    }
}

void kitty_write_pixel(const Color3 *pixel_color, void *context) {
    KittyContext *ctx = (KittyContext *)context;

    if (!ctx->image_data || ctx->current_index + 3 > ctx->buffer_size) {
        return;
    }

    double r = pixel_color->x;
    double g = pixel_color->y;
    double b = pixel_color->z;

    // Translate the [0,1] component values to the byte range [0,255]
    const Interval intensity = interval_create(0.000, 0.999);
    ctx->image_data[ctx->current_index++] =
        (unsigned char)(256 * interval_clamp(intensity, r));
    ctx->image_data[ctx->current_index++] =
        (unsigned char)(256 * interval_clamp(intensity, g));
    ctx->image_data[ctx->current_index++] =
        (unsigned char)(256 * interval_clamp(intensity, b));
}

void kitty_end_render(void *context) {
    KittyContext *ctx = (KittyContext *)context;

    if (!ctx->image_data)
        return;

    char *encoded_data = base64_encode(ctx->image_data, ctx->buffer_size);
    if (!encoded_data) {
        fprintf(stderr, "Failed to encode image data\n");
        return;
    }

    // Output entire image in one command
    printf("\033_Ga=T,f=24,s=%d,v=%d;%s\033\\", ctx->width, ctx->height,
           encoded_data);

    free(encoded_data);
    fflush(stdout);
}

void kitty_cleanup(void *context) {
    KittyContext *ctx = (KittyContext *)context;
    free(ctx->image_data);
    free(ctx);
}

Renderer *create_kitty_renderer(void) {
    Renderer *renderer = malloc(sizeof(Renderer));
    KittyContext *context = malloc(sizeof(KittyContext));

    if (!renderer || !context) {
        free(renderer);
        free(context);
        return NULL;
    }

    memset(context, 0, sizeof(KittyContext));

    renderer->begin_render = kitty_begin_render;
    renderer->write_pixel = kitty_write_pixel;
    renderer->end_render = kitty_end_render;
    renderer->cleanup = kitty_cleanup;
    renderer->context = context;

    return renderer;
}

void destroy_renderer(Renderer *renderer) {
    if (renderer) {
        if (renderer->cleanup && renderer->context) {
            renderer->cleanup(renderer->context);
        }
        free(renderer);
    }
}

void render(Camera camera, const World *world, Renderer *renderer) {
    if (!renderer || !renderer->begin_render || !renderer->write_pixel ||
        !renderer->end_render) {
        fprintf(stderr, "Invalid renderer provided\n");
        return;
    }

    // Initialize rendering
    renderer->begin_render(camera.image_width, camera.image_height,
                           renderer->context);

    // Render pixels
    for (int j = 0; j < camera.image_height; j++) {
        for (int i = 0; i < camera.image_width; i++) {
            Color3 pixel_color = vec3_create_zero();
            for (int sample = 0; sample < camera.samples_per_pixel; sample++) {
                Ray r = camera_get_ray(camera, i, j);
                Color3 color = camera_ray_color(r, world);
                pixel_color = vec3_add(pixel_color, color);
            }

            // Write pixel using renderer
            pixel_color = vec3_scale(pixel_color, camera.pixel_samples_scale);
            renderer->write_pixel(&pixel_color, renderer->context);
        }
    }

    // Finalize rendering
    renderer->end_render(renderer->context);
}
