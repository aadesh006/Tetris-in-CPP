#include "grid.h"
#include <iostream>
#include "color.h" // Include the color header file for color definitions

Grid::Grid(){
    rows = 20; // Number of rows in the grid
    cols = 10; // Number of columns in the grid
    cellSize = 30; // Size of each cell in pixels
    Initialize(); // Call the initialization function to set up the grid
    colors = GetColors(); // Get the colors for the grid cells

}

void Grid::Initialize() {
    // Initialize the grid with zeros
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0; // Empty cell
        }
    }
}

void Grid::PrintGrid() {
    // Print the grid to the console for debugging
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << grid[i][j] << " "; // Print each cell value
        }
        std::cout << std::endl; // New line after each row
    }
}

void Grid::DrawGrid() {
    // Draw the grid on the screen
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int cellValue = grid[i][j]; // Get the value of the cell
            DrawRectangle(j * cellSize+11, i * cellSize+11, cellSize-1, cellSize-1, colors[cellValue]); // Draw the cell
        }
    }
}

bool Grid::IsCellOutOfBounds(int x, int y)
{
    if(x >=0 && x<rows && y>=0 && y<cols)
    {
        return false; // Cell is within bounds
    }
    return true; // Cell is out of bounds
}

bool Grid::IsCellEmpty(int x, int y){
    if(grid[x][y] == 0) // Check if the cell is empty
    {
        return true; // Cell is empty
    }
    return false; // Cell is not empty
}

int Grid::ClearFullRows()
{
    int clearedRows = 0; // Counter for cleared rows
    for(int row = rows - 1; row >= 0; row--) { // Start from the bottom row
        if(IsRowFull(row)) { // Check if the row is full
            ClearRow(row); // Clear the full row
            ShiftRowsDown(row, rows); // Shift all rows above down
            clearedRows++; // Increment the cleared rows counter
        }
    }
    return clearedRows; // Return the number of cleared rows
}

bool Grid::IsRowFull(int row)
{
    for(int col = 0; col < cols; col++) {
        if(grid[row][col] == 0) // Check if any cell in the row is empty
        {
            return false; // Row is not full
        }
    }
    return true; // Row is full
}

void Grid::ClearRow(int row)
{
    for(int col = 0; col < cols; col++) {
        grid[row][col] = 0; // Clear the row by setting all cells to zero
    }
}

void Grid::ShiftRowsDown(int row, int rows)
{
    // Shift rows down starting from the specified row
    for(int i = row; i > 0; i--) {
        for(int j = 0; j < cols; j++) {
            grid[i][j] = grid[i-1][j]; // Move the row down
        }
    }
}
