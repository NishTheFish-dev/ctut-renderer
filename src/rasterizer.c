#include "rasterizer.h"
#include <stdlib.h>

// TODO: Implement Bresenham's Line Algorithm
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void rst_draw_line(uint32_t* buffer, int width, int height, int x0, int y0, int x1, int y1, uint32_t color) {
    // Your implementation here
}

// TODO: Implement Triangle Rasterization (Barycentric Coordinates or Scanline)
// https://github.com/ssloy/tinyrenderer/wiki/Lesson-2:-Triangle-rasterization-and-back-face-culling
void rst_draw_triangle(uint32_t* buffer, int width, int height, Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color) {
    // Your implementation here
}

void rst_clear_buffer(uint32_t* buffer, int width, int height, uint32_t color) {
    for (int i = 0; i < width * height; ++i) {
        buffer[i] = color;
    }
}

void rst_draw_pixel(uint32_t* buffer, int width, int height, int x, int y, uint32_t color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        buffer[y * width + x] = color;
    }
}
