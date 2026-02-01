#include <raylib.h>
#include "game.h"
#include "color.h"
#include <iostream>

double lastTime = 0;

bool EventTriggered(double interval){

    double currentTime = GetTime(); // Get current time in milliseconds
    if(currentTime-lastTime >= interval) {

        lastTime = currentTime;
        return true;
    }
    return false;
}
int main() 
{
    // Initialize the window
    InitWindow(510, 620, "Tetris Game"); // 500x600 window
    SetTargetFPS(60);
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0); // Load a font for text rendering
    
    Game game = Game(); // Create a Game instance

    while(WindowShouldClose() == false) 
    {
        UpdateMusicStream(game.music);
        BeginDrawing();
        ClearBackground(darkBlue);

        game.HandleInput(); // Handle user input

        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.GameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        }

        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        if (EventTriggered(0.2)) { // Check if 0.1 seconds have passed
                game.MoveBlockDown(); // Move the block down every 0.1 seconds
                game.grid.PrintGrid(); // Print the grid to the console for debugging
            }

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        
        game.IsCellOutOfBounds(); // Check if the current block is out of bounds
        game.Draw(); // Draw the game state

        EndDrawing();
    }

    CloseWindow();  
}