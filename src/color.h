#pragma once
#include <raylib.h>
#include <vector>

extern const Color darkGrey; // Empty cell color (black)
extern const Color red; // Red
extern const Color green; // Green
extern const Color blue; // Blue
extern const Color yellow; // Yellow
extern const Color orange; // Orange
extern const Color purple; // Purple
extern const Color cyan; // Cyan
extern const Color lightBlue; // Light Blue
extern const Color darkBlue; // Dark Blue


std::vector<Color> GetColors(); // Function to get the colors for the grid cells