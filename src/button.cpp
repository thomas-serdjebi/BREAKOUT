#include "Button.h"

Button::Button(const Rectangle& rect, const std::string& text, std::function<void()> callback)
    : bounds(rect), label(text), onClick(callback) {}

void Button::Draw() const {
    DrawRectangleRec(bounds, LIGHTGRAY);
    DrawText(label.c_str(), bounds.x + 10, bounds.y + 10, 20, BLACK);
}

void Button::HandleClick(const Vector2& mousePosition) {
    if (CheckCollisionPointRec(mousePosition, bounds)) {
        if (onClick) {
            onClick();
        }
    }
}
