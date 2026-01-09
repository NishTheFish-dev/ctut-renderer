#pragma once

#include <stdint.h>
#include <stdbool.h>

// This provides the definitions for the elements of a window
typedef struct Window Window;

// SDL_CreateWindow, SDL_CreateRenderer, SDL_CreateTexture
Window* platform_create_window(const char* title, int width, int height);

// SDL_DestroyWindow
void platform_destroy_window(Window* window);

// SDL_PollEvent
bool platform_process_events(void);

// SDL_UpdateTexture, SDL_RenderCopy
void platform_update_window(Window* window, uint32_t* buffer, int pitch);