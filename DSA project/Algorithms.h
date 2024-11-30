#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <utility>

class Algorithms {
public:
    static std::vector<std::pair<int, int>> bfs(const std::vector<std::vector<int>>& maze, std::pair<int, int> start, std::pair<int, int> end);
    static std::vector<std::pair<int, int>> dfs(const std::vector<std::vector<int>>& maze, std::pair<int, int> start, std::pair<int, int> end);
    static std::vector<std::pair<int, int>> dijkstra(const std::vector<std::vector<int>>& maze, std::pair<int, int> start, std::pair<int, int> end);
    static std::vector<std::pair<int, int>> aStar(const std::vector<std::vector<int>>& maze, std::pair<int, int> start, std::pair<int, int> end);

private:
    static int heuristic(std::pair<int, int> a, std::pair<int, int> b);
};

#endif
