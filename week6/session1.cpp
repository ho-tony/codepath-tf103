#include <iostream>
#include <vector>
#include <array>
using namespace std;
class Solution {
        // U - Understand
    // Q1: Are we guaranteed that there will always be a 0 in the input matrix?
    // Q2: Can the matrix contain other values besides 0 and 1, or is it strictly binary?

    // M - Match
    // Likely: BFS because we are looking for the shortest path from multiple sources (the 0s) to other cells.
    // Likely: Grid traversal, as the problem involves processing a matrix.
    // Unlikely: Sorting algorithms, because this is a search problem.

    // P - Plan
    // 1. We need to traverse the matrix to identify all the cells containing 0s.
    // 2. For each 0, use a BFS to calculate the shortest distance to the other cells.
    // 3. As we traverse the grid, if we find a shorter path to a cell, we update the memoization table.
    // 4. Return the matrix where each cell contains the shortest distance to a 0.

    // I - Implement
    // Implementation done in C++ as provided in the original code.

    // RE - Review and Evaluate
    // Strength: The BFS approach ensures we calculate the shortest distance in a grid efficiently.
    // Weakness: The space complexity is O(m * n) due to the additional memoization table and queue.
    // Future Work: Optimize the space complexity by performing in-place updates, if the input matrix can be modified.
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
    // U - Understand
    // Q1: What are the constraints on the size of the image matrix?
    // Q2: Can we assume the image will always have a valid starting pixel?

    // M - Match
    // Likely: DFS (Depth-First Search) because we need to explore connected components.
    // Likely: Recursion, since DFS lends itself to recursive implementation.
    // Unlikely: BFS because we are not looking for the shortest path but rather filling regions.

    // P - Plan
    // 1. Identify the original color of the starting pixel.
    // 2. Traverse the grid using DFS, visiting all connected pixels that share the same original color.
    // 3. Change the color of each visited pixel to the new color.
    // 4. Ensure that no pixels outside the region with the original color are affected.

    // I - Implement
    // Implementation done in C++ as provided in the original code.

    // RE - Review and Evaluate
    // Strength: DFS ensures that all connected pixels are visited and updated with the new color.
    // Weakness: Recursion depth could be an issue if the image is large or has many connected pixels.
    // Future Work: Implement an iterative DFS to avoid stack overflow issues on large images.
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

