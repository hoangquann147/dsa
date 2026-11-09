// LAB 2 - PROBLEM 5: RAT IN A MAZE

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Lexicographic direction order; it also determines the order of emitted paths.
const int DR[] = {1, 0, 0, -1};
const int DC[] = {0, -1, 1, 0};
const char DIRECTION[] = {'D', 'L', 'R', 'U'};

struct Cell { int row, col; };

bool inside(int row, int col, int n) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

vector<vector<int>> distancesToGoal(const vector<vector<int>>& maze) {
    const int n = static_cast<int>(maze.size());
    vector<vector<int>> distance(n, vector<int>(n, -1));
    if (maze[n - 1][n - 1] == 0) return distance;
    queue<Cell> pending;
    pending.push({n - 1, n - 1});
    distance[n - 1][n - 1] = 0;
    while (!pending.empty()) {
        int row = pending.front().row, col = pending.front().col;
        pending.pop();
        for (int k = 0; k < 4; ++k) {
            const int nextRow = row + DR[k], nextCol = col + DC[k];
            if (inside(nextRow, nextCol, n) && maze[nextRow][nextCol] == 1 &&
                distance[nextRow][nextCol] == -1) {
                distance[nextRow][nextCol] = distance[row][col] + 1;
                pending.push({nextRow, nextCol});
            }
        }
    }
    return distance;
}

struct Frame { int row; int col; int nextDirection; };

void printShortestPaths(const vector<vector<int>>& distance) {
    const int n = static_cast<int>(distance.size());
    if (distance[0][0] == -1) {
        cout << "No path\n";
        return;
    }
    // Explicit DFS stack avoids a deep function-call stack on a long corridor.
    vector<Frame> frames = {{0, 0, 0}};
    string path;
    while (!frames.empty()) {
        Frame& current = frames.back();
        if (current.row == n - 1 && current.col == n - 1) {
            cout << (path.empty() ? "(empty path)" : path) << '\n';
            frames.pop_back();
            if (!frames.empty()) path.pop_back();
            continue;
        }
        bool advanced = false;
        while (current.nextDirection < 4) {
            const int k = current.nextDirection++;
            const int row = current.row + DR[k], col = current.col + DC[k];
            // Moving one step closer to the goal guarantees a shortest path.
            if (inside(row, col, n) && distance[row][col] == distance[current.row][current.col] - 1) {
                path += DIRECTION[k];
                frames.push_back({row, col, 0});
                advanced = true;
                break; // current reference may have been invalidated by push_back.
            }
        }
        if (!advanced) {
            frames.pop_back();
            if (!frames.empty()) path.pop_back();
        }
    }
}

// Read the square maze and print every shortest path.
int main() {
    int n;
    if (!(cin >> n) || n < 1 || n > 1000) {
        cerr << "Error: invalid maze size\n";
        return 1;
    }
    vector<vector<int>> maze(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (!(cin >> maze[i][j]) || (maze[i][j] != 0 && maze[i][j] != 1)) {
                cerr << "Error: expected binary cells\n";
                return 1;
            }
        }
    if (maze[0][0] == 0) cout << "No path\n";
    else printShortestPaths(distancesToGoal(maze));
    return 0;
}
