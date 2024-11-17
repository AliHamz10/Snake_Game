# Snake Game in C++

A classic Snake Game implemented in C++ with basic input handling, dynamic difficulty levels, and a terminal-based rendering system.

## Features

- **Dynamic Game Rendering**: The game is rendered directly in the terminal using ASCII characters.
- **Multiple Difficulty Levels**: Choose between Easy, Medium, and Hard difficulty.
- **Score Tracking**: The game displays the player's score in real-time.
- **Simple Input Handling**: Control the snake using `W`, `A`, `S`, `D` keys.
- **Food Mechanics**: The snake grows longer with each food consumed.

## How to Play

1. Run the program in a terminal.
2. Enter your name when prompted.
3. Select a difficulty level:
    - `1`: Easy
    - `2`: Medium
    - `3`: Hard
4. Use the following keys to control the snake:
    - `W`: Move up
    - `A`: Move left
    - `S`: Move down
    - `D`: Move right
5. Avoid colliding with the walls, your tail, or running out of bounds.
6. Collect the food (`#`) to score points and grow your snake.
7. Press `X` to exit the game.

## Game Mechanics

- **Walls**: Represented by `-` (horizontal) and `|` (vertical). Colliding with them ends the game.
- **Snake Head**: Represented by `O`.
- **Snake Tail**: Represented by `o`.
- **Food**: Represented by `#`.
- **Score**: Your score increases by 10 for each food item consumed.

## Prerequisites

To run this game, you need:
- A C++ compiler that supports C++11 or later (e.g., GCC, Clang).
- A terminal to execute the program.

## Compilation and Execution

### Compiling the Program
Use the following command to compile the game:
```bash
g++ -o snake_game main.cpp
```