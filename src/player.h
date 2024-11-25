#pragma once
#include <string>

class Player {
private:
    std::string name;
    int level;

public:
    Player();
    void SetName(const std::string& playerName);
    void SetLevel(int selectedLevel);
    std::string GetName() const;
    int GetLevel() const;
};
