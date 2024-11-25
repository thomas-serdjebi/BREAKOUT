#include "piece.h"
#include <cstdlib>
#include <optional>


Piece::Piece(int type, int gridCellSize)
    : x(4), y(0), cellSize(gridCellSize), shape(GetShapes()[type]) {

    Color pieceColors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK};
    color = pieceColors[type % 7];
}


void Piece::Draw() const {
    for (int row = 0; row < shape.size(); ++row) {
        for (int col = 0; col < shape[row].size(); ++col) {
            if (shape[row][col] == 1) {
                DrawRectangle((x + col) * cellSize, (y + row) * cellSize, cellSize, cellSize, color);
                DrawRectangleLines((x + col) * cellSize, (y + row) * cellSize, cellSize, cellSize, BLACK);
            }
        }
    }
}

// Faire tourner la pièce
void Piece::Rotate() {
    std::vector<std::vector<int>> newShape(shape[0].size(), std::vector<int>(shape.size()));
    for (int row = 0; row < shape.size(); ++row) {
        for (int col = 0; col < shape[row].size(); ++col) {
            newShape[col][shape.size() - row - 1] = shape[row][col];
        }
    }
    shape = newShape;
}

//Faire bouger la pièce
void Piece::Move(int dx, int dy) {
    x += dx;
    y += dy;
}

//Gérer les limites car la pièce ne peux pas dépasser la grille lolilol
bool Piece::IsMoveValid(const std::vector<std::vector<std::optional<Color>>>& grid, int dx, int dy) const
{
    for (int row = 0; row < shape.size(); ++row) {
        for (int col = 0; col < shape[row].size(); ++col) {
            if (shape[row][col] == 1) {
                int newX = x+col +dx;
                int newY = y+row + dy;

                if (newX < 0 || newX >= grid[0].size() || newY >= grid.size() || grid[newY][newX].has_value() ) {
                    return false;
                }
            }

        }

    }

    return true;
}

void Piece::AnchorToGrid(std::vector<std::vector<std::optional<Color>>>& grid) const {
    for (int row = 0; row < shape.size(); ++row) {
        for (int col = 0; col < shape[row].size(); ++col) {
            if (shape[row][col] == 1) {
                int gridX = x + col;
                int gridY = y + row;

                grid[gridY][gridX] = color;
            }
        }
    }
}


std::vector<std::vector<std::vector<int>>> Piece::GetShapes() {
    return {
        // Carré (O)
            {{1, 1},
             {1, 1}},
            // Ligne (I)
            {{1, 1, 1, 1}},
            // T
            {{0, 1, 0},
             {1, 1, 1}},
            // L
            {{1, 0},
             {1, 0},
             {1, 1}},
            // J
            {{0, 1},
             {0, 1},
             {1, 1}},
            // S
            {{0, 1, 1},
             {1, 1, 0}},
            // Z
            {{1, 1, 0},
             {0, 1, 1}}
    };
}
