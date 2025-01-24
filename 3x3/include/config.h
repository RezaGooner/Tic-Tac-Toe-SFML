#ifndef CONFIG_H
#define CONFIG_H

// Window and grid settings
#define WINDOW_WIDTH   600
#define WINDOW_HEIGHT  600
#define DIALOG_WIDTH   400
#define DIALOG_HEIGHT  200
#define GRID_SIZE      3
#define CELL_SIZE      (WINDOW_WIDTH / GRID_SIZE)

#define FONT_PATH      "C:/Windows/Fonts/arial.ttf"
#define DRAW_MESSAGE   "It's a draw!"
#define WIN_MESSAGE    " wins!"
#define RESTART_TEXT   "Press R to restart or Close to exit."
#define GAME_OVER_TITLE "Game Over"
#define FAILED_FONT_MSG "Failed to load font!"

#define QUIT_GAME_KEY    sf::Keyboard::Q
#define RESTART_GAME_KEY sf::Keyboard::R

#define PLAYER1_MARK "X"
#define PLAYER2_MARK "O"

#endif // CONFIG_H
