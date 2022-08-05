#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>

void addright(std::vector<int> &vtr)
{
    int middle = vtr.size() / 2;
    int largest = vtr[middle];
    // difference between two
    int ans = vtr[middle] - vtr[middle - 1];

    int i = vtr.size() - vtr.size() / 2;
    for (int j = 1; j < i; ++j)
        vtr[middle + j] = largest + ans * j;
    return;
}

void addleft(std::vector<int> &vtr)
{
    int middle = vtr.size() / 2;
    int first = vtr[middle - 1];
    int second = vtr[middle];
    int ans = first - second;

    int i = vtr.size() - vtr.size() / 2;
    for (int j = 1; j < i; ++j)
    {
        vtr[middle - j - 1] = first + ans * j;
    }
    return;
}

void adddown(std::vector<std::vector<int>> &arr, int column)
{
    int verticlemiddle = arr.size() / 2;
    int first = arr[verticlemiddle][column];
    int second = arr[verticlemiddle - 1][column];
    int ans = first - second;

    int i = arr.size() - arr.size() / 2;
    for (int j = 1; j < i; ++j)
        arr[verticlemiddle + j][column] = first + ans * j;
    return;
}

void addup(std::vector<std::vector<int>> &arr, int column)
{
    int verticlemiddle = arr.size() / 2;
    int first = arr[verticlemiddle][column];
    int second = arr[verticlemiddle - 1][column];
    int ans = second - first;

    int i = arr.size() - arr.size() / 2;
    for (int j = 1; j < i; ++j)
        arr[verticlemiddle - j - 1][column] = second + ans * j;
}

void printline(SDL_Surface* redsurface, SDL_Surface* greensurface, SDL_Surface* bluesurface, SDL_Surface* surface, int row, std::vector<int> value)
{
    SDL_Rect position;
    position.x = 50;
    position.y = 50;
    
    // draw verticle
    position.y *= row;
    
    for (int i = 1; i <= 8; ++i)
    {
        // draw horizontal
        position.x = position.x * i;
        
        if(value[i-1] < 0)
            SDL_BlitSurface(redsurface, NULL, surface, &position);
        else if(value[i-1] > 0)
            SDL_BlitSurface(greensurface, NULL, surface, &position);
        else if(value[i-1] == 0)
            SDL_BlitSurface(bluesurface, NULL, surface, &position);
        
        position.x = 50;
    }
}

void printgrid(const std::vector<std::vector<int>> &arr, SDL_Surface* redsurface, SDL_Surface* greensurface, SDL_Surface* bluesurface, SDL_Surface* surface)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        //whole row
    printline(redsurface, greensurface, bluesurface,surface, i, arr[i]);
    }
}

void initgrid(std::vector<std::vector<int>> &arr)
{
    // first pass
    addright(arr[3]);
    addright(arr[4]);
    addleft(arr[3]);
    addleft(arr[4]);
    adddown(arr, 3);
    adddown(arr, 4);
    addup(arr, 3);
    addup(arr, 4);

    // second pass
    addright(arr[0]);
    addright(arr[1]);
    addright(arr[2]);
    addleft(arr[0]);
    addleft(arr[1]);
    addleft(arr[2]);
    addright(arr[5]);
    addright(arr[6]);
    addright(arr[7]);
    addleft(arr[5]);
    addleft(arr[6]);
    addleft(arr[7]);
}

int main(int argc, char *argv[])
{
    // we need SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // my code
    
    // change these values to produce
    // different patterns
    
    int one{7};
    int two{3};
    int three{21};

    std::vector<std::vector<int>> arr =
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, one, 0, 0, 0},
         {0, 0, 0, two, three, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}};

    initgrid(arr);
    
    // SDL set up

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }
    
       SDL_Surface *surface = NULL;
    surface = SDL_GetWindowSurface(window);
    
     // draw to off screen surface
    // blit surface to screen
    // update window surface
    // see results

    SDL_Surface *redsurface = NULL;
    redsurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    
    SDL_Surface *greensurface = NULL;
    greensurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    
    SDL_Surface *bluesurface = NULL;
    bluesurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    
    // fill surfaces with red, green and blue

    SDL_FillRect(redsurface, NULL, SDL_MapRGB(redsurface->format, 0xFF, 0x00, 0x00));
    
     SDL_FillRect(greensurface, NULL, SDL_MapRGB(greensurface->format, 0x00, 0xFF, 0x00));
    
    SDL_FillRect(bluesurface, NULL, SDL_MapRGB(bluesurface->format, 0x00, 0x00, 0xFF));
    
    // get them on screen
    
    printgrid(arr, redsurface, greensurface, bluesurface, surface);
    
    


    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
    
    // clean up

    SDL_FreeSurface(surface);
    SDL_FreeSurface(redsurface);
    SDL_FreeSurface(greensurface);
    SDL_FreeSurface(bluesurface);
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
