#include "Pointer.h"

// Constructor: Initialize the pointer's starting and ending positions
Pointer::Pointer(int startX, int startY, int targetX, int targetY, const std::vector<std::vector<int>>& mazeGrid)
    : x(startX), y(startY), endX(targetX), endY(targetY), grid(mazeGrid) {}

// Get the current X position
int Pointer::getX() const {
    return x;
}

// Get the current Y position
int Pointer::getY() const {
    return y;
}

// Check if the pointer is at the target position
bool Pointer::isAtEnd() const {
    return x == endX && y == endY;
}

// Move up if the space is valid
bool Pointer::moveUp() {
    if (y > 0 && grid[y - 1][x] == 0) {
        y--;
        return true;
    }
    return false;
}

// Move down if the space is valid
bool Pointer::moveDown() {
    if (y < grid.size() - 1 && grid[y + 1][x] == 0) {
        y++;
        return true;
    }
    return false;
}

// Move left if the space is valid
bool Pointer::moveLeft() {
    if (x > 0 && grid[y][x - 1] == 0) {
        x--;
        return true;
    }
    return false;
}

// Move right if the space is valid
bool Pointer::moveRight() {
    if (x < grid[0].size() - 1 && grid[y][x + 1] == 0) {
        x++;
        return true;
    }
    return false;
}

// Reset the pointer to a new start and end position
void Pointer::reset(int startX, int startY, int targetX, int targetY, const std::vector<std::vector<int>>& mazeGrid) {
    x = startX;
    y = startY;
    endX = targetX;
    endY = targetY;
    grid = mazeGrid; // This now works because grid is not const
}
