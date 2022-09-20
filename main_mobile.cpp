//
// SDL graphical - infinite line
//
// addition by mobile
//
// clear out all old functions
// keep SDL functions
// and clear out bulk of main loop

#include <stdio.h>
#include <vector>
#include <random>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

// the final array requires the average
// of four arrays
void putDivideFour(int sum, std::vector<std::vector<int>> &arr, int x, int y)
{
    arr[x][y] = sum / 4;
}

void putDivideTwo(int sum, std::vector<std::vector<int>> &arr, int x, int y)
{
    arr[x][y] = sum / 2;
}

//
// sums
//
int sum(int a, int b)
{
    return a - b;
}

int total(int a, int b)
{
    return a + b;
}

//
// initialising
//
void initRight(std::vector<int> &vtr)
{
    int coord1 = vtr.size() / 2;

    for (int j = coord1; j < vtr.size() - 1; ++j)
    {
        int first = get(vtr, j);
        int second = get(vtr, j - 1);
        int ans = sum(first, second);
        int t = total(first, ans);
        put(t, vtr, j + 1);
    }
    return;
}

void initLeft(std::vector<int> &vtr)
{
    int coord0 = vtr.size() / 2 - 1;

    for (int j = coord0; j > 0; --j)
    {
        int first = get(vtr, j);
        int second = get(vtr, j + 1);
        int ans = sum(first, second);
        int t = total(first, ans);
        put(t, vtr, j - 1);
    }
    return;
}

void initDown(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int column)
{
    int first = get(a, column);
    int second = get(b, column);
    int ans = sum(first, second);
    int t = total(first, ans);
    put(t, c, column);
}

void initUp(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int column)
{
    int first = get(a, column);
    int second = get(b, column);
    int ans = sum(first, second);
    int t = total(first, ans);
    put(t, c, column);
}

// initial steps to complete first grid
void initStepOne(std::vector<std::vector<int>> &arr)
{
    initRight(arr[3]);
    initRight(arr[4]);
    initLeft(arr[3]);
    initLeft(arr[4]);
}

void initStepTwo(std::vector<std::vector<int>> &arr)
{
    initDown(arr[4], arr[3], arr[5], 3);
    initDown(arr[5], arr[4], arr[6], 3);
    initDown(arr[6], arr[5], arr[7], 3);

    initDown(arr[4], arr[3], arr[5], 4);
    initDown(arr[5], arr[4], arr[6], 4);
    initDown(arr[6], arr[5], arr[7], 4);

    initUp(arr[3], arr[4], arr[2], 3);
    initUp(arr[2], arr[3], arr[1], 3);
    initUp(arr[1], arr[2], arr[0], 3);

    initUp(arr[3], arr[4], arr[2], 4);
    initUp(arr[2], arr[3], arr[1], 4);
    initUp(arr[1], arr[2], arr[0], 4);
}

void initStepThree(std::vector<std::vector<int>> &arr)
{
    initRight(arr[0]);
    initRight(arr[1]);
    initRight(arr[2]);
    initLeft(arr[0]);
    initLeft(arr[1]);
    initLeft(arr[2]);

    initRight(arr[5]);
    initRight(arr[6]);
    initRight(arr[7]);
    initLeft(arr[5]);
    initLeft(arr[6]);
    initLeft(arr[7]);
}

void addRight(const std::vector<int> a, int column, std::vector<int> &b)
{
    int first = get(a, column);
    int second = get(a, column - 1);
    int ans = sum(first, second);
    int t = total(first, ans);
    put(t, b, column + 1);
}

void addLeft(const std::vector<int> a, int column, std::vector<int> &b)
{
    int first = get(a, column);
    int second = get(a, column + 1);
    int ans = sum(first, second);
    int t = total(first, ans);
    //std::cout << first << "," << second << std::endl;
    put(t, b, column - 1);
}

//
// diagonally
//
void addUpLeft(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int column)
{
    int first = get(a, column - 1);
    int second = get(b, column);
    int ans = sum(first, second);
    int t = total(first, ans);
    //std::cout << "upleft col " << column << first << "," << second << "tot " << t << "\n";
    put(t, c, column - 2);
}

