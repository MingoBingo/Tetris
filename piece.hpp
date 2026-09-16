#ifndef PIECE_HPP
#define PIECE_HPP

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
        {1, 1, 0, 0},
        {0, 1, 1, 0},
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

enum Rotation
{
    Left,
    Right
};

typedef struct 
{
    int x;
    int y;
}Coordinates;

class Piece
{
    public:
        Form shape;
        Coordinates position;
        Piece();
        void Rotate(Rotation movement);
        void Slide();
        void Collapse();
        int CheckCollision();
};

#endif