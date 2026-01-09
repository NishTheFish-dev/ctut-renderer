#include "rasterizer.h"
#include <stdlib.h>

// --- Helper functions ---
static int min3(int a, int b, int c) { return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c); }
static int max3(int a, int b, int c) { return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c); }

void swap_int(int* a, int* b) {
    int t = *a; 
    *a = *b; 
    *b = t;
}

static float edge_cross(Vec3 a, Vec3 b, Vec3 p) {
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

void rst_clear_zbuffer(float* zbuffer, int width, int height) {
    // Slow implementation (double for loop)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                zbuffer[y * width + x] = 1.0f;
            }
        }
    }
}

// --- Main functions ---

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void rst_draw_line(uint32_t* buffer, int width, int height, int x0, int y0, int x1, int y1, uint32_t color) {
    // Check if line is "steep" (height > width)
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap_int(&x0, &y0);
        swap_int(&x1, &y1);
    }

    // Always draw line from left to right
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
void rst_draw_triangle(uint32_t* buffer, float* zbuffer, int width, int height, Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color) {
    // Slow implementation: Checking every pixel on the screen 
    int min_x = 0;
    int min_y = 0;
    int max_x = width - 1;
    int max_y = height - 1;

    float area = edge_cross(v0, v1, v2); 
    
    // Loop over pixels in the bounding box
    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            // Sample at pixel center (+0.5)
            Vec3 p = { x + 0.5f, y + 0.5f, 0 };

            // Calculate Barycentric coordinates, if p is inside the triangle, all cross products will have the same sign
            float w0 = edge_cross(v1, v2, p);
            float w1 = edge_cross(v2, v0, p);
            float w2 = edge_cross(v0, v1, p);

            // 5. Check if inside, handle both all positive / all negative cases
            bool inside = (w0 >= 0 && w1 >= 0 && w2 >= 0) || 
                          (w0 <= 0 && w1 <= 0 && w2 <= 0);
            if (inside) {
                // Normalize the weights
                float alpha = w0 / area;
                float beta = w1 / area;
                float gamma = w2 / area;
                // Interpolate Z (depth)
                float z = alpha * v0.z + beta * v1.z + gamma * v2.z;

                // Depth Test
                int index = y * width + x;
                if (z < zbuffer[index]) {
                    zbuffer[index] = z;
                    buffer[index] = color;
                }
            }
        }
    }
}

void rst_clear_buffer(uint32_t* buffer, int width, int height, uint32_t color) {
    // Slow implementation: double for loop for pixel by pixel drawing
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            rst_draw_pixel(buffer, width, height, x, y, color);
        }
    }
}

void rst_draw_pixel(uint32_t* buffer, int width, int height, int x, int y, uint32_t color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        buffer[y * width + x] = color;
    }
}

void rst_draw_digit(uint32_t* buffer, int width, int height, int x, int y, int digit, uint32_t color) {
    int w = 10;
    int h = 20;
    // Segments
    //   A
    // F   B
    //   G
    // E   C
    //   D
    
    bool segA = digit!=1 && digit!=4;
    bool segB = digit!=5 && digit!=6;
    bool segC = digit!=2;
    bool segD = digit!=1 && digit!=4 && digit!=7;
    bool segE = digit==0 || digit==2 || digit==6 || digit==8;
    bool segF = digit!=1 && digit!=2 && digit!=3 && digit!=7;
    bool segG = digit!=0 && digit!=1 && digit!=7;

    if (segA) rst_draw_line(buffer, width, height, x, y, x+w, y, color);
    if (segB) rst_draw_line(buffer, width, height, x+w, y, x+w, y+h/2, color);
    if (segC) rst_draw_line(buffer, width, height, x+w, y+h/2, x+w, y+h, color);
    if (segD) rst_draw_line(buffer, width, height, x, y+h, x+w, y+h, color);
    if (segE) rst_draw_line(buffer, width, height, x, y+h/2, x, y+h, color);
    if (segF) rst_draw_line(buffer, width, height, x, y, x, y+h/2, color);
    if (segG) rst_draw_line(buffer, width, height, x, y+h/2, x+w, y+h/2, color);
}