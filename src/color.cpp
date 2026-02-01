#include "color.h"

const Color darkGrey = {26, 31, 40, 255}; // Empty cell color (black)
const Color red = {255, 0, 0, 255}; // Red
const Color green = {0, 255, 0, 255}; // Green
const Color blue = {0, 0, 255, 255}; // Blue
const Color yellow = {255, 255, 0, 255}; // Yellow
const Color orange = {255, 165, 0, 255}; // Orange
const Color purple = {128, 0, 128, 255}; // Purple
const Color cyan = {0, 255, 255, 255}; // Cyan
const Color lightBlue = {173, 216, 230, 255}; // Light Blue
const Color darkBlue = {44, 44, 127, 255}; // Dark

std::vector<Color> GetColors() {
    // Define the colors for the grid cells
    return {darkGrey, red, green, blue, yellow, orange, purple, cyan};
}