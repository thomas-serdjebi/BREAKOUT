#include "Player.h"

Player::Player() : name(""), level(1) {}

void Player::SetName(const std::string& playerName) {
    name = playerName;
}

void Player::SetLevel(int selectedLevel) {
    level = selectedLevel;
}

std::string Player::GetName() const {
    return name;
}

int Player::GetLevel() const {
    return level;
}
