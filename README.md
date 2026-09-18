# 🧱 Raylib Tetris in C++

A classic Tetris clone built from scratch using C++ and the [Raylib](https://www.raylib.com/) library. 

This project focuses on clean, static memory management and a modular, logical structure for game mechanics. Instead of complex pointer arithmetic, the game uses a fixed 2D matrix for the board, ensuring robust collision detection, reliable line-clearing, and zero memory leaks.

## ✨ Features

* **Classic Tetris Mechanics:** Sliding, rotation, soft drops, and hard drops.
* **Flawless Collision Detection:** Pieces stop exactly where they should, respecting walls, the floor, and other locked pieces.
* **Next Piece Preview:** A UI panel displaying the upcoming Tetromino.
* **Line Clearing:** Fully implemented line detection and "gravity" shift for blocks above cleared lines.
* **Game State Management:** Includes a proper Game Over screen with a clean exit sequence.
* **Delta-Time Gravity:** Piece falling speed is decoupled from the frame rate using `GetFrameTime()` for smooth, consistent gameplay at 60 FPS.

## 🎮 Controls

* **Left / Right Arrows:** Move piece horizontally.
* **Down Arrow:** Soft drop (move piece down faster).
* **Up Arrow:** Rotate piece.
* **Spacebar:** Hard drop (instantly collapse the piece to the bottom).
* **ENTER:** Exit the game (only on the Game Over screen).

## 🛠️ Prerequisites

To compile and run this project, you need:
1. A C++ compiler (like GCC / `g++`).
2. **[Raylib](https://github.com/raysan5/raylib)** installed on your system.

## 🚀 How to Build and Run

Open your terminal or command prompt in the project folder and run the appropriate command for your operating system.

### Linux
Compile the game linking the Raylib library and its dependencies:
```bash
g++ main.cpp piece.cpp -o tetris -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
---
*Note: This README was drafted with AI assistance.*
