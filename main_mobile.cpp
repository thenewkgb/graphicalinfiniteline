//
// SDL graphical - infinite line
//
// addition by mobile
//
// clear out conflicts
//
// keep necessary SDL setup

#include <stdio.h>
#include <vector>
#include <random>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char *argv[])
{
    // we need SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Android SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        fprintf(stderr, "%s", SDL_GetError());

    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
