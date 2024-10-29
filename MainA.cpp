#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

vector<pair<int, int>> get_next_moves(int x, int y, int dx, int dy) {
    vector<pair<int, int>> moves;
    moves.emplace_back(x + dx, y + dy); 
    moves.emplace_back(x + dy, y - dx); 
    moves.emplace_back(x - dy, y + dx); 
    moves.emplace_back(x - dx, y - dy); 
    return moves;
}

bool is_valid(int x, int y, int M, int N, const vector<vector<int>>& grid, const vector<vector<bool>>& visited) {
    return x >= 0 && x < M && y >= 0 && y < N && grid[x][y] == 0 && !visited[x][y];
}

int bfs(const vector<vector<int>>& grid, int M, int N, pair<int, int> src, pair<int, int> dest, pair<int, int> move_rule) {
    if (src == dest) {
        return 0;
    }

    queue<tuple<int, int, int>> q; 
    q.emplace(src.first, src.second, 0);
    vector<vector<bool>> visited(M, vector<bool>(N, false));
    visited[src.first][src.second] = true;

    while (!q.empty()) {
        auto [x, y, steps] = q.front();
        q.pop();

        if (make_pair(x, y) == dest) {
            return steps;
        }

        for (const auto& [next_x, next_y] : get_next_moves(x, y, move_rule.first, move_rule.second)) {
            if (is_valid(next_x, next_y, M, N, grid, visited)) {
                visited[next_x][next_y] = true;
                q.emplace(next_x, next_y, steps + 1);
            }
        }
    }

    return -1; 
}

int main() {
    int M, N;
    cin >> M >> N;
    vector<vector<int>> grid(M, vector<int>(N));

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    int src_x, src_y, dest_x, dest_y;
    cin >> src_x >> src_y >> dest_x >> dest_y;
    pair<int, int> src = {src_x, src_y};
    pair<int, int> dest = {dest_x, dest_y};

    int move_dx, move_dy;
    cin >> move_dx >> move_dy;
    pair<int, int> move_rule = {move_dx, move_dy};

    int result = bfs(grid, M, N, src, dest, move_rule);
    cout << result;

    return 0;
}
