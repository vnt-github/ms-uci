// return initial value of dp where dp[req_sum][i] is true if some subset from 1st to i'th has a sum equal to sum req_sum
vector<vector<bool>> getInitDP(int m, int n) {
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    for (int i = 0; i <= n; i++)
        dp[0][i] = true;
    return dp;
}

// solution to leetcode 1049 using  variation of 0/1 knapsack algo
int lastStoneWeightII(vector<int> stones) {
    int sum = 0, max_req_sum = 0;
    for (int each : stones) sum += each;
    vector<vector<bool>> dp = getInitDP(sum+1, stones.size()+1);
    
    for (int i = 1; i <= stones.size(); i++) {
        for (int req_sum = 1; req_sum <= sum / 2; req_sum++) {
            if (dp[req_sum][i - 1] || (req_sum >= stones[i - 1] && dp[req_sum - stones[i - 1]][i - 1])) {
                dp[req_sum][i] = true;
                max_req_sum = max(max_req_sum, req_sum);
            }
        }
    }
    return sum - 2 * max_req_sum;
}

