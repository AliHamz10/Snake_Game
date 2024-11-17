// Including necessary libraries
#include <termios.h> // For terminal I/O
#include <iostream>
#include <unistd.h> // For terminal I/O

using namespace std;

// Defining Global Variables

// height and width of the grid
constexpr int height = 20;
constexpr int width = 20;

// Snake head coordinates (x-axis, y-axis)
int x,y;
// Food coordinates
int foodX, foodY;
// variable to store the score of the player
int score;
// array to store the coordinates of snakes tail (x-axis, y-axis)
int tailX[100], tailY[100];
// variable to store the length of the snake's __disable_tail_calls
int snakeTailLength;
// variable to store the direction of the snake
enum snakesDirection {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
snakesDirection direction;
// boolean variable for checking if the game is over or not
bool gameOver;

// Initializing the game
void GameInIt() {
    gameOver = false;
    direction = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

// Function for drawing the game grid
void GameRender(string playerName) {
    system ("clear");

    // Creating the top walls with '-' character
    for (int i = 0; i < width + 2; i++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            // Creating side walls with '|' character
            if (j == 0 or j == width) {
                cout << "|";
            }
            // Creating snakes head with '0'
            if (i == y and j == x) {
                cout << "0";
            }
            // Creating food with "#'
            else if (i == foodY and j == foodX) {
                cout << "#";
            }
            // Creating snake's head with 'o'
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLength; k++) {
                    if (tailX[k] == j and tailY[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }
    // Creating bottom walls with '-' character
    for (int i = 0; i < width + 2; i++) {
        cout << "-";
    }
    // Displaying player's score
    cout << playerName << "'s Score: " << score << endl;
}
