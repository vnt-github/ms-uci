// solution to leetcode 64. Minimum Path Sum Medium
int minPathSum(vector<vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++)
        for (size_t j = 0; j < matrix[i].size(); j++)
            if (i == 0 && j == 0) continue;
            else if (i == 0) matrix[i][j] += matrix[i][j-1];
            else if (j == 0) matrix[i][j] += matrix[i-1][j];
            else matrix[i][j] += min(matrix[i-1][j], matrix[i][j-1]);
    return matrix.empty() ? 0: matrix.back().back();
}