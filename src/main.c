#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "platform.h"
#include "rasterizer.h"
#include "math_3d.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
    /*
        This program follows a 4 step process: Initializing the window, allocating the framebuffer in memory, rendering any inputs in the loop, and cleanup when exiting.
    */

    // Initialize the SDL2 window
    Window* window = platform_create_window("CTUT Renderer", WIDTH, HEIGHT);
    
    // Allocate the framebuffer
    uint32_t* framebuffer = malloc(WIDTH * HEIGHT * sizeof(uint32_t));
    float* zbuffer = malloc(WIDTH * HEIGHT * sizeof(float));

    // FPS variables
    uint32_t last_time = platform_get_time();
    int frame_count = 0;
    int fps = 0;

    // Main loop
    bool running = true;
    while (running) {
        // Input
        running = platform_process_events();

        // Update / Render
        rst_clear_buffer(framebuffer, WIDTH, HEIGHT, 0xFF000000); // Clear to black screen
        rst_clear_zbuffer(zbuffer, WIDTH, HEIGHT);

        // Normalized Device Coordinates (-1 to 1 range)
        Vec3 vertices[] = {
            {-1, -1, -1}, { 1, -1, -1}, { 1,  1, -1}, {-1,  1, -1}, // Front Face
            {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1}  // Back Face
        };

        // Indices connecting vertices into triangles (0-based)
        int indices[] = {
            0, 1, 2, 2, 3, 0, // Front
            1, 5, 6, 6, 2, 1, // Right
            5, 4, 7, 7, 6, 5, // Back
            4, 0, 3, 3, 7, 4, // Left
            3, 2, 6, 6, 7, 3, // Top
            4, 5, 1, 1, 0, 4  // Bottom
        };

        // Setup the model and projection matrices
        // Spin the cube over time
        static float angle = 0.0f;
        angle += 0.01f; 
        // Model Matrix: Rotate then move back 3 units
        Mat4 model = mat4_rotate_y(angle);
        model = mat4_mul_mat4(mat4_translate(0, 0, -3.0f), model);
        // Projection Matrix: 90 degree FOV
        Mat4 proj = mat4_perspective(1.57f, (float)WIDTH / HEIGHT, 0.1f, 100.0f);
                
        // Clip Space = Projection * Model
        Mat4 mvp = mat4_mul_mat4(proj, model);
        // Loop through all 12 triangles
        for (int i = 0; i < 36; i += 3) {
            Vec3 screen_tri[3];

            // Process each vertex of the triangle
            for (int j = 0; j < 3; j++) {
                Vec3 local = vertices[indices[i + j]];
                Vec4 v4 = { local.x, local.y, local.z, 1.0f };
                // Vertex Shader: Apply Matrix
                Vec4 clip = mat4_mul_vec4(mvp, v4);
                // Perspective Divide: Clip Space -> NDC
                if (clip.w != 0) {
                    clip.x /= clip.w;
                    clip.y /= clip.w;
                    clip.z /= clip.w;
                }

                // Viewport Transform from NDC to Screen
                // Note: flip y because screen coordinates start at the top
                screen_tri[j].x = (clip.x + 1.0f) * 0.5f * WIDTH;
                screen_tri[j].y = (1.0f - clip.y) * 0.5f * HEIGHT;
                screen_tri[j].z = clip.z;
            }
            // Rasterize and use a random-ish color based on the triangle index to see faces
            uint32_t color = 0xFF0000FF + (i * 50); 
            rst_draw_triangle(framebuffer, zbuffer, WIDTH, HEIGHT, 
                            screen_tri[0], screen_tri[1], screen_tri[2], color);
        }

        // Pitch = width * bytes_per_pixel (4)
        
        // Calculate and draw FPS
        frame_count++;
        uint32_t current_time = platform_get_time();
        if (current_time - last_time >= 100) {
            fps = frame_count * 1000 / (current_time - last_time);
            frame_count = 0;
            last_time = current_time;
        }

        int temp_fps = fps;
        int x_pos = WIDTH - 20;
        if (temp_fps == 0) {
             rst_draw_digit(framebuffer, WIDTH, HEIGHT, x_pos, 10, 0, 0xFF00FF00);
        } else {
            while (temp_fps > 0) {
                rst_draw_digit(framebuffer, WIDTH, HEIGHT, x_pos, 10, temp_fps % 10, 0xFF00FF00);
                x_pos -= 15;
                temp_fps /= 10;
            }
        }

        platform_update_window(window, framebuffer, WIDTH * 4);
    }

    // Cleanup after exiting
    free(framebuffer);
    free(zbuffer);
    platform_destroy_window(window);
    
    return 0;
}