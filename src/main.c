#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "platform.h"
#include "rasterizer.h"
#include "math_3d.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
    // 1. Initialize Platform (SDL2)
    Window* window = platform_create_window("CTUT Renderer", WIDTH, HEIGHT);
    
    // 2. Allocate Framebuffer (CPU-side pixel buffer)
    uint32_t* framebuffer = malloc(WIDTH * HEIGHT * sizeof(uint32_t));

    // 3. Main Loop
    bool running = true;
    while (running) {
        // A. Input
        running = platform_process_events();

        // B. Update / Render
        rst_clear_buffer(framebuffer, WIDTH, HEIGHT, 0xFF000000); // Clear to Black

        // TODO: Test rasterizer here
        // rst_draw_line(framebuffer, WIDTH, HEIGHT, 100, 100, 200, 200, 0xFFFF0000);

        // C. Display
        // Pitch = width * bytes_per_pixel (4)
        platform_update_window(window, framebuffer, WIDTH * 4);
    }

    // 4. Cleanup
    free(framebuffer);
    platform_destroy_window(window);
    
    return 0;
}