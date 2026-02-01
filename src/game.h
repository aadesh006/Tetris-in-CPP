#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
    public:
        Game();
        ~Game();
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        void Draw(); // Function to draw the game state
        Grid grid;
        void HandleInput(); // Function to handle user input
        void MoveBlockDown(); // Function to move the block down
        bool IsCellOutOfBounds(); // Function to check if the current block is out of bounds
        bool GameOver; // Function to check if the game is over
        int score;
        Music music;
        

    private:
        void ResetGame(); // Function to reset the game state
        void UpdateScore(int LinesCleared, int MovedDownPoints);
        Block nextBlock;
        Block currentBlock; // Current block being played
        std::vector<Block> blocks;// Vector to hold all available blocks
        bool BlockFits();
        void LockBlock(); // Function to lock the current block in place and generate a new one
        Sound rotate;
        Sound clear;
};