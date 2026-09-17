#ifndef PIECE_HPP
#define PIECE_HPP

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int BLOCK_SIZE = 60;

inline int pieces[7][4][4] = 
{
    { // IShaped
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    { // JShaped
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0}
    },

    { // LShaped
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0}
    },

    { // OShaped
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    
    {// SShaped
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },

    {// TShaped
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0}
    },
    
    {// ZShaped
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0}
    }
};

enum Form
{
    IShaped,
    JShaped,
    LShaped,
    OShaped,
    SShaped,
    TShaped,
    ZShaped
};

typedef struct 
{
    int x;
    int y;
}Coordinates;

void swap(int *a, int *b);

class Piece
{
    public:
        Form shape;
        int shape2D[4][4];
        Coordinates position;
        Piece();
        void Rotate(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2]);
        void Slide(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2], int direction, int *collisionIDX);
        void Collapse(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2]);
        int CheckCollision(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2]);
};

#endif