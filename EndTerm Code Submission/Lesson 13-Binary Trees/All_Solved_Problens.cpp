#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Binary Tree Node Structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* Problem 1: Given a binary tree, return its inorder traversal (Left-Root-Right) */
void inorderHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderHelper(root->left, result);
    result.push_back(root->val);
    inorderHelper(root->right, result);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    inorderHelper(root, result);
    return result;
}




/* Problem 2: Given a binary tree, return its preorder traversal (Root-Left-Right) */
void preorderHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorderHelper(root->left, result);
    preorderHelper(root->right, result);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    preorderHelper(root, result);
    return result;
}




/* Problem 3: Given a binary tree, return its postorder traversal (Left-Right-Root) */
void postorderHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorderHelper(root->left, result);
    postorderHelper(root->right, result);
    result.push_back(root->val);
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;
    postorderHelper(root, result);
    return result;
}




/* Problem 4: Given a binary tree, return its level order traversal (BFS) */
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            currentLevel.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(currentLevel);
    }
    
    return result;
}




/* Problem 5: Flatten binary tree to linked list in preorder sequence */
void flatten(TreeNode* root) {
    if (!root) return;
    
    flatten(root->left);
    flatten(root->right);
    
    TreeNode* right = root->right;
    root->right = root->left;
    root->left = nullptr;
    
    while (root->right) {
        root = root->right;
    }
    root->right = right;
}




/* Problem 6: Find maximum path sum in binary tree (path may not pass through root) */
int maxPathSumHelper(TreeNode* root, int& maxSum) {
    if (!root) return 0;
    
    int leftSum = max(0, maxPathSumHelper(root->left, maxSum));
    int rightSum = max(0, maxPathSumHelper(root->right, maxSum));
    
    maxSum = max(maxSum, leftSum + rightSum + root->val);
    
    return max(leftSum, rightSum) + root->val;
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, maxSum);
    return maxSum;
}





/* Problem 7: Check if two binary trees are identical */
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    if (p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}