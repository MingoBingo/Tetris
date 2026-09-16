#include <stdio.h>
#include <iostream>
#include <raylib.h>
#include <time.h>


const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    return 0;
}