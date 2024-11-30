#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm> // For std::shuffle
#include <random>    // For random number generator

using namespace std;

// Direction vectors for moving up, down, left, right
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

Maze::Maze(int rows, int cols) : rows(rows), cols(cols), grid(rows, vector<int>(cols, 1)) {}

void Maze::generateMaze() {
    srand(static_cast<unsigned>(time(0)));

    // Initialize the grid with walls
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 1; // All cells are walls
        }
    }

    // Start position
    int startX = 1, startY = 1;
    grid[startY][startX] = 0; // Make the start cell a path

    // DFS Stack
    stack<pair<int, int>> stack;
    stack.push({startX, startY});

    random_device rd;  // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;
        stack.pop();

        // Randomize directions
        vector<int> dirs = {0, 1, 2, 3};
        shuffle(dirs.begin(), dirs.end(), gen);

        for (int dir : dirs) {
            int nx = x + dx[dir] * 2;
            int ny = y + dy[dir] * 2;

            if (nx > 0 && ny > 0 && nx < cols - 1 && ny < rows - 1 && grid[ny][nx] == 1) {
                // Remove wall between cells
                grid[y + dy[dir]][x + dx[dir]] = 0;
                grid[ny][nx] = 0;

                stack.push({nx, ny});
            }
        }
    }
}

const vector<vector<int>>& Maze::getGrid() const {
    return grid;
}