void addDownRight(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int column)
{
    int first = get(a, column + 1);
    int second = get(b, column);
    int ans = sum(first, second);
    int t = total(first, ans);
    put(t, c, column + 2);
    //std::cout << "downright col" << column << first << "," << second << "tot " << t << "\n";
}

void addUpRight(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int column)
{
    int first = get(a, column + 1);
    int second = get(b, column);
    int ans = sum(first, second);
    int t = total(first, ans);
    put(t, c, column + 2);
    //std::cout << "upright col" << column << first << "," << second << "tot " << t << "\n";
}

void addDownLeft(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int column)
{
    int first = get(a, column - 1);
    int second = get(b, column);
    int ans = sum(first, second);
    int t = total(first, ans);
    //std::cout << "downleft col" << column << first << "," << second << "tot " << t << "\n";
    put(t, c, column - 2);
}

void avgDiagonals(
    std::vector<std::vector<int>> const a,
    std::vector<std::vector<int>> const b,
    std::vector<std::vector<int>> const c,
    std::vector<std::vector<int>> const d,
    std::vector<std::vector<int>> &result)
{
    int sum = 0;

    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < a[0].size(); ++j)
        {
            sum += a[i][j];
            sum += b[i][j];
            sum += c[i][j];
            sum += d[i][j];
            /*
            std::cout << a[i][j]
                << "+" 
                << b[i][j]
                << "+"
                << c[i][j]
                << "+"
                << d[i][j]
                << "="
                << sum
                << "/4="
                << sum/4;
            */

            putDivideFour(sum, result, i, j);
            // reset for next square
            sum = 0;
        }
        //std::cout << "\n";
    }
}

void addAverage(std::vector<std::vector<int>> const a, std::vector<std::vector<int>> const b, std::vector<std::vector<int>> &c)
{
    int sum = 0;

    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < a[0].size(); ++j)
        {
            sum += a[i][j];
            sum += b[i][j];
            putDivideTwo(sum, c, i, j);
            sum = 0;
        }
    }
}

void addStepOne(std::vector<std::vector<int>> const a, std::vector<std::vector<int>> &b)
{
    addRight(a[0], 1, b[0]);
    addRight(a[0], 2, b[0]);
    addRight(a[0], 3, b[0]);
    addRight(a[0], 4, b[0]);
    addRight(a[0], 5, b[0]);
    addRight(a[0], 6, b[0]);

    addRight(a[1], 1, b[1]);
    addRight(a[1], 2, b[1]);
    addRight(a[1], 3, b[1]);
    addRight(a[1], 4, b[1]);
    addRight(a[1], 5, b[1]);
    addRight(a[1], 6, b[1]);

    addRight(a[2], 1, b[2]);
    addRight(a[2], 2, b[2]);
    addRight(a[2], 3, b[2]);
    addRight(a[2], 4, b[2]);
    addRight(a[2], 5, b[2]);
    addRight(a[2], 6, b[2]);

    addRight(a[3], 1, b[3]);
    addRight(a[3], 2, b[3]);
    addRight(a[3], 3, b[3]);
    addRight(a[3], 4, b[3]);
    addRight(a[3], 5, b[3]);
    addRight(a[3], 6, b[3]);

    addRight(a[4], 1, b[4]);
    addRight(a[4], 2, b[4]);
    addRight(a[4], 3, b[4]);
    addRight(a[4], 4, b[4]);
    addRight(a[4], 5, b[4]);
    addRight(a[4], 6, b[4]);

    addRight(a[5], 1, b[5]);
    addRight(a[5], 2, b[5]);
    addRight(a[5], 3, b[5]);
    addRight(a[5], 4, b[5]);
    addRight(a[5], 5, b[5]);
    addRight(a[5], 6, b[5]);

    addRight(a[6], 1, b[6]);
    addRight(a[6], 2, b[6]);
    addRight(a[6], 3, b[6]);
    addRight(a[6], 4, b[6]);
    addRight(a[6], 5, b[6]);
    addRight(a[6], 6, b[6]);

    addRight(a[7], 1, b[7]);
    addRight(a[7], 2, b[7]);
    addRight(a[7], 3, b[7]);
    addRight(a[7], 4, b[7]);
    addRight(a[7], 5, b[7]);
    addRight(a[7], 6, b[7]);
}

