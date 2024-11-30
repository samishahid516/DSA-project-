#include "Algorithms.h"
#include <queue>
#include <map>
#include <tuple>
#include <cmath>
#include <stack>
#include <algorithm> // For std::reverse
#include <vector>
#include <climits>  // For INT_MAX

using namespace std;

// Helper directions for neighbors (up, down, left, right)
const int dx[4] = { 1, -1, 0, 0 };
const int dy[4] = { 0, 0, 1, -1 };

// BFS Algorithm
vector<pair<int, int>> Algorithms::bfs(const vector<vector<int>>& maze, pair<int, int> start, pair<int, int> end) {
    queue<pair<int, int>> q;
    map<pair<int, int>, pair<int, int>> parent; // Tracks the path
    q.push(start);
    parent[start] = { -1, -1 };

    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int x = p.first;
        int y = p.second;

        if (make_pair(x, y) == end) {
            // Reconstruct the path
            vector<pair<int, int>> path;
            for (auto current = end; current != make_pair(-1, -1); current = parent[current]) {
                path.push_back(current);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < maze.size() && ny < maze[0].size() && maze[nx][ny] == 0 && parent.find(make_pair(nx, ny)) == parent.end()) {
                q.push(make_pair(nx, ny));
                parent[make_pair(nx, ny)] = make_pair(x, y);
            }
        }
    }
    return {}; // No path found
}

// DFS Algorithm
vector<pair<int, int>> Algorithms::dfs(const vector<vector<int>>& maze, pair<int, int> start, pair<int, int> end) {
    stack<pair<int, int>> s;
    map<pair<int, int>, pair<int, int>> parent; // Tracks the path
    s.push(start);
    parent[start] = { -1, -1 };

    while (!s.empty()) {
        pair<int, int> p = s.top();
        s.pop();
        int x = p.first;
        int y = p.second;

        if (make_pair(x, y) == end) {
            // Reconstruct the path
            vector<pair<int, int>> path;
            for (auto current = end; current != make_pair(-1, -1); current = parent[current]) {
                path.push_back(current);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < maze.size() && ny < maze[0].size() && maze[nx][ny] == 0 && parent.find(make_pair(nx, ny)) == parent.end()) {
                s.push(make_pair(nx, ny));
                parent[make_pair(nx, ny)] = make_pair(x, y);
            }
        }
    }
    return {}; // No path found
}

// Dijkstra's Algorithm
vector<pair<int, int>> Algorithms::dijkstra(const vector<vector<int>>& maze, pair<int, int> start, pair<int, int> end) {
    vector<vector<int>> dist(maze.size(), vector<int>(maze[0].size(), INT_MAX));
    map<pair<int, int>, pair<int, int>> parent;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    dist[start.first][start.second] = 0;
    pq.push(make_tuple(0, start.first, start.second));
    parent[start] = { -1, -1 };

    while (!pq.empty()) {
        tuple<int, int, int> p = pq.top();
        pq.pop();
        int d = get<0>(p);
        int x = get<1>(p);
        int y = get<2>(p);

        if (make_pair(x, y) == end) {
            // Reconstruct the path
            vector<pair<int, int>> path;
            for (auto current = end; current != make_pair(-1, -1); current = parent[current]) {
                path.push_back(current);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < maze.size() && ny < maze[0].size() && maze[nx][ny] == 0) {
                int newDist = d + 1;
                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                    pq.push(make_tuple(newDist, nx, ny));
                    parent[make_pair(nx, ny)] = make_pair(x, y);
                }
            }
        }
    }
    return {}; // No path found
}

// A* Algorithm
vector<pair<int, int>> Algorithms::aStar(const vector<vector<int>>& maze, pair<int, int> start, pair<int, int> end) {
    vector<vector<int>> gScore(maze.size(), vector<int>(maze[0].size(), INT_MAX));
    vector<vector<int>> fScore(maze.size(), vector<int>(maze[0].size(), INT_MAX));
    map<pair<int, int>, pair<int, int>> parent;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    gScore[start.first][start.second] = 0;
    fScore[start.first][start.second] = heuristic(start, end);
    pq.push(make_tuple(fScore[start.first][start.second], start.first, start.second));
    parent[start] = { -1, -1 };

    while (!pq.empty()) {
        tuple<int, int, int> p = pq.top();
        pq.pop();
        int f = get<0>(p);
        int x = get<1>(p);
        int y = get<2>(p);

        if (make_pair(x, y) == end) {
            // Reconstruct the path
            vector<pair<int, int>> path;
            for (auto current = end; current != make_pair(-1, -1); current = parent[current]) {
                path.push_back(current);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < maze.size() && ny < maze[0].size() && maze[nx][ny] == 0) {
                int tentative_gScore = gScore[x][y] + 1;
                if (tentative_gScore < gScore[nx][ny]) {
                    parent[make_pair(nx, ny)] = make_pair(x, y);
                    gScore[nx][ny] = tentative_gScore;
                    fScore[nx][ny] = gScore[nx][ny] + heuristic(make_pair(nx, ny), end);
                    pq.push(make_tuple(fScore[nx][ny], nx, ny));
                }
            }
        }
    }
    return {}; // No path found
}

// Heuristic function for A* (Manhattan distance)
int Algorithms::heuristic(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}
