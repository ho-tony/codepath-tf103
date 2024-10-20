#include <iostream>
#include <vector>
#include <array>
using namespace std;
class Solution {
public:
    const int INF = 1e7;
    vector<vector<int>> memo;
    vector<vector<int>> DIRS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        memo = vector<vector<int>>(mat.size(), vector<int>(mat[0].size(), INF));
        queue<array<int, 3>> bfs;

        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].size(); ++j) {
                if (mat[i][j] == 0) {
                    memo[i][j] = 0;
                    bfs.push({i, j, 0});
                }
            }
        }
        int visited = 0;
        while (!bfs.empty()) {
            auto top = bfs.front();
            bfs.pop();
            int r = top[0], c = top[1], dist = top[2];
            for (const auto& d : DIRS) {
                int nextR = r + d[0], nextC = c + d[1], nextDist = dist + 1;
                if (nextR < 0 || nextC < 0 || nextR == mat.size() ||
                    nextC == mat[0].size() || memo[nextR][nextC] != INF || mat[nextR][nextC] == 0) {
                    continue;
                }
                
            memo[nextR][nextC] = dist + 1;
            bfs.push({nextR, nextC, nextDist});
        }
    }
    return memo;
}
}
class Solution2 {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (color == image[sr][sc]) return image;
        dfs(image, sr, sc, color, image[sr][sc]);
        return image;
        
    }
    void dfs(vector<vector<int>> & mat, int r, int c, int color, int original) {
        if (r == mat.size() || c == mat[0].size() || r < 0 || c < 0 || mat[r][c] != original) {
            return;
        }
        mat[r][c] = color;

        dfs(mat, r + 1, c, color, original);
        dfs(mat, r - 1, c, color, original);
        dfs(mat, r , c+1, color, original);
        dfs(mat, r , c-1, color, original);


    }
};

;