void addStepTwo(const std::vector<std::vector<int>> a, std::vector<std::vector<int>> &b)
{
    addLeft(a[0], 6, b[0]);
    addLeft(a[0], 5, b[0]);
    addLeft(a[0], 4, b[0]);
    addLeft(a[0], 3, b[0]);
    addLeft(a[0], 2, b[0]);
    addLeft(a[0], 1, b[0]);

    addLeft(a[1], 6, b[1]);
    addLeft(a[1], 5, b[1]);
    addLeft(a[1], 4, b[1]);
    addLeft(a[1], 3, b[1]);
    addLeft(a[1], 2, b[1]);
    addLeft(a[1], 1, b[1]);

    addLeft(a[2], 6, b[2]);
    addLeft(a[2], 5, b[2]);
    addLeft(a[2], 4, b[2]);
    addLeft(a[2], 3, b[2]);
    addLeft(a[2], 2, b[2]);
    addLeft(a[2], 1, b[2]);

    addLeft(a[3], 6, b[3]);
    addLeft(a[3], 5, b[3]);
    addLeft(a[3], 4, b[3]);
    addLeft(a[3], 3, b[3]);
    addLeft(a[3], 2, b[3]);
    addLeft(a[3], 1, b[3]);

    addLeft(a[4], 6, b[4]);
    addLeft(a[4], 5, b[4]);
    addLeft(a[4], 4, b[4]);
    addLeft(a[4], 3, b[4]);
    addLeft(a[4], 2, b[4]);
    addLeft(a[4], 1, b[4]);

    addLeft(a[5], 6, b[5]);
    addLeft(a[5], 5, b[5]);
    addLeft(a[5], 4, b[5]);
    addLeft(a[5], 3, b[5]);
    addLeft(a[5], 2, b[5]);
    addLeft(a[5], 1, b[5]);

    addLeft(a[6], 6, b[6]);
    addLeft(a[6], 5, b[6]);
    addLeft(a[6], 4, b[6]);
    addLeft(a[6], 3, b[6]);
    addLeft(a[6], 2, b[6]);
    addLeft(a[6], 1, b[6]);

    addLeft(a[7], 6, b[7]);
    addLeft(a[7], 5, b[7]);
    addLeft(a[7], 4, b[7]);
    addLeft(a[7], 3, b[7]);
    addLeft(a[7], 2, b[7]);
    addLeft(a[7], 1, b[7]);
}

// don't alter values as this calculates each
// cell in a particular order
void diagonalStepOne(std::vector<std::vector<int>> &arrOriginal, std::vector<std::vector<int>> &arrNew)
{
    // column 3
    addUpLeft(arrOriginal[6], arrOriginal[7], arrNew[5], 2);
    // column 4
    addUpLeft(arrOriginal[6], arrOriginal[7], arrNew[5], 3);
    addUpLeft(arrOriginal[5], arrOriginal[6], arrNew[4], 2);
    // column 5
    addUpLeft(arrOriginal[6], arrOriginal[7], arrNew[5], 4);
    addUpLeft(arrOriginal[5], arrOriginal[6], arrNew[4], 3);
    addUpLeft(arrOriginal[4], arrOriginal[5], arrNew[3], 2);
    // column 6
    addUpLeft(arrOriginal[6], arrOriginal[7], arrNew[5], 5);
    addUpLeft(arrOriginal[5], arrOriginal[6], arrNew[4], 4);
    addUpLeft(arrOriginal[4], arrOriginal[5], arrNew[3], 3);
    addUpLeft(arrOriginal[3], arrOriginal[4], arrNew[2], 2);
    //column 7
    addUpLeft(arrOriginal[6], arrOriginal[7], arrNew[5], 6);
    addUpLeft(arrOriginal[5], arrOriginal[6], arrNew[4], 5);
    addUpLeft(arrOriginal[4], arrOriginal[5], arrNew[3], 4);
    addUpLeft(arrOriginal[3], arrOriginal[4], arrNew[2], 3);
    addUpLeft(arrOriginal[2], arrOriginal[3], arrNew[1], 2);
    // column 8
    addUpLeft(arrOriginal[6], arrOriginal[7], arrNew[5], 7);
    addUpLeft(arrOriginal[5], arrOriginal[6], arrNew[4], 6);
    addUpLeft(arrOriginal[4], arrOriginal[5], arrNew[3], 5);
    addUpLeft(arrOriginal[3], arrOriginal[4], arrNew[2], 4);
    addUpLeft(arrOriginal[2], arrOriginal[3], arrNew[1], 3);
    addUpLeft(arrOriginal[1], arrOriginal[2], arrNew[0], 2);
    // time to traverse upward
    addUpLeft(arrOriginal[5], arrOriginal[6], arrNew[4], 7);
    addUpLeft(arrOriginal[4], arrOriginal[5], arrNew[3], 6);
    addUpLeft(arrOriginal[3], arrOriginal[4], arrNew[2], 5);
    addUpLeft(arrOriginal[2], arrOriginal[3], arrNew[1], 4);
    addUpLeft(arrOriginal[1], arrOriginal[2], arrNew[0], 3);
    // next traverse
    addUpLeft(arrOriginal[4], arrOriginal[5], arrNew[3], 7);
    addUpLeft(arrOriginal[3], arrOriginal[4], arrNew[2], 6);
    addUpLeft(arrOriginal[2], arrOriginal[3], arrNew[1], 5);
    addUpLeft(arrOriginal[1], arrOriginal[2], arrNew[0], 4);
    // next traverse
    addUpLeft(arrOriginal[3], arrOriginal[4], arrNew[2], 7);
    addUpLeft(arrOriginal[2], arrOriginal[3], arrNew[1], 6);
    addUpLeft(arrOriginal[1], arrOriginal[2], arrNew[0], 5);
    // next traverse
    addUpLeft(arrOriginal[2], arrOriginal[3], arrNew[1], 7);
    addUpLeft(arrOriginal[1], arrOriginal[2], arrNew[0], 6);
    // last one
    addUpLeft(arrOriginal[1], arrOriginal[2], arrNew[0], 7);
}

