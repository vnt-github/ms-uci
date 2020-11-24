vector<int> dp;
// use dp with binary search to solve this problem
vector<int> countSmaller(vector<int>& nums) {
    vector<int> count;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        auto insert_pos = lower_bound(dp.begin(), dp.end(), nums[i]);
        int smallers = insert_pos - dp.begin();
        dp.insert(insert_pos, nums[i]);
        count.push_back(smallers);
    }
    reverse(count.begin(), count.end());
    return count;
}