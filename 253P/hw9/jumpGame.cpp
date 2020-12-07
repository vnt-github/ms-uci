// solution to leetcode 55. Jump Game
bool canJump(vector<int>& nums) {
    if (nums.size() == 1) return true;

    int val = 1;
    for (int i = nums.size() - 2; i >= 1; i--)
        val = (nums[i] >= val) ? 1 : val + 1;

    return (nums[0] >= val);
}