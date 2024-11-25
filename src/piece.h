#pragma once

#include <iosfwd>
#include <optional>
#include <vector>
#include <raylib.h>
#include <vector>

class Piece {
public:
    Piece(int type, int gridCellSize); // Constructeur qui initialise la pièce
    void Draw() const;                // Dessiner la pièce
    void Rotate();                    // Rotation de la pièce
    void Move(int dx, int dy);       //bouger la pièce
    bool IsMoveValid(const std::vector<std::vector<std::optional<Color>>> &grid, int dx, int dy) const; //vérifier si ca ne sort pas
    void AnchorToGrid(std::vector<std::vector<std::optional<Color>>> &grid) const; //accrocher la piece a la grille

    std::vector<std::vector<int>> GetShape() const { return shape; }
    int GetX() const { return x; }
    int GetY() const { return y; }



private:
    int x;
    int y;
    int cellSize;
    std::vector<std::vector<int>> shape;
    Color color{};

    static std::vector<std::vector<std::vector<int>>> GetShapes();
};
