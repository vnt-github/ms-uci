// dfs returning a pair with 
// first value as the sum at max depth as pair
pair<int, int> dfs(node *root) {
    if (!root)
        return make_pair(0, 0);
    if (!root->left && !root->right)
        return make_pair(root->val, 0);
    // left subtrees pair with sum at max depth as pair
    // ie. left sum and depth (lsd)
    pair<int, int> lsd = dfs(root->left);
    // right subtrees pair with sum at max depth as pair
    // i.e right sum depth (rsd)
    pair<int, int> rsd = dfs(root->right);
    if (lsd.second > rsd.second)
        return make_pair(lsd.first, lsd.second+1);
    else if (rsd.second > lsd.second)
        return make_pair(rsd.first, rsd.second+1);
    else
        return make_pair(rsd.first+lsd.first, lsd.second+1);
}
int deepestLeavesSum(node* root) {
    // the dfs returns the pair
    // with first value as sum at the max depth
    // and the second value is that max depth
    return dfs(root).first;
}