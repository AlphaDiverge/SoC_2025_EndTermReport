#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

/*Problem 1: Power Set*/
vector<string> subsequences(string s) {
    vector<string> result;
    generate(s, "", 0, result);
    return result;
}

void generate(string s, string current, int index, vector<string>& result) {
    if (index == s.size()) {
        if (!current.empty()) result.push_back(current);
        return;
    }
    generate(s, current + s[index], index + 1, result);
    generate(s, current, index + 1, result);
}
//This method save the subsets in the vector for future use and prints, rather than simply printing them.



/*Problem 2: Has a subsequence with sum k*/
bool hasSubsequenceSum(vector<int>& nums, int k) {
    return helper(nums, k, 0, 0);
}

bool helper(vector<int>& nums, int k, int sum, int index) {
    if (sum == k) return true;
    if (index >= nums.size()) return false;
    return helper(nums, k, sum + nums[index], index + 1) || helper(nums, k, sum, index + 1);
}



/*Problem 3: Word Search in a 2D array*/
bool exist(vector<vector<char>> board, string word) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (search(board, word, i, j, 0)) return true;
        }
    }
    return false;
}

bool search(vector<vector<char>> board, string word, int i, int j, int index) {
    if (index == word.size()) return true;
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index]) return false;
    char temp = board[i][j];
    board[i][j] = '#';
    bool found = search(board, word, i + 1, j, index + 1) ||
                search(board, word, i - 1, j, index + 1) ||
                search(board, word, i, j + 1, index + 1) ||
                search(board, word, i, j - 1, index + 1);
    board[i][j] = temp;
    return found;
}



/*Problem 4: All sums possible for subsets*/
vector<int> subsetSums(vector<int>& nums) {
    vector<int> sums;
    generateSums(nums, 0, 0, sums);
    sort(sums.begin(), sums.end());
    return sums;
}

void generateSums(vector<int>& nums, int index, int currentSum, vector<int>& sums) {
    if (index == nums.size()) {
        sums.push_back(currentSum);
        return;
    }
    generateSums(nums, index + 1, currentSum + nums[index], sums);
    generateSums(nums, index + 1, currentSum, sums);
}