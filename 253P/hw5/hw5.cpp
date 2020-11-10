// C++ program to insertNode a node in AVL tree 
#include <iostream> 
#include <vector>
#include <sstream>

using namespace std;

struct TreeNode { 
    int val; 
    TreeNode *left;
    TreeNode *right;
    int height;
    TreeNode(int val): val(val), left(nullptr), right(nullptr), height(1) {}
};

// return height of a node, if it's nullptr return 0.
int getHeight(TreeNode *node) {
	return node ? node->height: 0; 
}

// perform right rotate and return new Root
TreeNode *rightRotate(TreeNode *y) {
	TreeNode *x = y->left; 
	TreeNode *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1; 
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1; 

	// Return new root 
	return x; 
} 

// A utility function to left 
// rotate subtree rooted with x 
// See the diagram given above. 
TreeNode *leftRotate(TreeNode *x) {
	TreeNode *y = x->right;
	TreeNode *T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	// Update heights 
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	// Return new root
	return y;
} 

// Get Balance factor of node 
int getBalance(TreeNode *node) {
	return node ? getHeight(node->left) - getHeight(node->right): 0;
}

// return new root with insertNodeion of new node with val
TreeNode* insertNode(TreeNode* node, int val) {
    // BST insertNodeion
	if (!node) {
        cout << val << " (inserted)" << endl;
		return new TreeNode(val); 
    }

    cout << node->val << " ";
	if (val < node->val)
		node->left = insertNode(node->left, val); 
	else if (val > node->val) 
		node->right = insertNode(node->right, val); 
	else
		return node; 

	node->height = 1 + max(getHeight(node->left), getHeight(node->right)); 

	int balance = getBalance(node); 

	// perform right Rotation once
	if (balance > 1 && val < node->left->val) 
		return rightRotate(node); 

    // perform left rotation once
	if (balance < -1 && val > node->right->val) 
		return leftRotate(node); 

    // perform left rotation and then right rotation
	if (balance > 1 && val > node->left->val) {
		node->left = leftRotate(node->left); 
		return rightRotate(node);
	}

    // perform right rotation and then left rotation
	if (balance < -1 && val < node->right->val) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node; 
} 

void deleteTree(TreeNode *root) {
    if (!root) return;
    deleteTree(root->left); 
    deleteTree(root->right); 
    delete root;
}

// return the node with min value
TreeNode * minNode(TreeNode* node) {
    TreeNode* curr = node;
    while (curr->left)  
        curr = curr->left;
    return curr;  
}

TreeNode* findNode(TreeNode* root, int val) {
    if (!root) {
        cout << "(not found!)" << endl;
        return root;
    }
    
    cout << root->val << " ";
    if (val < root->val)
        return findNode(root->left, val);
    else if (val > root->val)
        return findNode(root->right, val);
    else {
        cout << "(found)" << endl;
        return root;
    }
}

// return new root with deletion of node with val if found
TreeNode* deleteNode(TreeNode* root, int val, bool log=true)  
{
    // bst deletion  
    if (!root) {
        if (log) cout << "(not found!)" << endl;
        return root;
    }
    if (log) cout << root->val << " ";
    if (val < root->val)
        root->left = deleteNode(root->left, val, log);
    else if(val > root->val)
        root->right = deleteNode(root->right, val, log);
    // found the node to be deleted
    else {
        if (log) cout << " (deleted)" << endl;
        TreeNode *temp;
        if (!root->left && !root->right) {
            temp = root;
            root = nullptr;
            delete temp;
        } else if (!root->left || !root->right) {
            temp = root->left ? root->left : root->right;
            *root = *temp;
            delete temp;
        } else {  
            TreeNode* temp = minNode(root->right);  
            root->val = temp->val;  
            root->right = deleteNode(root->right, temp->val, false);
        }  
    }  
  
    // if the tree had only one node then return
    if (!root)  
        return root;
  
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));  
   
    int balance = getBalance(root);  
  
    // perfrom right rotation once
    if (balance > 1 && getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // perform left rotation and then right rotation 
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }

    // perform left rotation
    if (balance < -1 && getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // perform right rotation and then left rotation
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  

// splits a string on the delimiter
vector<string> split(string& str, char delim)
{
    vector<string> values;
    std::stringstream ss(str);
    string value;
    while (std::getline(ss, value, delim)) {
        values.push_back(value);
    }
    return values;
}

// check if a string is a integer
bool isNumber(string s)
{
    if (s.length() > 1 && s[0] == '-')
        s = s.substr(1);
    for (auto &&each : s)
        if (!isdigit(each))
            return false;

    return true;
}

// read commands from stdin and call corresponding functionss
void handleInput() {
    string input, command;
    int val;
    TreeNode *root = nullptr;
    while (true) {
        cin.clear();
        getline(cin, input);
        if (input == "exit") {
            deleteTree(root);
            break;
        }
        vector<string> ip = split(input, ' ');
        if (ip.size() != 2 || !isNumber(ip[1])) {
            cout << "incorrect format use: command integer_value" << endl;
            continue;
        }
        command = ip[0];
        val = stoi(ip[1]);
        if (command == "insert") {
            root = insertNode(root, val);
        } else if (command == "find")
            findNode(root, val);
        else if (command == "delete")
            root = deleteNode(root, val);
        else
            cout << "invalid command" << endl;
    }
}

int main() {
    handleInput();
}