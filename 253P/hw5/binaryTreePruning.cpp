// recursively call pruning based on subtrees
bool prune(TreeNode* node) {
    if (!node)
        return false;

    bool left = prune(node->left);
    bool right = prune(node->right);
    if (!left) {
        delete node->left;
        node->left = nullptr;
    }
    if (!right) {
        delete node->right;
        node->right = nullptr;
    }
    return node->val == 1 || left || right;
}

// call sub process prune and handle case when root is to be pruned
TreeNode* pruneTree(TreeNode* root) {
    return prune(root) ? root: nullptr;
}