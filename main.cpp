#include <stdio.h>
#include <iostream>
#include <raylib.h>
#include <time.h>
#include "piece.hpp"

const int BOARD_OFFSET_X = 150;
const int BOARD_OFFSET_Y = 100;

const int NEXT_PIECE_OFFSET_X = 300;
const int NEXT_PIECE_OFFSET_Y = 150;

const int screenWidth = 1200;
const int screenHeight = 1600;

int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2] = {0};

void prepareBoard(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2])
{
    for(int i = 0; i < BOARD_HEIGHT + 2; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH + 2; ++j)
        {
            int boardX = j * BLOCK_SIZE + BOARD_OFFSET_X;
            int boardY = i * BLOCK_SIZE + BOARD_OFFSET_Y;
            
            if(i == 0 || i == BOARD_HEIGHT + 1)
            {
                board[i][j] = 3;
            }
            else if(j == 0 || j == BOARD_WIDTH + 1)
            {
                board[i][j] = 2;
            }
        }
    }
}

bool lineCheck(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2], int *line)
{
    int count = 0;
    for(int i = 1; i < BOARD_HEIGHT + 1; ++i)
    {
        count = 0;
        for(int j = 1; j < BOARD_WIDTH + 1; ++j)
        {
            if(board[i][j] >= 10)
            {
                count++;
            }
            else break;
        }
        if(count == BOARD_WIDTH)
        {
            *line = i;
            return true;
        }
    }
    *line = -1;
    return false;
}


void lineDelete(int board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2], int lineIndex)
{
    for(int i = lineIndex; i > 1; --i)
    {
        for(int j = 1; j < BOARD_WIDTH + 1; ++j)
        {
            board[i][j] = board[i-1][j];
        }
    }
}



Color pieceColors[7] = 
{
    SKYBLUE,   // IShaped 
    BLUE,      // JShaped
    ORANGE,    // LShaped
    GOLD ,    // OShaped
    GREEN,     // SShaped
    PURPLE,    // TShaped
    RED        // ZShaped
};

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);
    prepareBoard(board);

    float dropTimer = 0.0f;
    float dropInterval = 1.0f;

    Piece currentPiece, nextPiece;
    bool gameOver = false;

    while(!WindowShouldClose())
    {   
        if(!gameOver)
        {
                dropTimer += GetFrameTime();

            if(dropTimer >= dropInterval)
            {
                int status = -1;

                currentPiece.Slide(board, 2, &status);

                if(status > 0)
                {
                    for(int i = 0; i < 4; ++i)
                    {
                        for(int j = 0; j < 4; ++j)
                        {
                            if(currentPiece.shape2D[i][j] == 1)
                                board[i + currentPiece.position.y][j + currentPiece.position.x] = currentPiece.shape + 10;
                        }
                    }
                    int line;
                    while(lineCheck(board, &line) == 1)
                    {
                        lineDelete(board, line);
                    }
                    
                    currentPiece = nextPiece;
                    nextPiece = Piece();

                    if(currentPiece.CheckCollision(board) != 0)
                    {
                        gameOver = true;
                    }
                }
                dropTimer = 0.0f;
            }

            int dummystatus = -1;

            if(IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
            {
                currentPiece.Slide(board, 0, &dummystatus);
            }
            if(IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
            {
                currentPiece.Slide(board, 1, &dummystatus);
            }
            if(IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))
            {
                currentPiece.Slide(board, 2, &dummystatus);
            }
            if(IsKeyPressed(KEY_SPACE) || IsKeyPressedRepeat(KEY_SPACE))
            {
                currentPiece.Collapse(board);
            }
            if(IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP))
            {
                currentPiece.Rotate(board);
            }
        }
        

        BeginDrawing();

        if(gameOver)
        {
            DrawText("GAME OVER", 350, 1500, 50, RED);
            DrawText("Press Enter to exit", 300, 1550, 40, RED);

            if(IsKeyPressed(KEY_ENTER))
                break;
        }

        ClearBackground(DARKGRAY);

        int panelX = ((BOARD_WIDTH + 2) * BLOCK_SIZE) + BOARD_OFFSET_X;
        int panelY = BOARD_OFFSET_Y;

        DrawText("NEXT", panelX, panelY - 40, 30, WHITE);
        DrawRectangleLines(panelX, panelY, 5 * BLOCK_SIZE, 5 * BLOCK_SIZE, BLACK);

        for(int i = 0; i < 4; ++i) //Draw Next Piece
        {
            for(int j = 0; j < 4; ++j)
            {
                int nextPanelX = panelX + (j * BLOCK_SIZE);
                int nextPanelY = panelY + (i * BLOCK_SIZE);

                if(nextPiece.shape2D[i][j] == 1)
                {
                    DrawRectangle(nextPanelX, nextPanelY, BLOCK_SIZE, BLOCK_SIZE, pieceColors[nextPiece.shape]);
                    DrawRectangleLines(nextPanelX, nextPanelY, BLOCK_SIZE, BLOCK_SIZE, WHITE);
                }
            }
        }

        for(int i = 0; i < BOARD_HEIGHT + 2; ++i) //Board Drawing
        {
            for(int j = 0; j < BOARD_WIDTH + 2; ++j)
            {
                int boardX = j * BLOCK_SIZE + BOARD_OFFSET_X;
                int boardY = i * BLOCK_SIZE + BOARD_OFFSET_Y;

                if(board[i][j] >= 10)
                {
                    DrawRectangle(boardX, boardY, BLOCK_SIZE, BLOCK_SIZE, pieceColors[board[i][j] - 10]);
                    DrawRectangleLines(boardX, boardY, BLOCK_SIZE, BLOCK_SIZE, WHITE);
                }
                else if(board[i][j] == 0)
                {
                    DrawRectangleLines(boardX, boardY, BLOCK_SIZE, BLOCK_SIZE, LIGHTGRAY);
                }
                else if(board[i][j] == 2 || board[i][j] == 3)
                {
                    DrawRectangle(boardX, boardY, BLOCK_SIZE, BLOCK_SIZE, BLACK);
                }
            }
        }

        for(int p = 0; p < 4; ++p) //Falling Piece Drawing
        {
            for(int k = 0; k < 4; ++k)
            {
                if(currentPiece.shape2D[p][k] == 1)
                {
                    int boardX = (k + currentPiece.position.x) * BLOCK_SIZE + BOARD_OFFSET_X;
                    int boardY = (p + currentPiece.position.y) * BLOCK_SIZE + BOARD_OFFSET_Y;

                    DrawRectangle(boardX, boardY, BLOCK_SIZE, BLOCK_SIZE, pieceColors[currentPiece.shape]);
                    DrawRectangleLines(boardX, boardY, BLOCK_SIZE, BLOCK_SIZE, WHITE);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}