#pragma once

#include <string>
#include <functional>
#include <raylib.h>

class Button {
public:
    Button(const Rectangle& rect, const std::string& text, std::function<void()> callback);

    void Draw() const;
    void HandleClick(const Vector2& mousePosition);

private:
    Rectangle bounds;
    std::string label;
    std::function<void()> onClick;
};
