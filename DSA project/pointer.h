#ifndef POINTER_H
#define POINTER_H

#include <vector>

class Pointer {
private:
    int x, y; // Current position
    int endX, endY; // Target position
    std::vector<std::vector<int>> grid; // Maze grid (modifiable now)

public:
    Pointer(int startX, int startY, int targetX, int targetY, const std::vector<std::vector<int>>& mazeGrid);

    int getX() const;
    int getY() const;
    bool isAtEnd() const;

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    void reset(int startX, int startY, int targetX, int targetY, const std::vector<std::vector<int>>& mazeGrid);
};

#endif
