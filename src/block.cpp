#include "block.h"
#include "position.h"
#include "color.h" // Include the color header file for color definitions

Block::Block(){
    rotationState = 0;
    cellSize = 30;
    colors = GetColors(); // Get the colors for the block
    row_offset = 0; // Initialize row offset
    col_offset = 0; // Initialize column offset
}

void Block::Draw(int OffsetX, int OffsetY){
    std::vector<Position> tiles = GetCurrentRotation(); // Get the current rotation of the block
    for(Position item: tiles){
        DrawRectangle(item.col * cellSize+OffsetX, item.row * cellSize+OffsetY, cellSize - 1, cellSize - 1, colors[id]); // Draw the block
    }
}

void Block::Move(int row, int col) {
    row_offset += row;
    col_offset += col;
}

std::vector<Position> Block::GetCurrentRotation() {
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position item: tiles){
        Position NewPos = Position(item.row + row_offset, item.col + col_offset);
        movedTiles.push_back(NewPos); // Adjust the position based on the offsets
    }
    return movedTiles;
}