void diagonalStepTwo(std::vector<std::vector<int>> &arrOriginal, std::vector<std::vector<int>> &arrNew)
{
    // column 5
    addDownRight(arrOriginal[1], arrOriginal[0], arrNew[2], 5);
    // column 4
    addDownRight(arrOriginal[1], arrOriginal[0], arrNew[2], 4);
    addDownRight(arrOriginal[2], arrOriginal[1], arrNew[3], 5);
    // column 3
    addDownRight(arrOriginal[1], arrOriginal[0], arrNew[2], 3);
    addDownRight(arrOriginal[2], arrOriginal[1], arrNew[3], 4);
    addDownRight(arrOriginal[3], arrOriginal[2], arrNew[4], 5);
    //column 2
    addDownRight(arrOriginal[1], arrOriginal[0], arrNew[2], 2);
    addDownRight(arrOriginal[2], arrOriginal[1], arrNew[3], 3);
    addDownRight(arrOriginal[3], arrOriginal[2], arrNew[4], 4);
    addDownRight(arrOriginal[4], arrOriginal[3], arrNew[5], 5);
    // column 1
    addDownRight(arrOriginal[1], arrOriginal[0], arrNew[2], 1);
    addDownRight(arrOriginal[2], arrOriginal[1], arrNew[3], 2);
    addDownRight(arrOriginal[3], arrOriginal[2], arrNew[4], 3);
    addDownRight(arrOriginal[4], arrOriginal[3], arrNew[5], 4);
    addDownRight(arrOriginal[5], arrOriginal[4], arrNew[6], 5);
    // column 0
    addDownRight(arrOriginal[1], arrOriginal[0], arrNew[2], 0);
    addDownRight(arrOriginal[2], arrOriginal[1], arrNew[3], 1);
    addDownRight(arrOriginal[3], arrOriginal[2], arrNew[4], 2);
    addDownRight(arrOriginal[4], arrOriginal[3], arrNew[5], 3);
    addDownRight(arrOriginal[5], arrOriginal[4], arrNew[6], 4);
    addDownRight(arrOriginal[6], arrOriginal[5], arrNew[7], 5);
    // traverse downwards
    addDownRight(arrOriginal[2], arrOriginal[1], arrNew[3], 0);
    addDownRight(arrOriginal[3], arrOriginal[2], arrNew[4], 1);
    addDownRight(arrOriginal[4], arrOriginal[3], arrNew[5], 2);
    addDownRight(arrOriginal[5], arrOriginal[4], arrNew[6], 3);
    addDownRight(arrOriginal[6], arrOriginal[5], arrNew[7], 4);
    // traverse
    addDownRight(arrOriginal[3], arrOriginal[2], arrNew[4], 0);
    addDownRight(arrOriginal[4], arrOriginal[3], arrNew[5], 1);
    addDownRight(arrOriginal[5], arrOriginal[4], arrNew[6], 2);
    addDownRight(arrOriginal[6], arrOriginal[5], arrNew[7], 3);
    // traverse
    addDownRight(arrOriginal[4], arrOriginal[3], arrNew[5], 0);
    addDownRight(arrOriginal[5], arrOriginal[4], arrNew[6], 1);
    addDownRight(arrOriginal[6], arrOriginal[5], arrNew[7], 2);
    // traverse
    addDownRight(arrOriginal[5], arrOriginal[4], arrNew[6], 0);
    addDownRight(arrOriginal[6], arrOriginal[5], arrNew[7], 1);
    // traverse
    addDownRight(arrOriginal[6], arrOriginal[5], arrNew[7], 0);
}

