#include "menu.h"
#include <string>
#include <cstring>

bool Menu::DisplayAndHandleInput(std::string& playerName, int& level) {
    static char nameBuffer[16] = ""; // Pour le pseudo
    static int selectedLevel = 1;

    BeginDrawing();
    ClearBackground(RAYWHITE);


    DrawText("TETRIS", screenWidth / 2 - MeasureText("TETRIS", 40) / 2, 50, 40, DARKGRAY);

    DrawText("Enter your name:", screenWidth / 2 - 100, 150, 20, DARKGRAY);
    DrawText(nameBuffer, screenWidth / 2 - MeasureText(nameBuffer, 20) / 2, 180, 20, BLACK);

    int key = GetKeyPressed();
    if (key >= 32 && key <= 125 && strlen(nameBuffer) < 15) {
        char c = (char)key;
        strncat(nameBuffer, &c, 1);
    }
    if (IsKeyPressed(KEY_BACKSPACE) && strlen(nameBuffer) > 0) {
        nameBuffer[strlen(nameBuffer) - 1] = '\0';
    }


    DrawText("Select Level (1-10):", screenWidth / 2 - 100, 250, 20, DARKGRAY);
    DrawText(TextFormat("%d", selectedLevel), screenWidth / 2, 280, 20, BLACK);
    if (IsKeyPressed(KEY_UP) && selectedLevel < 10) selectedLevel++;
    if (IsKeyPressed(KEY_DOWN) && selectedLevel > 1) selectedLevel--;


    DrawText("Press ENTER to Play", screenWidth / 2 - MeasureText("Press ENTER to Play", 20) / 2, 350, 20, GREEN);
    if (IsKeyPressed(KEY_ENTER) && strlen(nameBuffer) > 0) {
        playerName = nameBuffer;
        level = selectedLevel;
        startGame = true;
    }

    EndDrawing();

    return startGame;
}

void Menu::DisplayGameInfo(int score) const {
    DrawText("Controls:", screenWidth - 150, 50, 20, DARKGRAY);
    DrawText("Arrow Left/Right: Move", screenWidth - 150, 80, 15, BLACK);
    DrawText("Arrow Down: Drop", screenWidth - 150, 100, 15, BLACK);
    DrawText("Space: Rotate", screenWidth - 150, 120, 15, BLACK);
    DrawText(TextFormat("Score: %d", score), screenWidth - 150, 180, 20, DARKGRAY);
}
