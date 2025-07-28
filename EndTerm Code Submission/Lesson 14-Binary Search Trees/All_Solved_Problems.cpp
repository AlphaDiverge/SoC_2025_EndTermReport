#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* Problem 1: Check if a binary tree is a valid BST */
bool isValidBSTHelper(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
    if (!root) return true;
    if ((minNode && root->val <= minNode->val) || 
        (maxNode && root->val >= maxNode->val)) {
        return false;
    }
    return isValidBSTHelper(root->left, minNode, root) && 
           isValidBSTHelper(root->right, root, maxNode);
}

bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, nullptr, nullptr);
}




/* Problem 2: BST Iterator for inorder traversal */
class BSTIterator {
private:
    stack<TreeNode*> st;
    void pushAll(TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }
public:
    BSTIterator(TreeNode* root) {
        pushAll(root);
    }
    
    int next() {
        TreeNode* node = st.top();
        st.pop();
        pushAll(node->right);
        return node->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};




/* Problem 3: Find the largest BST subtree */
struct BSTInfo {
    bool isBST;
    int size;
    int minVal;
    int maxVal;
    BSTInfo(bool b, int s, int min, int max) : 
        isBST(b), size(s), minVal(min), maxVal(max) {}
};

BSTInfo largestBSTHelper(TreeNode* root) {
    if (!root) {
        return BSTInfo(true, 0, INT_MAX, INT_MIN);
    }
    
    BSTInfo left = largestBSTHelper(root->left);
    BSTInfo right = largestBSTHelper(root->right);
    
    if (left.isBST && right.isBST && 
        root->val > left.maxVal && 
        root->val < right.minVal) {
        return BSTInfo(true, 
                      1 + left.size + right.size,
                      min(root->val, left.minVal),
                      max(root->val, right.maxVal));
    }
    
    return BSTInfo(false, max(left.size, right.size), 0, 0);
}

int largestBSTSubtree(TreeNode* root) {
    return largestBSTHelper(root).size;
}





/* Problem 4: Delete a node in BST */
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        
        TreeNode* successor = root->right;
        while (successor->left) {
            successor = successor->left;
        }
        root->val = successor->val;
        root->right = deleteNode(root->right, successor->val);
    }
    return root;
}





/* Problem 5: Find floor and ceil in BST */
vector<int> floorAndCeil(TreeNode* root, int key) {
    int floor = -1, ceil = -1;
    while (root) {
        if (root->val == key) {
            return {root->val, root->val};
        } else if (root->val < key) {
            floor = root->val;
            root = root->right;
        } else {
            ceil = root->val;
            root = root->left;
        }
    }
    return {floor, ceil};
}