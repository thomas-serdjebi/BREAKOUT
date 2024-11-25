#pragma once
#include <raylib.h>
#include <string>

class Menu {
private:
    int screenWidth;
    int screenHeight;
    bool startGame;

public:
    Menu(int width, int height) : screenWidth(width), screenHeight(height), startGame(false) {}

    bool DisplayAndHandleInput(std::string& playerName, int& level);

    void DisplayGameInfo(int score) const;
};
