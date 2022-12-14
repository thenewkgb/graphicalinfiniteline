//
// SDL graphical - infinite line
//
// version on PC without TFF and now uses #ifdef for platforms

#include <stdio.h>
#include <SDL.h>
//#include <SDL_ttf.h>
#include <vector>
#include <random>

int get(std::vector<std::vector<int>> &arr, int x, int y)
{
    return arr[y][x];
}

int get(std::vector<int> vtr, int x)
{
    int result = vtr[x];
    return result;
}

// add on top of previous square
void put(int result, std::vector<int> &vtr, int x)
{
    vtr[x] = result;
    return;
}

void put(int result, std::vector<std::vector<int>> &arr, int x, int y)
{
    arr[y][x] = result;
    return;
}

int sum(int a, int b)
{
    return a - b;
}

int total(int a, int b)
{
    return a + b;
}

int addright(std::vector<int> &vtr, std::vector<int> &vtr2)
{
    // where is the middle?
    int coord1 = vtr.size() / 2;
    int ans{0};

    for (int j = coord1; j < vtr.size() - 1; ++j)
    {
        int first = get(vtr, j);
        int second = get(vtr, j - 1);
        int ans = sum(first, second);
        int t = total(first, ans);
        put(t, vtr, j + 1);
        // difference grid
        put(ans, vtr2, j + 1);
    }
    return ans;
}
int addleft(std::vector<int> &vtr,
            std::vector<int> &vtr2)
{
    int coord0 = vtr.size() / 2 - 1;
    int ans{0};

    for (int j = coord0; j > 0; --j)
    {
        int first = get(vtr, j);
        int second = get(vtr, j + 1);
        ans = sum(first, second);
        int t = total(first, ans);
        put(t, vtr, j - 1);
        put(ans, vtr2, j - 1);
    }
    return ans;
}

int adddown(std::vector<std::vector<int>> &arr, int column, std::vector<std::vector<int>> &arr2)
{
    int coord1 = arr.size() / 2;
    int ans{0};

    for (int j = coord1; j < arr.size() - 1; ++j)
    {
        int first = get(arr, column, j);
        int second = get(arr, column, j - 1);
        ans = sum(first, second);
        int t = total(first, ans);
        put(t, arr, column, j + 1);
        put(ans, arr2, column, j + 1);
    }
    return ans;
}

int addup(std::vector<std::vector<int>> &arr, int column, std::vector<std::vector<int>> &arr2)
{
    int coord0 = arr.size() / 2 - 1;
    int ans{0};

    for (int j = coord0; j > 0; --j)
    {
        int first = get(arr, column, j);
        int second = get(arr, column, j + 1);
        ans = sum(first, second);
        int t = total(first, ans);
        put(t, arr, column, j - 1);
        put(ans, arr2, column, j - 1);
    }

    return ans;
}

void calcDiagonals(std::vector<std::vector<int>> &arr, int a, int b, int i)
{
    if (i > 0)
    {
        int first = get(arr, a, b);
        int second = get(arr, a - 1, b - 1);
        int ans = sum(second, first);
        int t = total(second, ans);
        put(t, arr, a - 2, b - 2);
        calcDiagonals(arr, a - 1, b - 1, i - 1);
    }
}

void diagonalBottom(std::vector<std::vector<int>> &arr)
{
    // include longest diagonal
    // top right, bottom left
    int size = arr.size();
    int sum2 = size - 2 - 1;

    for (int i = 0; i < sum2; ++i)
    {
        // - 1 for vector[0]
        int a = size - 1 - sum2 + i;
        // -1 for vector[0]
        int b = arr[0].size() - 1;
        int first = get(arr, a, b);
        int second = get(arr, a - 1, b - 1);
        int ans = sum(second, first);
        int t = total(second, ans);
        put(t, arr, a - 2, b - 2);
        calcDiagonals(arr, a - 1, b - 1, i);
    }

    // hack
    // longest diagonal
    calcDiagonals(arr, 7, 7, 6);
}

void diagonalTop(std::vector<std::vector<int>> &arr)
{
    int size = arr.size();
    int sum2 = size - 2 - 1;

    for (int i = 0; i < sum2; ++i)
    {
        // - 1 for vector[0]
        int b = size - 1 - sum2 + i;
        // -1 for vector[0]
        int a = arr[0].size() - 1;
        int first = get(arr, a, b);
        int second = get(arr, a - 1, b - 1);
        int ans = sum(second, first);
        int t = total(second, ans);
        put(t, arr, a - 2, b - 2);
        calcDiagonals(arr, a - 1, b - 1, i);
    }
}

