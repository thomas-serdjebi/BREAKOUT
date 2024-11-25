#include "grid.h"

#include <iostream>
#include <ostream>

Grid::Grid(int rows, int cols, int cellSize)
    : rows(rows), cols(cols), cellSize(cellSize), cells(rows, std::vector<std::optional<Color>>(cols, std::nullopt)), linesCleared(0)  {}

void Grid::Draw() const {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Color cellColor = cells[row][col].has_value() ? cells[row][col].value() : DARKGRAY;
            DrawCell(col * cellSize, row * cellSize, cellColor);
        }
    }
}

void Grid::Clear() {
    for (auto& row : cells) {
        std::fill(row.begin(), row.end(), std::nullopt);
    }
}

void Grid::DrawCell(int x, int y, Color color) const {
    DrawRectangle(x, y, cellSize, cellSize, color);
    DrawRectangleLines(x, y, cellSize, cellSize, BLACK);
}

int Grid::ClearFullLines() {
    int linesCleared = 0;

    for (int row = rows - 1; row >= 0; --row) {
        bool isFull = true;

        for (int col = 0; col < cols; ++col) {
            if (!cells[row][col].has_value()) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            for (int moveRow = row; moveRow > 0; --moveRow) {
                cells[moveRow] = cells[moveRow - 1];
            }
            cells[0] = std::vector<std::optional<Color>>(cols, std::nullopt);
            ++linesCleared;
            row++;
        }
    }

    return linesCleared;
}


int Grid::GetCols() const {
    return cols;
}

int Grid::GetRows() const {
    return rows;
}

int Grid::GetLinesCleared() const {
    return linesCleared;
}

std::vector<std::vector<std::optional<Color>>> &Grid::GetCells() {
    return cells;
}

const std::vector<std::vector<std::optional<Color>>> &Grid::GetCells() const {
    return cells;
}

bool Grid::IsGameOver() const {
    for (int col= 0 ; col < cols ; ++col) {
        if (cells[0][col].has_value()) {
            return true;
        }
    }
    return false;
}
