# Snake Game

## Introduction

The snake game is to control a snake as it moves around the board, eating food pellets and growing longer with each piece consumed. The goal is to avoid collisions with the snake's own body while trying to consume as much food as possible. The snake can only move forward, turn left and turn right. The game continues until the snake collides with itself, ending the game.

This implementation of the snake game is designed to be cross-platform and can run on both Unix-like systems (such as Linux and macOS) and Windows. You can play the game directly from your terminal or command prompt.

## Getting Started

To get started with the Snake Game, follow these steps:

### Prerequisites

- **C++ Compiler:** Ensure you have a C++ compiler installed (such as `g++` on Unix-like systems or Visual Studio on Windows).
- **Terminal/Command Prompt:** You will need to run the game in a terminal (Unix-like systems) or command prompt (Windows).

### Building the Game

1. **Clone the Repository:**

   Clone this repository to your local machine using:
   ```
   git clone <repository_url>
   ```
1. **Compile the Code:**

   Navigate to the directory containing snake_game.cpp and compile the code using:

   ```
   g++ -o snake_game snake_game.cpp
   ```
1. **Run the Game:**

   After compiling, you can run the game by executing:

   ```
   ./snake_game   # On Unix-like systems
   ```
   ```
   snake_game.exe # On Windows
   ```
## How to Play

### Controls

Use the following arrow keys to control the snake's direction:

- **Up Arrow Key:** Moves the snake up.
- **Down Arrow Key:** Moves the snake down.
- **Left Arrow Key:** Moves the snake left.
- **Right Arrow Key:** Moves the snake right.

### Movement Rules

- **No Backward Movement:** The snake cannot reverse direction. If you press the arrow key that would make the snake move directly backward, the snake will continue to move in the current direction.

## Gameplay Video

Watch the gameplay video to see how the game is played:

![Gameplay Video](https://github.com/Yinysgithub/snake_game/snake_game_example)