void changeRedSurfaceColour(SDL_Texture *redtexture, int val)
{
    int value = (val * 4) % 255;
    SDL_SetTextureColorMod(redtexture, value, 0, 0);
}

void changeGreenSurfaceColour(SDL_Texture *greentexture, int val)
{
    int value = (val * 4) % 255;
    SDL_SetTextureColorMod(greentexture, 0, value, 0);
}

void changeYellowSurfaceColour(SDL_Texture *yellowtexture, int val)
{
    int value = (val * 4) % 255;
    SDL_SetTextureColorMod(yellowtexture, value, value, 0);
}

void changePurpleSurfaceColour(SDL_Texture *purpletexture, int val)
{
    int value = (val * 4) % 255;
    SDL_SetTextureColorMod(purpletexture, value, 0, value);
}

void printline(SDL_Texture *redtexture, SDL_Texture *greentexture, SDL_Texture *bluetexture, SDL_Texture *yellowtexture, SDL_Texture *purpletexture, SDL_Renderer *renderer, int row, std::vector<int> value)
{
    SDL_Rect position;
    position.x = 50;
    position.y = 50;
    position.h = 50;
    position.w = 50;

    // draw verticle
    position.y *= row;

    for (int i = 1; i <= 8; ++i)
    {
        // draw horizontal
        position.x = position.x * i;

        // colours are relatively small
        if (value[i - 1] < 0 && value[i - 1] > -255)
        {
            changeRedSurfaceColour(redtexture, value[i - 1] * -1);
            SDL_RenderCopy(renderer, redtexture, NULL, &position);
        }
        else if (value[i - 1] > 0 && value[i - 1] < 255)
        {
            changeGreenSurfaceColour(greentexture, value[i - 1]);
            SDL_RenderCopy(renderer, greentexture, NULL, &position);
        }
        // colours are very big or very small
        else if (value[i - 1] < -255)
        {
            changeYellowSurfaceColour(yellowtexture, value[i - 1]);
            SDL_RenderCopy(renderer, yellowtexture, NULL, &position);
        }
        else if (value[i - 1] > 255)
        {
            changePurpleSurfaceColour(purpletexture, value[i - 1]);
            SDL_RenderCopy(renderer, purpletexture, NULL, &position);
        }
        else if (value[i - 1] == 0)
            SDL_RenderCopy(renderer, bluetexture, NULL, &position);

        position.x = 50;
    }
}

void printgrid(const std::vector<std::vector<int>> &arr, SDL_Texture *redtexture, SDL_Texture *greentexture, SDL_Texture *bluetexture, SDL_Texture *yellowtexture, SDL_Texture *purpletexture, SDL_Renderer *renderer)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        //whole row vector
        printline(redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer, i, arr[i]);
    }
}

void printdiffgrid(const std::vector<std::vector<int>> &arrDiff, SDL_Texture *redtexture, SDL_Texture *greentexture, SDL_Texture *bluetexture, SDL_Texture *yellowtexture, SDL_Texture *purpletexture, SDL_Renderer *renderer)
{
    for (int i = 0; i < arrDiff.size(); ++i)
    {
        //an extra 15 spaces below
        printline(redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer, i + 15, arrDiff[i]);
    }
}

void initGridHorz(std::vector<std::vector<int>> &arr, std::vector<std::vector<int>> &arr2)
{
    // first pass
    addright(arr[3], arr2[3]);
    addright(arr[4], arr2[4]);
    addleft(arr[3], arr2[3]);
    addleft(arr[4], arr2[4]);
    // column arg for multi arrays
    adddown(arr, 3, arr2);
    adddown(arr, 4, arr2);
    addup(arr, 3, arr2);
    addup(arr, 4, arr2);

    // second pass
    addright(arr[0], arr2[0]);
    addright(arr[1], arr2[1]);
    addright(arr[2], arr2[2]);
    addleft(arr[0], arr2[0]);
    addleft(arr[1], arr2[1]);
    addleft(arr[2], arr2[2]);
    addright(arr[5], arr2[5]);
    addright(arr[6], arr2[6]);
    addright(arr[7], arr2[7]);
    addleft(arr[5], arr2[5]);
    addleft(arr[6], arr2[6]);
    addleft(arr[7], arr2[7]);
}

/*
static SDL_Texture *loadText(SDL_Renderer *renderer, const char *text)
{
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        return NULL;
    }
    TTF_Font *font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", 256);
    if (font == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

*/
SDL_Texture *createSquare(SDL_Renderer *renderer, int r, int g, int b)

{
    SDL_Surface *surface = NULL;
    surface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}
