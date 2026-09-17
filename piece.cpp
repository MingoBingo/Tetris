#include "piece.hpp"
#include <cstdlib>

void swap(int *a, int *b)
{
    int aux = (*a);
    (*a) = (*b);
    (*b) = aux;
}

Piece::Piece()
{
    shape = static_cast<Form>(rand() % 7);

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        shape2D[i][j] = pieces[shape][i][j];

    position.x = 4;
    position.y = 0;
}

void Piece::Rotate(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2])
{
    Piece clone = *this;

    for(int i = 0; i < 4; ++i)
        for(int j = i; j < 4; ++j)
        swap(&clone.shape2D[j][i], &clone.shape2D[i][j]);
    
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 2; ++j)
        swap(&clone.shape2D[i][j], &clone.shape2D[i][3-j]);

    if(clone.CheckCollision(board) == 0)
    {
        *this = clone;
    }
}

void Piece::Slide(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2], int direction, int *collisionIDX)
{
    Piece clone = *this;

    switch(direction)
    {
        case 0:
            clone.position.x--;
            break;
        case 1:
            clone.position.x++;
            break;
        case 2:
            clone.position.y++;
            break;
    }

   *collisionIDX = clone.CheckCollision(board);

   if(*collisionIDX == 0)
   {
        *this = clone;
   }
}

void Piece::Collapse(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2])
{
    while(!CheckCollision(board))
    {
         position.y++;
    }

    position.y--;
}

int Piece::CheckCollision(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2])
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(shape2D[i][j] == 1)
            {
                if(board[i + position.y][j + position.x] > 0)
                    return board[i + position.y][j + position.x];
            }
        }
    }
    return 0;
}