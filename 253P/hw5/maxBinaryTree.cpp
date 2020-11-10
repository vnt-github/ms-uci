// return the index of nums vector with max value
int getMaxIndex(vector<int>& nums, int start_i, int end_i) {
    int ans = start_i;
    for (int i = start_i; i <= end_i; i++)
        if (nums[ans] < nums[i])
            ans = i;
    return ans;
}

// make max binary tree recursively with adjusted start and end indices
TreeNode* maxBT(vector<int>& nums, int start_i, int end_i) {
    if (start_i > end_i)
        return nullptr;
    int max_i = getMaxIndex(nums, start_i, end_i);
    return new TreeNode(nums[max_i], maxBT(nums, start_i, max_i-1), maxBT(nums, max_i+1, end_i));
}

// call sub function with initial start and end indices
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return maxBT(nums, 0, nums.size()-1);
}