/*
SDL_Texture *createGreenTexture(SDL_Renderer *renderer)
{
    SDL_Surface *greensurface = NULL;
    greensurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);

    SDL_FillRect(greensurface, NULL, SDL_MapRGB(greensurface->format, 0x00, 0xFF, 0x00));

    SDL_Texture *greentexture = SDL_CreateTextureFromSurface(renderer, greensurface);

    SDL_FreeSurface(greensurface);

    return greentexture;
}
*/
/*
SDL_Texture *createBlueTexture(SDL_Renderer *renderer)
{
    SDL_Surface *bluesurface = NULL;
    bluesurface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);

    SDL_FillRect(bluesurface, NULL, SDL_MapRGB(bluesurface->format, 0x00, 0x00, 0xFF));

    SDL_Texture *bluetexture = SDL_CreateTextureFromSurface(renderer, bluesurface);

    SDL_FreeSurface(bluesurface);

    return bluetexture;
}

/*
void printNumbers(SDL_Renderer *renderer, int w, int x, int y, int z)
{
    // display numbers
    // x pos, y pos, width, height
    SDL_Rect textPositionW{50, 500, 50, 50};
    SDL_Rect textPositionX{150, 500, 50, 50};
    SDL_Rect textPositionY{50, 600, 50, 50};
    SDL_Rect textPositionZ{150, 600, 50, 50};

    std::string sw = std::to_string(w);
    std::string sx = std::to_string(x);
    std::string sy = std::to_string(y);
    std::string sz = std::to_string(z);

    SDL_Texture *textTextureW = loadText(renderer, sw.c_str());
    SDL_Texture *textTextureX = loadText(renderer, sx.c_str());
    SDL_Texture *textTextureY = loadText(renderer, sy.c_str());
    SDL_Texture *textTextureZ = loadText(renderer, sz.c_str());

    //  SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textTextureW, NULL, &textPositionW);
    SDL_RenderCopy(renderer, textTextureX, NULL, &textPositionX);
    SDL_RenderCopy(renderer, textTextureY, NULL, &textPositionY);
    SDL_RenderCopy(renderer, textTextureZ, NULL, &textPositionZ);
}
*/

int main(int argc, char *argv[])
{
    // we need SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

#ifdef __ANDROID__
    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Android SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
#endif
#ifdef __WIN32__
    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Win SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 120, 0);
#endif

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        fprintf(stderr, "%s", SDL_GetError());

    // create three surfaces to draw off screen
    // fill these surfaces with colours
    // create textures from surfaces and free surfaces

    SDL_Texture *redtexture = createSquare(renderer, 255, 0, 0);

    SDL_Texture *greentexture = createSquare(renderer, 0, 255, 0);

    SDL_Texture *bluetexture = createSquare(renderer, 0, 0, 255);

    SDL_Texture *yellowtexture = createSquare(renderer, 255, 255, 0);

    SDL_Texture *purpletexture = createSquare(renderer, 255, 0, 255);

    // allow a touch to change patterns
    SDL_Event event;

    // change these values to produce
    // different patterns
    int w{0};
    int x{0};
    int y{0};
    int z{0};

    std::vector<std::vector<int>> arrHorz =
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, w, x, 0, 0, 0},
         {0, 0, 0, y, z, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}};

    // make a copy
    std::vector<std::vector<int>> arrDiff = arrHorz;
    std::vector<std::vector<int>> arrDiag = arrHorz;

    //main loop
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    srand(time(0));
    bool go = true;

    for (int i = 0; i < 5; ++i)
    {
        while (go == false)
        {
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_FINGERUP:
                    go = true;
                    break;
                }
            }
        }

        w = rand() % 20;
        x = rand() % 20;
        y = rand() % 20;
        z = rand() % 20;

        // manual entry of numbers
        // 1 4 9 1
        // 0 3 5 8
        //w = 1; x = 4; y = 9; z = 12;

        arrHorz =
            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, w, x, 0, 0, 0},
             {0, 0, 0, y, z, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}};

        initGridHorz(arrHorz, arrDiff);

        SDL_RenderClear(renderer);

        printgrid(arrHorz, redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer);

        printdiffgrid(arrDiff, redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer);


        // update screen
        SDL_RenderPresent(renderer);

        for (int i = 0; i < 50; ++i)
        {
            SDL_RenderClear(renderer);
            /*
            initGridDiag(arrHorz);
            initGridHorz(arrHorz, arrDiff);
            printgrid(arrHorz, redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer);

            printdiffgrid(arrDiff, redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer);

            printNumbers(renderer, w, x, y, z);
            SDL_RenderPresent(renderer);
            SDL_Delay(1200);
            */
        }

        go = false;
    }

    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
