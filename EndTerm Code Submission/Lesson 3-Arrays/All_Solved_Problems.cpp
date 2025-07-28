#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

/*Problem 1: Given an array consisting of only 0s, 1s, and 2s. Write a program to in-place sort the array without using inbuilt sort functions. ( Expected: Single pass-O(N) and constant space)*/
void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}
//This is a famous answer actually and widely used as an example.



/*Problem 2: Find the contiguous subarray with the largest sum.*/
int maxSubArray(vector<int>& nums) {
    int max_sum = nums[0];
    int current_sum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        current_sum = max(nums[i], current_sum + nums[i]);
        max_sum = max(max_sum, current_sum);
    }
    return max_sum;
}
//This is a problem which is known to me from the CS101 problems.
//But while solving this on the website, I found its name to be Kadane's Algorithm.



/*Problem 3: Rotate an N×N matrix 90 degrees clockwise.*/
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}
//The reverse function is a built in function in the algorithm library.



/*Problem 4: Print a matrix in spiral order.*/
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) result.push_back(matrix[top][i]);
        top++;
        for (int i = top; i <= bottom; i++) result.push_back(matrix[i][right]);
        right--;
        if (top <= bottom) {
            for (int i = right; i >= left; i--) result.push_back(matrix[bottom][i]);
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--) result.push_back(matrix[i][left]);
            left++;
        }
    }
    return result;
}
//A similar question was done in my CS101 lab too.



/*Problem 5: Find all unique quadruplets in an array that sum to a target value.*/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    set<vector<int>> result;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                for (int l = k+1; l < n; l++) {
                    long long sum = (long long)nums[i] + nums[j] + nums[k] + nums[l];  // Avoid overflow
                    if (sum == target) {
                        result.insert({nums[i], nums[j], nums[k], nums[l]});
                    }
                }
            }
        }
    }

    return vector<vector<int>>(result.begin(), result.end());
}
//This answer has a high time complexity but this was the best i could do.
//The set is a data type that stores unique elements only and disallows repititions.
//Also the for loop structure prevent permutations of the same structure, due to the limits and sorting.




/*Problem 6: Generate Pascal's Triangle up to N rows.*/
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> triangle;
    for (int i = 0; i < numRows; i++) {
        vector<int> row(i + 1, 1);
        for (int j = 1; j < i; j++) {
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
        triangle.push_back(row);
    }
    return triangle;
}
//This stores the values in the proper vector values, to get the exact triangular form with spaces, further spacing during printing might be needed.
//There is another easier way to do this, that is my listing combinations in a loop. This is an easier solution, hence I did not write this.