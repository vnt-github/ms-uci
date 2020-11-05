// get answer list with default 0 value prepopulated with correct size
vector<int> getAnsList(ListNode* head) {
    vector<int> ans;
    ListNode* curr = head;
    while (curr) {
        ans.push_back(0);
        curr = curr->next;
    }
    return ans;
}

// maintain a strictly decreasing stack with entries (index, value) to compare and set next greater value with current
vector<int> nextLargerNodes(ListNode* head) {
    vector<int> ans = getAnsList(head);
    vector<pair<int, int>> stack;
    ListNode* curr = head;
    int curr_i = 0;
    while (curr) {
        while (stack.size() && stack.back().second < curr->val) {
            ans[stack.back().first] = curr->val;
            stack.pop_back();
        }
        stack.push_back(make_pair(curr_i++, curr->val));
        curr = curr->next;
    }
    return ans;
}