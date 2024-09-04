#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <conio.h>    // For Windows-specific keyboard input
#include <windows.h> // For Windows-specific system calls
#else
#include <unistd.h>   // For Unix-specific system calls
#include <termios.h>  // For Unix-specific terminal settings
#endif

using namespace std;

// Enumeration for the possible movement directions of the snake
enum Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame {
private:
    // Dimension of the 2D board
    int width, height;
    vector<vector<char>> board;
    // Snake positions, including head and body
    vector<pair<int, int>> snake; 
    // Food pellet position
    pair<int, int> food;
    Direction dir;

    // Place food randomly on the board without colliding with the snake
    void placeFood() {
        while (true) {
            int x = rand() % width;
            int y = rand() % height;
            bool occupied = false;
            // Check if the randomly chosen position is occupied by the snake
            for (const auto& s : snake) {
                if (s.first == x && s.second == y) {
                    occupied = true;
                    break;
                }
            }
            if (!occupied) {
                food = { x, y };
                break;
            }
        }
    }

    // Update the game board with the current state of the snake and food
    void updateBoard() {
        // Clear the board
        for (int y = 0; y < height; ++y) {
            fill(board[y].begin(), board[y].end(), '.');
        }
        // Place the food
        board[food.second][food.first] = '@';
        // Place the snake
        for (size_t i = 0; i < snake.size(); ++i) {
            board[snake[i].second][snake[i].first] = (i == 0) ? 'o' : 'x'; // Head and body
        }
    }

    // Print the current state of the game board
    void printBoard() const {
#ifdef _WIN32
        system("cls"); // Clear the screen on Windows
#else
        // Clear the screen on Unix-like systems (using ANSI escape codes)
        cout << "\033[2J\033[1;1H"; // Clear screen and move cursor to top-left
#endif
        for (const auto& row : board) {
            for (char cell : row) {
                cout << cell;
            }
            cout << endl;
        }
    }

    // Move the snake based on its current direction
    void moveSnake() {
        // Calculate new head position
        pair<int, int> head = snake.front();
        switch (dir) {
            case UP: head.second = (head.second - 1 + height) % height; break;
            case DOWN: head.second = (head.second + 1) % height; break;
            case LEFT: head.first = (head.first - 1 + width) % width; break;
            case RIGHT: head.first = (head.first + 1) % width; break;
        }

        // Check for collision with itself
        if (find(snake.begin() + 1, snake.end(), head) != snake.end()) {
            throw runtime_error("Game Over: Snake collided with itself!");
        }

        // Add new head to the snake
        snake.insert(snake.begin(), head);

        // Check if food is eaten
        if (head == food) {
            placeFood(); // Place new food
        } else {
            snake.pop_back(); // Remove the tail if no food is eaten
        }
    }

public:
    // Constructor to initialize the game with a given board size
    SnakeGame(int w, int h) : width(w), height(h), dir(RIGHT) {
        board.resize(height, vector<char>(width, '.'));

        // Initialize the snake with size 3 (1 head and 2 body segments) in the middle of the board
        int startX = w / 2 - 1;
        int startY = h / 2;
        snake = { {startX + 2, startY}, {startX + 1, startY}, {startX, startY} }; // Head and body

        // Place food
        placeFood();
        updateBoard();
        printBoard();
    }

    // Change the direction of the snake
    void setDirection(Direction newDir) {
        // Prevent the snake from reversing direction
        if ((dir == UP && newDir != DOWN) ||
            (dir == DOWN && newDir != UP) ||
            (dir == LEFT && newDir != RIGHT) ||
            (dir == RIGHT && newDir != LEFT)) {
            dir = newDir;
        }
    }

    // Advance the game by one step
    void step() {
        moveSnake();
        updateBoard();
        printBoard();
    }
};

// Function to capture keyboard input
char getch() {
#ifdef _WIN32
    return _getch(); // Windows-specific getch()
#else
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON; // Disable canonical mode
    old.c_lflag &= ~ECHO;   // Disable echoing of input
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON; // Restore canonical mode
    old.c_lflag |= ECHO;   // Restore echoing of input
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
#endif
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Initialize an 8x8 game board
    SnakeGame game(8, 8);

    while (true) {
        // Get user input
        char input = getch();

        switch (input) {
            case 'A': // Up arrow key
                game.setDirection(UP);
                break;
            case 'B': // Down arrow key
                game.setDirection(DOWN);
                break;
            case 'C': // Right arrow key
                game.setDirection(RIGHT);
                break;
            case 'D': // Left arrow key
                game.setDirection(LEFT);
                break;
            default:
                continue;
        }

        try {
            game.step();
        } catch (const exception& e) {
            // End the game on collision
            cout << e.what() << endl;
            break; 
        }
    }

    return 0;
}
