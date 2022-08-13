//
// SDL graphical - infinite line
//
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include <random>

void addright(std::vector<int> &vtr)
{
    // which numbers do we want?
    int first = vtr.size() / 2;
    int second = first-1;
    //difference between the two
    int ans = vtr[first] - vtr[second];

    int i = vtr.size() - vtr.size() / 2;
    
    for (int j = 1; j < i; ++j)
    {
        vtr[first + j] = ans + vtr[second + j];
        ans = vtr[first+j] - vtr[second + j];
    }
    return;
}

void addleft(std::vector<int> &vtr)
{
    int first = vtr.size() / 2;
    int second = first-1;
    int ans = vtr[second] - vtr[first];

    int i = vtr.size() - vtr.size() / 2;
    for (int j = 1; j < i; ++j)
    {
        vtr[second-j] = ans + vtr[first-j];
        ans = vtr[second-j] - vtr[first-j];
    }
    return;
}

void adddown(std::vector<std::vector<int>> &arr, int column)
{
    int first = arr.size()/2;
    int second = first -1;
    int ans = arr[first][column] - arr[second][column];
        
    int i = arr.size() - arr.size()/2;
    for(int j=1;j<i;++j)
    {
        arr[first + j][column] =
             ans + arr[second+j][column];
        ans = arr[first+j][column] - 
            arr[second+j][column];
    }
        return;
}

void addup(std::vector<std::vector<int>> &arr, int column)
{
    int first = arr.size()/2;
    int second = first - 1;
    int ans = arr[second][column] - arr[first][column];
    
    int i = arr.size() - arr.size()/2;
    for(int j=1;j<i;++j)
    {
        arr[second - j][column] =
            ans + arr[first-j][column];
        ans = arr[second-j][column] - arr[first-j][column];
    }
    return;
}

void changeRedSurfaceColour(SDL_Surface *surface, int val)
{
    int newValue = (val*8)%200;
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, newValue, 0, 0));
}

void changeGreenSurfaceColour(SDL_Surface *surface, int val)
{
    int newValue = (val*8)%255;
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, newValue, 0));
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
        {
            changeRedSurfaceColour(redsurface, value[i-1]);
            
            SDL_BlitSurface(redsurface, NULL, surface, &position);
        }
        else if(value[i-1] > 0)
        {
            changeGreenSurfaceColour(greensurface, value[i-1]);
            SDL_BlitSurface(greensurface, NULL, surface, &position);
        }
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

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // surface to display on window
    
       SDL_Surface *surface = NULL;
    surface = SDL_GetWindowSurface(window);
    
     // create three surfaces to draw off screen

    SDL_Surface *redsurface = NULL;
    redsurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    
    SDL_Surface *greensurface = NULL;
    greensurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    
    SDL_Surface *bluesurface = NULL;
    bluesurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    
    // fill these surfaces with red, green and blue

    SDL_FillRect(redsurface, NULL, SDL_MapRGB(redsurface->format, 255, 0, 0));
    
     SDL_FillRect(greensurface, NULL, SDL_MapRGB(greensurface->format, 0x00, 0xFF, 0x00));
    
    SDL_FillRect(bluesurface, NULL, SDL_MapRGB(bluesurface->format, 0x00, 0x00, 0xFF));
    
     // my code
    
    // change these values to produce
    // different patterns
    
    int w {0};
    int x {1};
    int y {2};
    int z {3};

    std::vector<std::vector<int>> arr =
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, w, x, 0, 0, 0},
         {0, 0, 0, y, z, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}};

    initgrid(arr);
    
    // get them on screen
    
    printgrid(arr, redsurface, greensurface, bluesurface, surface);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
    
    srand(time(0));
    
    for(int i = 0; i<10;++i)
    {
    
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    
    SDL_UpdateWindowSurface(window);
    SDL_Delay(1000);
    
    w = rand() % 20;
    x = rand() % 20;
    y = rand() % 20;
    z = rand() % 20;
    
    arr =
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, w, x, 0, 0, 0},
         {0, 0, 0, y, z, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}};
    
    initgrid(arr);
    printgrid(arr, redsurface, greensurface, bluesurface, surface);
    
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
    }
    
    
    // clean up

    SDL_FreeSurface(surface);
    SDL_FreeSurface(redsurface);
    SDL_FreeSurface(greensurface);
    SDL_FreeSurface(bluesurface);
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
