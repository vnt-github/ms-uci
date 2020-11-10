// - [ ] https://www.youtube.com/watch?v=aQS9DqLWxw4&ab_channel=AcmeGroups
// - [ ] http://www.csanimated.com/animation.php?t=Self-balancing_binary_search_tree
#include <iostream>

using namespace std;

template <typename KeyType, typename InfoType>
class TreeNode
{
    private:
        KeyType key;
        InfoType info;
        TreeNode * left, * right;
    public:
        TreeNode(KeyType k, InfoType e, TreeNode* l, TreeNode *r): key(k), info(e), left(l), right(r){}
        static TreeNode * newNode(KeyType k, InfoType e, TreeNode * l, TreeNode * r) {
            return new TreeNode(k,e,l, r);
        }
        static TreeNode* insert(KeyType key, InfoType info, TreeNode* RootT) {
            if (!RootT)
                RootT = newNode(key, info, nullptr, nullptr);
            
            TreeNode *t = RootT;
            while (t->key != key) {
                if (key < t->key) {
                    if (!t->left)
                        t->left = newNode(key, info, nullptr, nullptr);
                } else if (key > t->key) {
                    if (!t->right)
                        t->right = newNode(key, info, nullptr, nullptr);
                }
                t->info = info;
                return RootT;
            }
        }

        TreeNode * find(KeyType key, TreeNode * t) {
            while ( t != nullptr )
                if ( key  <  t->key )
                    t = t->left;
                else if ( key  >  t->key )
                    t = t->right;  
                else // found it!
                    return t;
            return nullptr;
        }

        TreeNode * remove( KeyType key, TreeNode * t )
        {
            TreeNode * toRemove = find(key, t); // must do in-line
            if ( toRemove->left  ==  nullptr )
                if ( toRemove->right  ==  nullptr )
                    return nullptr;
                else
                    return toRemove->right;
            else if ( toRemove->right == nullptr )
                return toRemove->left;
            else {  // hard case, two children
                TreeNode * predecessorNode = findPred(key, toRemove);
                swapKeyAndInfo(predecessorNode, toRemove);
                toRemove = remove(key, toRemove);
                return toRemove;
            }
        }

        static void print(ostream & out , TreeNode * t);
        static void deleteNode(TreeNode * t) { delete t; }
        static void deleteTree(TreeNode * t);
};



template <typename KeyType, typename InfoType>
class BinarySearchTree
{
    TreeNode<KeyType, InfoType> *root;
};