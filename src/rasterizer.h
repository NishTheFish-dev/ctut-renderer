#pragma once

#include <stdint.h>
#include "math_3d.h"

// Tiny Renderer (GitHub) - Lesson 1: Bresenham's Line Drawing Algorithm
// Tiny Renderer (GitHub) - Lesson 2: Triangle Rasterization and Back face culling

void rst_clear_buffer(uint32_t* buffer, int width, int height, uint32_t color);

void rst_draw_pixel(uint32_t* buffer, int width, int height, int x, int y, uint32_t color);

void rst_draw_line(uint32_t* buffer, int width, int height, int x0, int y0, int x1, int y1, uint32_t color);

void rst_draw_triangle(uint32_t* buffer, int width, int height, Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color);

