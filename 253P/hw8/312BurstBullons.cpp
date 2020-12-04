vector<vector<int>> dp;
int maxCoinsTD(vector<int>& arr, int i, int j) {
    if (dp[i][j])
        return dp[i][j];

    if (i > j)
        return 0;
    if (i == j)
        return arr[i-1]*arr[i]*arr[i+1];

    dp[i][j] = INT8_MIN;
    for (int p = i; p <= j; p++) {
        dp[i][j] = max(dp[i][j], maxCoinsTD(arr, i, p-1) + maxCoinsTD(arr, p+1, j) + arr[i-1]*arr[p]*arr[j+1]);
    }

    return dp[i][j];
}
int maxCoins(vector<int>& original_nums) {
    int n = original_nums.size() + 1;
    dp = vector<vector<int>> (n+1, vector<int> (n+1));
    original_nums.insert(original_nums.begin(), 1);
    original_nums.push_back(1);
    int ans = maxCoinsTD(original_nums, 1, original_nums.size() - 2);
    return ans;
}