void diagonalStepThree(std::vector<std::vector<int>> &arrOriginal, std::vector<std::vector<int>> &arrNew)
{
    // row 1
    addUpRight(arrOriginal[1], arrOriginal[2], arrNew[0], 0);
    // row 2
    addUpRight(arrOriginal[2], arrOriginal[3], arrNew[1], 0);
    addUpRight(arrOriginal[1], arrOriginal[2], arrNew[0], 1);
    // row 3
    addUpRight(arrOriginal[3], arrOriginal[4], arrNew[2], 0);
    addUpRight(arrOriginal[2], arrOriginal[3], arrNew[1], 1);
    addUpRight(arrOriginal[1], arrOriginal[2], arrNew[0], 2);
    // row 4
    addUpRight(arrOriginal[4], arrOriginal[5], arrNew[3], 0);
    addUpRight(arrOriginal[3], arrOriginal[4], arrNew[2], 1);
    addUpRight(arrOriginal[2], arrOriginal[3], arrNew[1], 2);
    addUpRight(arrOriginal[1], arrOriginal[2], arrNew[0], 3);
    // row 5
    addUpRight(arrOriginal[5], arrOriginal[6], arrNew[4], 0);
    addUpRight(arrOriginal[4], arrOriginal[5], arrNew[3], 1);
    addUpRight(arrOriginal[3], arrOriginal[4], arrNew[2], 2);
    addUpRight(arrOriginal[2], arrOriginal[3], arrNew[1], 3);
    addUpRight(arrOriginal[1], arrOriginal[2], arrNew[0], 4);
    // row 6
    addUpRight(arrOriginal[6], arrOriginal[7], arrNew[5], 0);
    addUpRight(arrOriginal[5], arrOriginal[6], arrNew[4], 1);
    addUpRight(arrOriginal[4], arrOriginal[5], arrNew[3], 2);
    addUpRight(arrOriginal[3], arrOriginal[4], arrNew[2], 3);
    addUpRight(arrOriginal[2], arrOriginal[3], arrNew[1], 4);
    addUpRight(arrOriginal[1], arrOriginal[2], arrNew[0], 5);
    // traverse right
    addUpRight(arrOriginal[6], arrOriginal[7], arrNew[5], 1);
    addUpRight(arrOriginal[5], arrOriginal[6], arrNew[4], 2);
    addUpRight(arrOriginal[4], arrOriginal[5], arrNew[3], 3);
    addUpRight(arrOriginal[3], arrOriginal[4], arrNew[2], 4);
    addUpRight(arrOriginal[2], arrOriginal[3], arrNew[1], 5);
    // traverse right
    addUpRight(arrOriginal[6], arrOriginal[7], arrNew[5], 2);
    addUpRight(arrOriginal[5], arrOriginal[6], arrNew[4], 3);
    addUpRight(arrOriginal[4], arrOriginal[5], arrNew[3], 4);
    addUpRight(arrOriginal[3], arrOriginal[4], arrNew[2], 5);
    // traverse right
    addUpRight(arrOriginal[6], arrOriginal[7], arrNew[5], 3);
    addUpRight(arrOriginal[5], arrOriginal[6], arrNew[4], 4);
    addUpRight(arrOriginal[4], arrOriginal[5], arrNew[3], 5);
    // traverse right
    addUpRight(arrOriginal[6], arrOriginal[7], arrNew[5], 4);
    addUpRight(arrOriginal[5], arrOriginal[6], arrNew[4], 5);
    // traverse right
    addUpRight(arrOriginal[6], arrOriginal[7], arrNew[5], 5);
}

