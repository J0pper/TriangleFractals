#include "sdl2.h"
#include "fractal.h"

#include <stdio.h>

void init_fractal(Line **line_array, int *array_size, int depth, Line start_line)
{
    int arr_size = (int)pow(3, depth);

    *line_array = (Line *)realloc(*line_array, sizeof(Line) * arr_size);
    *line_array[0] = start_line;

    generate_fractal(start_line, depth, *line_array, arr_size);

    *array_size = arr_size;
}

int main(int argc, char *argv[])
{
    int depth = 0;
    Line start_line = { { 400.f, 400.f}, { 1200.f, 400.f } };
    int array_size;
    int *ptr_array_size = &array_size;
    Line *line_array = (Line *)malloc(sizeof(Line));
    init_fractal(&line_array, ptr_array_size, depth, start_line);

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("TRIANGLE FRACTAL", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1600, 800, 0);
 
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = 0;

    // creates a renderer to render our images
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    // controls animation loop
    int close = 0;
    int depth_buffer = depth;

    // animation loop
    while (!close) {
        if (depth_buffer != depth) {
            depth = depth_buffer;
            init_fractal(&line_array, ptr_array_size, depth, start_line);
        };

        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // handling of close button
                    close = 1;
                    break;

                case SDL_MOUSEWHEEL:
                    depth_buffer += event.wheel.y;
                    if (depth_buffer < 0) depth_buffer = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        for (int i = 0; i < *ptr_array_size; i++)
        {
            SDL_RenderDrawLine(renderer,
                               line_array[i].point1[0],
                               line_array[i].point1[1],
                               line_array[i].point2[0],
                               line_array[i].point2[1]);
        }

        SDL_RenderPresent(renderer);
    }
        // cleanup SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

    return 0;
}

