#define SDL_MAIN_HANDLED
#include "platform.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

Window* platform_create_window(const char* title, int width, int height) {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL failed to initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(-1);
	}

    // Initialize a window, renderer, and texture
    Window* win = malloc(sizeof(Window));
    win->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    win->renderer = SDL_CreateRenderer(win->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    win->texture = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    return win;
}

void platform_destroy_window(Window* window) {
    // Remove all of the elements in reverse order
    SDL_DestroyTexture(window->texture);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();
    free(window);
}

bool platform_process_events(void) {
    SDL_Event event;
    bool running = true;
    // Process all events that happened since the last frame (handling for X button and escape key)
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                break;
        }
    }
    return running;
}

void platform_update_window(Window* window, uint32_t* buffer, int pitch) {
    // 4 step process: Update the texture with buffer pixel data, clear renderer, copy texture to renderer, and present it
    SDL_UpdateTexture(window->texture, NULL, buffer, pitch);
    SDL_RenderClear(window->renderer);
    SDL_RenderCopy(window->renderer, window->texture, NULL, NULL);
    SDL_RenderPresent(window->renderer);
}