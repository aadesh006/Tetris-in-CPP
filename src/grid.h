#pragma once
#include<vector>
#include<raylib.h>
#include "color.h" // Include the color header file for color definitions

class Grid{
    public:
        Grid();
        int grid[20][10];
        void Initialize();
        void PrintGrid();
        void DrawGrid();
        bool IsCellOutOfBounds(int x, int y);
        bool IsCellEmpty(int x, int y);
        int ClearFullRows();

    private:
        bool IsRowFull(int row);
        void ClearRow(int row);
        void ShiftRowsDown(int row, int rows);
        int cols;
        int rows;
        int cellSize;
        std::vector<Color> colors;
};