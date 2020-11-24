// traverse up down left andright from curr i, j
// if hit boundary return false
// if hit non zero return true
// else set curr 1 and dfs traverse further
bool dfs(vector<vector<int>>& grid, int i, int j) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
        return false;
    if (grid[i][j])
        return true;

    grid[i][j] = 1;
    bool up = dfs(grid, i-1, j);
    bool down = dfs(grid, i+1, j);
    bool left = dfs(grid, i, j-1);
    bool right = dfs(grid, i, j+1);
    return  up && down && left && right;
}
int closedIsland(vector<vector<int>>& grid) {
    int ans=0;
    for (int i=0; i < grid.size(); i++)
        for (int j=0; j < grid[0].size(); j++)
            if (!grid[i][j] && dfs(grid, i, j))
                ans += 1;
    return ans;
}