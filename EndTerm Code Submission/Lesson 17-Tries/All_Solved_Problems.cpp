#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd = false;
};

/* Problem 1: Find the longest word where every prefix exists in the dictionary */
class CompleteStringTrie {
    TrieNode* root;
    
public:
    CompleteStringTrie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }
    
    bool checkAllPrefixes(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c) || !node->children[c]->isEnd) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
    
    string longestCompleteString(vector<string>& words) {
        for (string word : words) {
            insert(word);
        }
        
        string longest = "";
        for (string word : words) {
            if (checkAllPrefixes(word)) {
                if (word.size() > longest.size() || 
                   (word.size() == longest.size() && word < longest)) {
                    longest = word;
                }
            }
        }
        return longest.empty() ? "None" : longest;
    }
};





/* Problem 2: Count distinct substrings in a string using Trie */
class DistinctSubstrings {
    TrieNode* root;
    int count;
    
public:
    DistinctSubstrings() {
        root = new TrieNode();
        count = 1;
    }
    
    int countDistinct(string s) {
        for (int i = 0; i < s.size(); i++) {
            TrieNode* node = root;
            for (int j = i; j < s.size(); j++) {
                char c = s[j];
                if (!node->children.count(c)) {
                    node->children[c] = new TrieNode();
                    count++;
                }
                node = node->children[c];
            }
        }
        return count;
    }
};




/* Problem 3: Find maximum XOR of two numbers in an array */
class MaxXORTrie {
    TrieNode* root;
    
public:
    MaxXORTrie() {
        root = new TrieNode();
    }
    
    void insert(int num) {
        TrieNode* node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            char c = bit + '0';
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
    }
    
    int findMaxXOR(int num) {
        TrieNode* node = root;
        int maxXOR = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            char target = (1 - bit) + '0';
            if (node->children.count(target)) {
                maxXOR |= (1 << i);
                node = node->children[target];
            } else {
                node = node->children[bit + '0'];
            }
        }
        return maxXOR;
    }
    
    int findMaximumXOR(vector<int>& nums) {
        int maxXOR = 0;
        for (int num : nums) {
            insert(num);
            maxXOR = max(maxXOR, findMaxXOR(num));
        }
        return maxXOR;
    }
};




/* Problem 4: Maximum XOR with an element from array for each query */
class QueryOptimizedTrie {
    struct Node {
        Node* children[2] = {nullptr, nullptr};
        int minNum = INT_MAX;
    };
    
    Node* root;
    
public:
    QueryOptimizedTrie() {
        root = new Node();
    }
    
    void insert(int num) {
        Node* node = root;
        node->minNum = min(node->minNum, num);
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new Node();
            }
            node = node->children[bit];
            node->minNum = min(node->minNum, num);
        }
    }
    
    int query(int x, int m) {
        Node* node = root;
        if (node->minNum > m) return -1;
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int target = 1 - bit;
            if (node->children[target] && node->children[target]->minNum <= m) {
                res |= (1 << i);
                node = node->children[target];
            } else {
                node = node->children[bit];
            }
        }
        return res;
    }
    
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(), nums.end());
        for (int num : nums) {
            insert(num);
        }
        
        vector<int> results;
        for (auto& q : queries) {
            results.push_back(query(q[0], q[1]));
        }
        return results;
    }
};