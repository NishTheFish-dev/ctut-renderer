#pragma once

#include <stdint.h>
#include "math_3d.h"

void rst_clear_buffer(uint32_t* buffer, int width, int height, uint32_t color);
void rst_clear_zbuffer(float* zbuffer, int width, int height);
void rst_draw_pixel(uint32_t* buffer, int width, int height, int x, int y, uint32_t color);
void rst_draw_line(uint32_t* buffer, int width, int height, int x0, int y0, int x1, int y1, uint32_t color);
void rst_draw_triangle(uint32_t* buffer, float* zbuffer, int width, int height, Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color);
void rst_draw_digit(uint32_t* buffer, int width, int height, int x, int y, int digit, uint32_t color);