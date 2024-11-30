#ifndef MAZE_H
#define MAZE_H

#include <vector>

class Maze {
private:
    int rows, cols;
    std::vector<std::vector<int>> grid;

public:
    Maze(int rows, int cols);
    void generateMaze(); // Randomly generates the maze
    const std::vector<std::vector<int>>& getGrid() const;
};

#endif
