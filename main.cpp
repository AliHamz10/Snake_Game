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

// Function for updating the game status
void GameUpdate() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < snakeTailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (direction) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    // Checks for snake's collision with the walls (|)
    if (x >= width or x < 0 or y >= height or y < 0) {
        gameOver = true;
    }
    // Checks for snake's collision with the tail
    for (int i = 0; i < snakeTailLength; i++) {
        if (tailX[i] == x and tailY[i] == y) {
            gameOver = true;
        }
    }
    // Checks for snake's collision with the food
    if (x == foodX and y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        snakeTailLength++;
    }
}

// Function to set the game difficulty
int SetDifficulty() {
    int difficulty = 0, choice;
    cout << "Choose the difficulty level: " << endl << "1. Easy" << endl << "2. Medium" << endl << "3. Hard" << endl << "Note: Default difficulty level is Medium" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            difficulty = 1000;
            break;
        case 2:
            difficulty = 500;
            break;
        case 3:
            difficulty = 100;
            break;
    }
    return difficulty;
}

// Function to check if a key is pressed (non-blocking)
bool kbhit() {
    struct termios oldt, newt;
    int ch;
    bool ch_available = false;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply the new settings

    ch = getchar();  // Read a character
    if (ch != EOF) {
        ch_available = true;
    }

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch_available;
}

// Function to handle user input
void UserInput() {
    // Checks if a key is pressed or not
    if (kbhit()) {
        // Getting the pressed key
        char ch = getchar();  // Capture the key pressed
        switch (ch) {
            case 'a':
                direction = LEFT;
            break;
            case 'd':
                direction = RIGHT;
            break;
            case 'w':
                direction = UP;
            break;
            case 's':
                direction = DOWN;
            break;
            case 'x':
                gameOver = true;
            break;
        }
    }
}
