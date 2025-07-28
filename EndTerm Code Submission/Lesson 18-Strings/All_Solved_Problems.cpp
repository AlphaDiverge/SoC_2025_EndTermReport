#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/* Problem 1: Minimum bracket reversals for balancing */
int minBracketReversals(string s) {
    if (s.size() % 2 != 0) return -1;
    int open = 0, close = 0;
    
    for (char c : s) {
        if (c == '(') {
            open++;
        } else {
            if (open > 0) open--;
            else close++;
        }
    }
    return (open + 1) / 2 + (close + 1) / 2;
}




/* Problem 2: Count and Say sequence */
string countAndSay(int n) {
    if (n == 1) return "1";
    string prev = countAndSay(n - 1), result;
    int count = 1;
    
    for (int i = 0; i < prev.size(); i++) {
        if (i + 1 < prev.size() && prev[i] == prev[i+1]) {
            count++;
        } else {
            result += to_string(count) + prev[i];
            count = 1;
        }
    }
    return result;
}




/* Problem 3: Shortest Palindrome */
string shortestPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    string combined = s + "#" + rev;
    vector<int> lps(combined.size(), 0);
    
    for (int i = 1; i < combined.size(); i++) {
        int len = lps[i-1];
        while (len > 0 && combined[i] != combined[len]) {
            len = lps[len-1];
        }
        if (combined[i] == combined[len]) len++;
        lps[i] = len;
    }
    return rev.substr(0, s.size() - lps.back()) + s;
}




/* Problem 4: Count Palindromic Subsequences */
int countPalindromicSubsequences(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j] + dp[i][j-1] + 1;
            } else {
                dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
            }
        }
    }
    return dp[0][n-1];
}




/* Problem 5: Longest Happy Prefix */
string longestHappyPrefix(string s) {
    int n = s.size();
    vector<int> lps(n, 0);
    
    for (int i = 1; i < n; i++) {
        int len = lps[i-1];
        while (len > 0 && s[i] != s[len]) {
            len = lps[len-1];
        }
        if (s[i] == s[len]) len++;
        lps[i] = len;
    }
    return s.substr(0, lps.back());
}