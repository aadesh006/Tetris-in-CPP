#include "game.h"
#include<random>

Game::Game()
{
    grid = Grid(); // Initialize the grid
    blocks = GetAllBlocks(); // Initialize the blocks
    currentBlock = GetRandomBlock(); // Get a random block to start
    nextBlock = GetRandomBlock(); // Get the next block
    GameOver = false; // Initialize game over state
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
}

Game::~Game(){
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty()) // Check if the blocks vector is empty
    {
        blocks = GetAllBlocks(); // If empty, get all blocks again
        if (blocks.empty()) {
            // Handle the case where GetAllBlocks() also returns empty
            return Block(); // Return a default Block (ensure Block has a default constructor)
        }
    }
    int rndIndex = rand() % blocks.size(); // Generate a random index
    Block block = blocks[rndIndex]; // Get the block at the random index

    blocks.erase(blocks.begin()+rndIndex); // Remove the block from the vector
    return block; // Return the random block
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()}; // Return the vector of blocks
}

void Game::Draw()
{
    grid.DrawGrid(); // Draw the grid
    currentBlock.Draw(11,11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::HandleInput()
{
    if(GameOver ==true && IsKeyPressed(KEY_ENTER)){
        GameOver = false; // Reset game over state if Enter is pressed
        ResetGame(); // Reset the game state
    }
    // Handle user input for moving and rotating the current block
    if (IsKeyPressed(KEY_LEFT)) {
        if(!GameOver){
        currentBlock.Move(0, -1); // Move left

        if(IsCellOutOfBounds() || BlockFits() == false) {
            currentBlock.Move(0, 1); // If out of bounds, move back to the right
        }
    }
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        if(!GameOver){
        currentBlock.Move(0, 1); // Move right

        if(IsCellOutOfBounds() || BlockFits() == false) {
            currentBlock.Move(0, -1); // If out of bounds, move back to the left
        }
    }
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        if(!GameOver){
        currentBlock.Move(1, 0); // Move down
        UpdateScore(0,1);

        if(IsCellOutOfBounds()) {
            currentBlock.Move(-1, 0); // If out of bounds, move back up
        }
    }
    }
    else if (IsKeyPressed(KEY_UP)) {
        if(!GameOver){
        currentBlock.currentRotation = currentBlock.GetCurrentRotation(); // Get the current rotation of the block
        currentBlock.rotationState = (currentBlock.rotationState + 1) % 4; // Rotate the block

        if(IsCellOutOfBounds() || BlockFits() ) {
            currentBlock.rotationState = (currentBlock.rotationState - 1 + 4) % 4; // If out of bounds, revert rotation
            currentBlock.currentRotation = currentBlock.GetCurrentRotation(); // Update the current rotation
        }
    }
    }

    else if (IsKeyPressed(KEY_SPACE)) {
        if(!GameOver){
        // Handle dropping the block immediately to the bottom
        while (!IsCellOutOfBounds()) {
            currentBlock.Move(1, 0); // Move down until out of bounds
        }
        currentBlock.Move(-1, 0); // Move back up to the last valid position
    }
}

    else if(IsKeyPressed(KEY_ESCAPE)){
        CloseWindow(); // Close the window if Escape is pressed 
    }
    // No return needed for void function, but ensure all branches are covered
}

void Game::MoveBlockDown()
{
    if(!GameOver){
    currentBlock.Move(1, 0); // Move the block down
    if(IsCellOutOfBounds() || !BlockFits()){ // Check if the block is out of bounds or does not fit{
            currentBlock.Move(-1, 0); // If out of bounds, move back up
            LockBlock();
        }
    }
}

bool Game::IsCellOutOfBounds()
{
    std::vector<Position> tiles = currentBlock.GetCurrentRotation(); // Get the current rotation of the block
    for(Position item: tiles)
    {
        if (grid.IsCellOutOfBounds(item.row, item.col))
        {
            return true;
        }
    }
    return false;
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCurrentRotation();
    for(Position item: tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id; // Lock the block in the grid
    }
    currentBlock = nextBlock; // Set the current block to the next block
    if(BlockFits() == false) // Check if the new block fits
    {
        GameOver = true; // If it doesn't fit, set game over
    }
    nextBlock = GetRandomBlock(); // Get a new random block for the next turn
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        //PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }

}

void Game::ResetGame()
{
    grid.Initialize();
    blocks = GetAllBlocks(); // Reinitialize the blocks
    currentBlock = GetRandomBlock(); // Get a random block to start
    nextBlock = GetRandomBlock(); // Get the next block 
    score = 0;
}

void Game::UpdateScore(int LinesCleared, int MovedDownPoints)
{
    switch (LinesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += MovedDownPoints;
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCurrentRotation(); // Get the current rotation of the block
    for(Position item: tiles)
    {
        if (grid.IsCellOutOfBounds(item.row, item.col) || !grid.IsCellEmpty(item.row, item.col))
        {
            return false; // If any tile is out of bounds or not empty, the block does not fit
        }
    }
    return true; // The block fits in the grid
}