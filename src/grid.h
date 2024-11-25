#pragma once

#include <raylib.h>
#include <vector>
#include <optional>

class Grid {
public:
    Grid(int rows, int cols, int cellSize);
    void Draw() const;
    void Clear();
    std::vector<std::vector<std::optional<Color>>> &GetCells();
    [[nodiscard]] const std::vector<std::vector<std::optional<Color>>> &GetCells() const;

    bool IsGameOver() const;

    int ClearFullLines();
    [[nodiscard]] int GetCols() const;
    [[nodiscard]] int GetRows() const;
    [[nodiscard]] int GetLinesCleared() const;

private:
    int rows;
    int cols;
    int cellSize;
    int linesCleared;

    std::vector<std::vector<std::optional<Color>>> cells;

    void DrawCell(int x, int y, Color color) const;


};