void diagonalStepFour(std::vector<std::vector<int>> &arrOriginal, std::vector<std::vector<int>> &arrNew)
{
    // row 2
    addDownLeft(arrOriginal[1], arrOriginal[0], arrNew[2], 2);
    // row 3
    addDownLeft(arrOriginal[1], arrOriginal[0], arrNew[2], 3);
    addDownLeft(arrOriginal[2], arrOriginal[1], arrNew[3], 2);
    // row 4
    addDownLeft(arrOriginal[1], arrOriginal[0], arrNew[2], 4);
    addDownLeft(arrOriginal[2], arrOriginal[1], arrNew[3], 3);
    addDownLeft(arrOriginal[3], arrOriginal[2], arrNew[4], 2);
    // row 5
    addDownLeft(arrOriginal[1], arrOriginal[0], arrNew[2], 5);
    addDownLeft(arrOriginal[2], arrOriginal[1], arrNew[3], 4);
    addDownLeft(arrOriginal[3], arrOriginal[2], arrNew[4], 3);
    addDownLeft(arrOriginal[4], arrOriginal[3], arrNew[5], 2);
    // row 6
    addDownLeft(arrOriginal[1], arrOriginal[0], arrNew[2], 6);
    addDownLeft(arrOriginal[2], arrOriginal[1], arrNew[3], 5);
    addDownLeft(arrOriginal[3], arrOriginal[2], arrNew[4], 4);
    addDownLeft(arrOriginal[4], arrOriginal[3], arrNew[5], 3);
    addDownLeft(arrOriginal[5], arrOriginal[4], arrNew[6], 2);
    // row 7
    addDownLeft(arrOriginal[1], arrOriginal[0], arrNew[2], 7);
    addDownLeft(arrOriginal[2], arrOriginal[1], arrNew[3], 6);
    addDownLeft(arrOriginal[3], arrOriginal[2], arrNew[4], 5);
    addDownLeft(arrOriginal[4], arrOriginal[3], arrNew[5], 4);
    addDownLeft(arrOriginal[5], arrOriginal[4], arrNew[6], 3);
    addDownLeft(arrOriginal[6], arrOriginal[5], arrNew[7], 2);
    // traverse down
    addDownLeft(arrOriginal[2], arrOriginal[1], arrNew[3], 7);
    addDownLeft(arrOriginal[3], arrOriginal[2], arrNew[4], 6);
    addDownLeft(arrOriginal[4], arrOriginal[3], arrNew[5], 5);
    addDownLeft(arrOriginal[5], arrOriginal[4], arrNew[6], 4);
    addDownLeft(arrOriginal[6], arrOriginal[5], arrNew[7], 3);
    // traverse down
    addDownLeft(arrOriginal[3], arrOriginal[2], arrNew[4], 7);
    addDownLeft(arrOriginal[4], arrOriginal[3], arrNew[5], 6);
    addDownLeft(arrOriginal[5], arrOriginal[4], arrNew[6], 5);
    addDownLeft(arrOriginal[6], arrOriginal[5], arrNew[7], 4);
    // traverse down
    addDownLeft(arrOriginal[4], arrOriginal[3], arrNew[5], 7);
    addDownLeft(arrOriginal[5], arrOriginal[4], arrNew[6], 6);
    addDownLeft(arrOriginal[6], arrOriginal[5], arrNew[7], 5);
    // traverse down
    addDownLeft(arrOriginal[5], arrOriginal[4], arrNew[6], 7);
    addDownLeft(arrOriginal[6], arrOriginal[5], arrNew[7], 6);
    // traverse down
    addDownLeft(arrOriginal[6], arrOriginal[5], arrNew[7], 7);
}

//
// SDL functions
//

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

