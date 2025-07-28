#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

/*Problem 1: Square Root using Binary Search*/
int sqrt(int n) {
    if (n == 0) return 0;
    int left = 1, right = n, ans;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid <= n / mid) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}
//This works by moving the mid in the opp direction if the sqrt value is passed or not.


/*Problem 2: Smallest Divisor which divides all elements in an array and the sum of the division is lesser than the given Threshold*/
int smallestDivisor(vector<int>& nums, int threshold) {
    int left = 1;
    int right = *max_element(nums.begin(), nums.end());
    while (left < right) {
        int mid = left + (right - left) / 2;
        int sum = 0;
        for (int num : nums) {
            sum += num / mid;
            if (num % mid != 0) sum++;
        }
        if (sum > threshold) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}



/*Problem 3: Row with max no.of ones*/
int rowWithMax1s(vector<vector<int>>& mat) {
    int max_row = -1, max_count = 0;
    for (int i = 0; i < mat.size(); i++) {
        int left = 0, right = mat[i].size() - 1;
        int first_one = mat[i].size();
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mat[i][mid] == 1) {
                first_one = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        int count = mat[i].size() - first_one;
        if (count > max_count) {
            max_count = count;
            max_row = i;
        }
    }
    return max_row;
}



/*
Problem 4: Given an array ‘arr of integer numbers, ‘ar[i]’ represents the number of pages in the ‘i-th’ book. There are a ‘m’ number of students, and the task is to allocate all the books to the students.
Allocate books in such a way that:

Each student gets at least one book.
Each book should be allocated to only one student.
Book allocation should be in a contiguous manner.
*/
bool isPossible(vector<int>& arr, int m, int mid) {
    int students = 1, sum = 0;
    for (int num : arr) {
        if (sum + num > mid) {
            students++;
            sum = num;
        } else {
            sum += num;
        }
    }
    return students <= m;
}

int findPages(vector<int>& arr, int m) {
    if (m > arr.size()) return -1;
    int left = *max_element(arr.begin(), arr.end());
    int right = accumulate(arr.begin(), arr.end(), 0);
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (isPossible(arr, m, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
//The accumulate function provides a way to easily add up all the elements from the iterator's start to finish.




/*Problem 5: n^th root of a number*/
int nthRoot(int n, int m) {
    if (m == 0) return 0;
    int left = 1, right = m;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (pow(mid, n) == m) {
            return mid;
        } else if (pow(mid, n) < m) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}