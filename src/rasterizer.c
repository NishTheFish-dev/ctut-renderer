#include "rasterizer.h"
#include <stdlib.h>

void swap_int(int* a, int* b) {
    int t = *a; 
    *a = *b; 
    *b = t;
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void rst_draw_line(uint32_t* buffer, int width, int height, int x0, int y0, int x1, int y1, uint32_t color) {
    // Check if line is "steep" (height > width)
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap_int(&x0, &y0);
        swap_int(&x1, &y1);
    }

    // Always draw from left to right
    if (x0 > x1) {
        swap_int(&x0, &x1);
        swap_int(&y0, &y1);
    }

    // Variable setup
    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int y = y0;
    int y_step = (y0 < y1) ? 1 : -1;

    // Iterate over x to draw pixels
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            rst_draw_pixel(buffer, width, height, y, x, color);
        } 
        else {
            rst_draw_pixel(buffer, width, height, x, y, color);
        }

        error -= dy;
        if (error < 0) {
            y += y_step;
            error += dx;
        }
    }
}

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