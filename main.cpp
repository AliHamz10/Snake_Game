#include <iostream>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>

using namespace std;

// Defining Global Variables
const int height = 20;
const int width = 20;

int x, y;                // Snake head coordinates
int foodX, foodY;        // Food coordinates
int score;               // Player's score
int tailX[100], tailY[100]; // Snake's tail coordinates
int snakeTailLength;     // Length of the snake

enum snakesDirection {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

snakesDirection direction;
bool gameOver;

// Function to initialize the game
void GameInIt() {
    gameOver = false;
    direction = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
    snakeTailLength = 0;
}

// Function to render the game
void GameRender(const string& playerName) {
    cout << "\033[2J\033[1;1H"; // Clear screen and reset cursor position

    // Top wall
    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    // Game area
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (j == 0 || j == width + 1) {
                cout << "|"; // Walls
            } else if (i == y && j == x) {
                cout << "O"; // Snake head
            } else if (i == foodY && j == foodX) {
                cout << "#"; // Food
            } else {
                bool isTail = false;
                for (int k = 0; k < snakeTailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        isTail = true;
                    }
                }
                if (!isTail) cout << " "; // Empty space
            }
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    // Display score
    cout << playerName << "'s Score: " << score << endl;
}

// Function to update the game state
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
        case STOP:
            // Do nothing for STOP
                break;
        default:
            break; // Optional: handle unexpected values
    }

    // Check collision with walls
    if (x < 0 || x >= width || y < 0 || y >= height) gameOver = true;

    // Check collision with tail
    for (int i = 0; i < snakeTailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // Check collision with food
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        snakeTailLength++;
    }
}

// Function to handle user input
void UserInput() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        switch (ch) {
            case 'a': direction = LEFT; break;
            case 'd': direction = RIGHT; break;
            case 'w': direction = UP; break;
            case 's': direction = DOWN; break;
            case 'x': gameOver = true; break; // Exit game
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

// Function to set game difficulty
int SetDifficulty() {
    int difficulty = 500; // Default to medium
    int choice;

    cout << "Choose difficulty level:\n1. Easy\n2. Medium\n3. Hard\n";
    cin >> choice;

    switch (choice) {
        case 1: difficulty = 1000; break;
        case 2: difficulty = 500; break;
        case 3: difficulty = 100; break;
        default: cout << "Invalid choice, defaulting to Medium.\n";
    }

    return difficulty;
}

// Main function
int main() {
    srand(time(0)); // Seed random number generator

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int difficulty = SetDifficulty();

    GameInIt();

    while (!gameOver) {
        GameRender(playerName);
        UserInput();
        GameUpdate();
        usleep(difficulty * 1000); // Delay based on difficulty
    }

    cout << "Game Over! Final Score: " << score << endl;

    return 0;
}