void printNumbers(SDL_Renderer *renderer, int w, int x, int y, int z)
{
    SDL_Rect position;
    position.x = 100;
    position.y = 500;
    position.h = 50;
    position.w = 50;

    std::string sw = std::to_string(w);
    std::string sx = std::to_string(x);
    std::string sy = std::to_string(y);
    std::string sz = std::to_string(z);

    SDL_Texture *texW = loadText(renderer, sw.c_str());
    SDL_Texture *texX = loadText(renderer, sx.c_str());
    SDL_Texture *texY = loadText(renderer, sy.c_str());
    SDL_Texture *texZ = loadText(renderer, sz.c_str());

    SDL_RenderCopy(renderer, texW, NULL, &position);
    position.x += 100;
    SDL_RenderCopy(renderer, texX, NULL, &position);
    position.y += 100;
    position.x -= 100;
    SDL_RenderCopy(renderer, texY, NULL, &position);
    position.x += 100;
    SDL_RenderCopy(renderer, texZ, NULL, &position);
}

SDL_Texture *createSquare(SDL_Renderer *renderer, int r, int g, int b)

{
    SDL_Surface *surface = NULL;
    surface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
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
    window = SDL_CreateWindow("Android SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        fprintf(stderr, "%s", SDL_GetError());

    //
    // create vectors
    //
    int w{0};
    int x{3};
    int y{5};
    int z{7};

    std::vector<std::vector<int>> arr =
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, w, x, 0, 0, 0},
         {0, 0, 0, y, z, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}};

    std::vector<std::vector<int>> arrEmpty =
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}};

    // make copies for diagonal addition
    std::vector<std::vector<int>> arrDiagUpLeft = arrEmpty;
    std::vector<std::vector<int>> arrDiagDownRight = arrEmpty;
    std::vector<std::vector<int>> arrDiagUpRight = arrEmpty;
    std::vector<std::vector<int>> arrDiagDownLeft = arrEmpty;

    // final diagonal average
    std::vector<std::vector<int>> arrDiagFinal = arrEmpty;

    // some vectors for bringing addition
    // together
    std::vector<std::vector<int>> arrAddedLeft = arrEmpty;
    std::vector<std::vector<int>> arrAddedRight = arrEmpty;
    std::vector<std::vector<int>> arrAddedAvg = arrEmpty;

    //
    // how to start the grid off
    //

    // have a backup grid
    initStepOne(arr);
    initStepTwo(arr);
    initStepThree(arr);

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

    //
    // begin grid calculations
    //

    //main loop
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    srand(time(0));
    bool go = true;

    for (int i = 0; i < 3; ++i)
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
        
        // custom w, x, y, z go here
        w = 0;
        x = 3;
        y = 5;
        z = 8;

        std::vector<std::vector<int>> arr =
            {{0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, w, x, 0, 0, 0},
             {0, 0, 0, y, z, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}};

        // have a backup grid
        initStepOne(arr);
        initStepTwo(arr);
        initStepThree(arr);

        // clear screen
        SDL_RenderClear(renderer);

        printgrid(arr, redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer);

        printNumbers(renderer, w, x, y, z);

        // update screen
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);

        for (int j = 0; j < 50; ++j)
        {
            // read from arrReady and place into arrDiag
            diagonalStepOne(arr, arrDiagUpLeft);
            diagonalStepTwo(arr, arrDiagDownRight);
            diagonalStepThree(arr, arrDiagUpRight);
            diagonalStepFour(arr, arrDiagDownLeft);
            
            // average diagonals into arrFinal
            avgDiagonals(
                arrDiagUpLeft,
                arrDiagDownRight,
                arrDiagUpRight,
                arrDiagDownLeft,
                arrDiagFinal);

            // add up arrFinal
            // and store in arrAddedAvg
            addStepOne(arrDiagFinal, arrAddedRight);
            addStepTwo(arrDiagFinal, arrAddedLeft);
            addAverage(arrAddedLeft, arrAddedRight, arrAddedAvg);

            printgrid(arrAddedAvg, redtexture, greentexture, bluetexture, yellowtexture, purpletexture, renderer);
            
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            
            // clear old square and
            // what is the next iteration?
            SDL_RenderClear(renderer);
            arr = arrAddedAvg;
        }
        go = false;
        arr = arrEmpty;
    }

    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
