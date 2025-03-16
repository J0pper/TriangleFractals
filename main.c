#include "sdl2.h"
#include "fractal.h"

#include <stdio.h>

 
int main(int argc, char *argv[])
{
    int depth = 0;
    Line start_line = { { 400, 400}, { 1200, 400 } };
    Line *line_array;

    int final_array_size;
    generate_fractal(start_line, depth, &line_array, &final_array_size);
    
    printf("%p\n", &line_array[0].point1[0]);

    printf("Line ARRAY");
    print_lines(line_array, final_array_size);

    Line copy_line_array[final_array_size];

    memcpy(copy_line_array, line_array, sizeof(Line) * final_array_size);
    print_lines(copy_line_array, final_array_size);


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

    // animation loop
    while (!close) {
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        
        //printf("Line ARRAY");
        //print_lines(copy_line_array, final_array_size);

        for (int i = 0; i < final_array_size; i++)
        {
            SDL_RenderDrawLine(renderer,
                               copy_line_array[i].point1[0],
                               copy_line_array[i].point1[1],
                               copy_line_array[i].point2[0],
                               copy_line_array[i].point2[1]);
        }

        SDL_RenderPresent(renderer);
    }
        // cleanup SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

    return 0;
}

