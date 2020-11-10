// class(Solution) variables
vector<vector<int>> ans;
bool reverse_traverse;

// pushes the sub answer in the final ans in the correct order
void push_sub_ans(vector<int> sub_ans) {
    reverse_traverse = !reverse_traverse;
    if (reverse_traverse)
        reverse(sub_ans.begin(), sub_ans.end());
    ans.push_back(sub_ans);
}

// process the current queue iteration and populate next queue while building answer
queue<TreeNode*> processQueue(queue<TreeNode*>& q) {
    queue<TreeNode*> new_q;
    vector<int> sub_ans;
    while (!q.empty()) {
        TreeNode* each = q.front(); q.pop();
        sub_ans.push_back(each->val);
        if (each->left) new_q.push(each->left);
        if (each->right) new_q.push(each->right);
    }
    push_sub_ans(sub_ans);
    return new_q;
}

// inititalize values and start queue processing with root.
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    reverse_traverse = true;
    ans = {};
    if (!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty())
        q = processQueue(q);
    return ans;
}