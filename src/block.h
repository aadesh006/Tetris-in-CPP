#pragma once
#include <vector>
#include "position.h"
#include <map>
#include <raylib.h>


class Block{
    public:
        Block();
        void Draw(int OffsetX, int OffsetY); // Function to draw the block on the grid
        void Move(int row, int col);
        std::vector<Position> GetCurrentRotation();
        int id;
        std::map<int, std::vector<Position>>cells; // Map of cell positions for each rotation
        std::vector<Position> currentRotation; // Current rotation of the block
        int rotationState; // Current rotation state of the block

    private:
        int cellSize; // Size of each cell in pixels
        std::vector<Color> colors; // Colors for the block
        int row_offset; // Row offset for the block
        int col_offset; // Column offset for the block
};