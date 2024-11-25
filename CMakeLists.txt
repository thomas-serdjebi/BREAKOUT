cmake_minimum_required(VERSION 3.15)
project(TETRIS)

# Activer C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Définir les chemins pour Raylib
set(RAYLIB_INCLUDE_DIR "C:/raylib/w64devkit/include")
set(RAYLIB_LIB_DIR "C:/raylib/w64devkit/lib")

# Trouver les fichiers sources
file(GLOB SOURCES src/*.cpp)

# Ajouter les fichiers sources et inclure Raylib
add_executable(TETRIS ${SOURCES}
        src/grid.h
        src/grid.cpp
        src/piece.h
        src/piece.cpp
        src/player.h
        src/player.cpp
        src/button.h
        src/button.cpp
        src/menu.h
        src/menu.cpp)
target_include_directories(TETRIS PRIVATE ${RAYLIB_INCLUDE_DIR})
target_link_directories(TETRIS PRIVATE ${RAYLIB_LIB_DIR})
target_link_libraries(TETRIS raylib opengl32 gdi32 winmm)
