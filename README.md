# Tic-Tac-Toe with SFML

This project is a Tic-Tac-Toe game built using the [SFML](https://www.sfml-dev.org/) library.

## Features
- Visually appealing design using SFML
- Supports two-player mode (Player vs Player)
- Clean and structured code

## Prerequisites
To run this project, you need the following:

- **C++ Compiler** (e.g., g++, clang++)
- [SFML 2.5.1](https://www.sfml-dev.org/download.php) library

## How to Run

### 1. Clone the Repository
First, clone the repository:
```bash
git clone https://github.com/RezaGooner/Tic-Tac-Toe-SFML.git
cd Tic-Tac-Toe-SFML
```

### 2. Compile the Project
If SFML is installed on your system, you can compile the code as follows:
```bash
g++ -o TicTacToe main.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

### 3. Run the Game
After compiling, run the game with the following command:
```bash
./TicTacToe
```

## Project Structure

Tic-Tac-Toe-SFML

  ├── main.cpp             # Contains the main game logic
  
  ├── CMakeLists.txt       # Define path of SFML library and linkers
  
  ├── assets/              # Directory for game assets 
  
  │   ├── arial.ttf        # Default font
  
  ├── include/             # Header files 
  
  │   ├── config.h         # Define constant values ​​and settings
  
  └── cmake-build-debug/   # Directory for compiled binaries and necessary DLLs
  
      ├── ...
  
