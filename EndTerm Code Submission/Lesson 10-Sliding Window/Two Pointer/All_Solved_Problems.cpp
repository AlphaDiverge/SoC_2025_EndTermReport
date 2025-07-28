#include <unordered_set>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <set>
#include <numeric>
using namespace std;


// Below are some of the problem I have attempted. I failed at solving some and some i did succeed.


/*Problem 1: Given a string s, find the length of the longest substring without repeating characters.*/
int lengthOfLongestSubstring(string s) {
    unordered_set<char> window;
    int left = 0, max_len = 0;
    for (int right = 0; right < s.size(); right++) {
        while (window.count(s[right])) {
            window.erase(s[left]);
            left++;
        }
        window.insert(s[right]);
        max_len = max(max_len, right - left + 1);
    }
    return max_len;
}


/*Problem 2: Given a binary array nums and integer goal, return the number of subarrays with sum goal.*/
int numSubarraysWithSum(vector<int>& nums, int goal) {
    return atMost(nums, goal) - (goal > 0 ? atMost(nums, goal - 1) : 0);
}

int atMost(vector<int>& nums, int goal) {
    int left = 0, count = 0, sum = 0;
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        while (left <= right && sum > goal) {
            sum -= nums[left];
            left++;
        }
        count += right - left + 1;
    }
    return count;
}


/*Problem 3: Find the longest subarray with at most 2 distinct elements.*/
int totalFruit(vector<int>& fruits) {
    unordered_map<int, int> basket;
    int left = 0, max_fruits = 0;
    for (int right = 0; right < fruits.size(); right++) {
        basket[fruits[right]]++;
        while (basket.size() > 2) {
            basket[fruits[left]]--;
            if (basket[fruits[left]] == 0) basket.erase(fruits[left]);
            left++;
        }
        max_fruits = max(max_fruits, right - left + 1);
    }
    return max_fruits;
}



/*Problem 4: Given a binary array nums and integer k, flip at most k 0s to 1s to get the longest consecutive 1s*/
int longestOnes(vector<int>& nums, int k) {
    int left = 0, max_ones = 0, zero_count = 0;
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) zero_count++;
        while (zero_count > k) {
            if (nums[left] == 0) zero_count--;
            left++;
        }
        max_ones = max(max_ones, right - left + 1);
    }
    return max_ones;
}



/*Problem 5: Choose k cards from either end to maximize the sum*/
int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);
    int window_sum = accumulate(cardPoints.begin(), cardPoints.begin() + n - k, 0);
    int min_sum = window_sum;
    for (int left = 0, right = n - k; right < n; left++, right++) {
        window_sum += cardPoints[right] - cardPoints[left];
        min_sum = min(min_sum, window_sum);
    }
    return total - min_sum;
}