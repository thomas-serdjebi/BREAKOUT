#include <raylib.h>
#include <iostream>
#include <string>
#include <memory>
#include "grid.h"
#include "piece.h"
#include "Player.h"
#include <fstream>

void SaveBestScore(const std::string& playerName, int score) {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << playerName << "\n" << score << "\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for saving high score." << std::endl;
    }
}

void LoadBestScore(std::string& playerName, int& score) {
    if (std::ifstream file("highscore.txt"); file.is_open()) {
        std::getline(file, playerName);
        file >> score;
        file.close();
    } else {
        std::cerr << "No high score file found. Starting fresh." << std::endl;
        playerName = "Nobody";
        score = 0;
    }
}

int main() {
    bool isGameOver = false;
    bool isPaused = false;  // Variable pour l'état de pause
    const int screenWidth = 800;
    const int screenHeight = 600;
    std::string bestPlayerName = "Nobody";
    int bestScore = 0;
    LoadBestScore(bestPlayerName, bestScore);
    std::cout << bestScore << std::endl;

    InitWindow(screenWidth, screenHeight, "Tetris - C++23");
    SetTargetFPS(60);

    const int cellSize = 30;

    auto grid = std::make_shared<Grid>(20, 10, cellSize);
    auto piece = std::make_unique<Piece>(0, cellSize);

    Player player;
    std::string playerNameInput;
    int selectedLevel = 1;
    bool isPlaying = false;

    // Variables pour le timer et le score
    float dropTimer = 0.0f;
    float dropInterval = 1.0f;
    int score = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!isPlaying && !isGameOver) {
            // --- Menu principal ---
            DrawText("TETRIS", 300, 50, 40, BLACK);
            DrawText("Enter your name:", 200, 150, 20, GRAY);
            DrawText(playerNameInput.c_str(), 400, 150, 20, BLACK);
            DrawText("Select speed (1-10) with UP/DOWN arrows:", 200, 200, 20, GRAY);
            DrawText(TextFormat("%d", selectedLevel), 650, 200, 20, BLACK);
            DrawText("Press ENTER to play", 200, 300, 20, DARKGRAY);

            // Entrée utilisateur
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125 && playerNameInput.length() < 15) {
                    playerNameInput += static_cast<char>(key);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !playerNameInput.empty()) {
                playerNameInput.pop_back();
            }

            // Gérer le niveau
            if (IsKeyPressed(KEY_UP) && selectedLevel < 10) {
                selectedLevel++;
            }
            if (IsKeyPressed(KEY_DOWN) && selectedLevel > 1) {
                selectedLevel--;
            }

            // Démarrer le jeu
            if (IsKeyPressed(KEY_ENTER) && !playerNameInput.empty()) {
                player.SetName(playerNameInput);
                player.SetLevel(selectedLevel);
                dropInterval = 1.1f - (selectedLevel * 0.1f);
                isPlaying = true;
            }
        } else if (isPlaying) {
            // --- Gestion de la pause ---
            if (IsKeyPressed(KEY_SPACE)) {
                isPaused = !isPaused;  // Basculer entre pause et non-pause
            }

            if (isPaused) {
                DrawText("PAUSED", screenWidth / 2 - MeasureText("PAUSED", 40) / 2, screenHeight / 2 - 20, 40, RED);
            } else {
                // --- Jeu en cours ---
                DrawText(TextFormat("Player: %s", player.GetName().c_str()), 500, 10, 20, BLACK);
                DrawText(TextFormat("Level: %d", player.GetLevel()), 500, 40, 20, BLACK);
                DrawText(TextFormat("Score: %d", score), 500, 70, 20, BLACK);

                // Affichage des commandes
                DrawText("Controls:", 500, 120, 20, DARKGRAY);
                DrawText("LEFT: Move Left", 500, 150, 15, GRAY);
                DrawText("RIGHT: Move Right", 500, 180, 15, GRAY);
                DrawText("DOWN: Speed Down", 500, 210, 15, GRAY);
                DrawText("UP: Rotate Piece", 500, 240, 15, GRAY);
                DrawText("SPACE: Pause", 500, 270, 15, GRAY);

                float deltaTime = GetFrameTime();
                dropTimer += deltaTime;

                // Contrôles du joueur
                if (IsKeyPressed(KEY_LEFT) && piece->IsMoveValid(grid->GetCells(), -1, 0)) { piece->Move(-1, 0); }
                if (IsKeyPressed(KEY_RIGHT) && piece->IsMoveValid(grid->GetCells(), 1, 0)) { piece->Move(1, 0); }
                if (IsKeyPressed(KEY_DOWN) && piece->IsMoveValid(grid->GetCells(), 0, 1)) { piece->Move(0, 1); }
                if (IsKeyPressed(KEY_UP)) {
                    piece->Rotate();  // La flèche haut fait tourner la pièce
                    if (!piece->IsMoveValid(grid->GetCells(), 0, 0)) piece->Rotate();  // Revenir à l'état précédent si invalide
                }

                // Déplacement automatique
                if (dropTimer > dropInterval) {
                    if (piece->IsMoveValid(grid->GetCells(), 0, 1)) {
                        piece->Move(0, 1);
                    } else {
                        piece->AnchorToGrid(grid->GetCells());

                        if (grid->IsGameOver()) {
                            isPlaying = false;
                            isGameOver = true;
                        } else {
                            int clearedInCurrentCall = grid->ClearFullLines();
                            if (clearedInCurrentCall > 0) {
                                int basePoints = clearedInCurrentCall * grid->GetCols();
                                int comboBonus = (clearedInCurrentCall - 1) * basePoints;
                                score += basePoints + comboBonus;
                            }
                            piece = std::make_unique<Piece>(rand() % 7, cellSize);
                        }
                    }
                    dropTimer = 0.0f;
                }

                grid->Draw();
                piece->Draw();
            }
        } else if (isGameOver) {

            DrawText("Game Over!", 300, 200, 40, RED);
            DrawText(TextFormat("Your score: %d", score), 300, 250, 20, BLACK);

            if (score > bestScore) {
                bestScore = score;
                bestPlayerName = player.GetName();
                SaveBestScore(bestPlayerName, score);
                DrawText("New High Score!", 300, 300, 20, GREEN);
            } else {
                DrawText(TextFormat("High Score: %d by %s", bestScore, bestPlayerName.c_str()), 300, 300, 20, GRAY);
            }

            DrawText("Press ENTER to return to menu", 300, 400, 20, DARKGRAY);

            if (IsKeyPressed(KEY_ENTER)) {
                grid->Clear();
                score = 0;
                piece = std::make_unique<Piece>(rand() % 7, cellSize);
                isGameOver = false;
                isPlaying = false;
                playerNameInput.clear(); // Réinitialisation pour nouvel utilisateur
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
