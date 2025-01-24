#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"  // Include the configuration file

// Player enum to represent the state of each cell
enum class Player { None, X, O };

class TicTacToe {
public:
    TicTacToe() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_OVER_TITLE) {
        reset();
    }

    void run() {
        while (window.isOpen()) {
            handle_Events();
            render();
        }
    }

private:
    sf::RenderWindow window;  // Main game window
    Player grid[GRID_SIZE][GRID_SIZE];  // Game grid
    Player currentPlayer = Player::X;  // Current player (X or O)
    bool gameOver = false;  // Flag to check if the game is over

    // Reset the game grid and state
    void reset() {
        //initialize
        for (int i = 0; i < GRID_SIZE; ++i)
            for (int j = 0; j < GRID_SIZE; ++j)
                grid[i][j] = Player::None;  // Clear all cells

        currentPlayer = Player::X;  // Start with player X
        gameOver = false;  // Reset game over flag
    }

    // Handle user input events
    void handle_Events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed or event.key.code == QUIT_GAME_KEY)
                window.close();  // Close the window if the close button is clicked

            // Handle mouse clicks
            if (!gameOver && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x / CELL_SIZE;  // Calculate grid column
                    int y = event.mouseButton.y / CELL_SIZE;  // Calculate grid row

                    // Check if the clicked cell is valid and empty
                    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == Player::None) {
                        // Place the current player's mark
                        grid[x][y] = currentPlayer;

                        // Redraw the grid to show the latest move
                        render();

                        // Check if the current player has won
                        checkWin();

                        // If the game is not over, switch to the next player
                        if (!gameOver)
                            currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;  // Fix: Correct player switch
                    }
                }
            }

            // Handle keyboard input (reset the game when 'R' is pressed)
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::R)
                    reset();
        }
    }

    // Check if the current player has won
    void checkWin() {
        // Check rows for a win
        for (int i = 0; i < GRID_SIZE; ++i)
            if (grid[i][0] != Player::None && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
                gameOver = true;
                return;
            }

        // Check columns for a win
        for (int j = 0; j < GRID_SIZE; ++j)
            if (grid[0][j] != Player::None && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
                gameOver = true;
                return;
            }

        // Check main diagonal (\) for a win
        if (grid[0][0] != Player::None && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
            gameOver = true;
            return;
        }

        // Check secondary-diagonal (/) for a win
        if (grid[0][2] != Player::None && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
            gameOver = true;
            return;
        }

        // Check for a draw (no empty cells left)
        bool isDraw = true;
        for (int i = 0; i < GRID_SIZE; ++i)
            for (int j = 0; j < GRID_SIZE; ++j)
                if (grid[i][j] == Player::None) {
                    isDraw = false;
                    break;
                }

        if (isDraw)
            gameOver = true;
    }

    // Render the game grid and player marks
    void render() {
        window.clear(sf::Color::White);

        // Draw grid lines
        sf::RectangleShape line(sf::Vector2f(WINDOW_WIDTH, 5));
        line.setFillColor(sf::Color::Black);
        for (int i = 1; i < GRID_SIZE; ++i) {
            line.setPosition(0, i * CELL_SIZE);
            window.draw(line);
            line.setPosition(i * CELL_SIZE, 0);
            line.setRotation(90);
            window.draw(line);
            line.setRotation(0);
        }

        // Draw X and O marks
        sf::Font font;
        if (!font.loadFromFile(FONT_PATH)) {  // Load the font
            std::cerr << FAILED_FONT_MSG << std::endl;
            return;
        }

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(100);

        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (grid[i][j] == Player::X) {
                    text.setString(PLAYER1_MARK);
                    text.setFillColor(sf::Color::Black);  // Player X: Black
                    text.setPosition(i * CELL_SIZE + 50, j * CELL_SIZE + 30);
                    window.draw(text);
                } else if (grid[i][j] == Player::O) {
                    text.setString(PLAYER2_MARK);
                    text.setFillColor(sf::Color::Red);  // Player O: Red
                    text.setPosition(i * CELL_SIZE + 50, j * CELL_SIZE + 30);
                    window.draw(text);
                }
            }
        }

        // Show game over message if the game is over
        if (gameOver)
            showGameOverDialog();

        window.display();
    }

    // Display a dialog when the game is over
    void showGameOverDialog() {
        sf::RenderWindow dialog(sf::VideoMode(DIALOG_WIDTH, DIALOG_HEIGHT), GAME_OVER_TITLE, sf::Style::Titlebar | sf::Style::Close);
        sf::Font font;
        if (!font.loadFromFile(FONT_PATH)) {
            std::cerr << FAILED_FONT_MSG << std::endl;
            return;
        }

        sf::Text message;
        message.setFont(font);
        message.setCharacterSize(30);
        message.setFillColor(sf::Color::Black);

        bool isDraw = true;
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (grid[i][j] == Player::None) {
                    isDraw = false;
                    break;
                }
            }
        }

        if (isDraw) {
            message.setString(DRAW_MESSAGE);
        } else {
            message.setString((currentPlayer == Player::O ? PLAYER2_MARK : PLAYER1_MARK) + std::string(WIN_MESSAGE));
        }

        message.setPosition(50, 50);

        sf::Text restartText;
        restartText.setFont(font);
        restartText.setCharacterSize(20);
        restartText.setFillColor(sf::Color::Black);
        restartText.setString(RESTART_TEXT);
        restartText.setPosition(50, 120);

        while (dialog.isOpen()) {
            sf::Event event;
            while (dialog.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    dialog.close();
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::R) {
                        dialog.close();
                        reset();
                    }
                }
            }

            dialog.clear(sf::Color::White);
            dialog.draw(message);
            dialog.draw(restartText);
            dialog.display();
        }
    }
};

int main() {
    // Run the game
    TicTacToe game;
    game.run();
    return 0;
}
