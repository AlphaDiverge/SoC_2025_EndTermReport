#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>
#include <stack>
using namespace std;

/*Problem 1: Removing k digits from a number to form the least possible number*/
string removeKdigits(string num, int k) {
    stack<char> st;
    for(char c : num) {
        while(!st.empty() && k > 0 && st.top() > c) {
            st.pop();
            k--;
        }
        st.push(c);
    }
    while(k-- > 0) st.pop();
    string res;
    while(!st.empty()) {
        res += st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());

    int i = 0;
    while(i < res.size() && res[i] == '0') i++;
    return (i == res.size()) ? "0" : res.substr(i);
}
//The last 3 lines are to remove zeroes, which i understood only after running few testcases.
//The substr takes the substring from the first non-zero element as i defines that position.
//The other parts of the code are quite easy. It just compares the to be added digit and top digit and compares them and keeps the lowest number possible.



/*Problem 2: Asteroid collisions. Signs represent direction. If same size, they get destroyed and if different sizes, the smaller one gets destroyed*/
//It just works by pushing asteroids onto the stack where if a negative one if encountered, a while loop triggers and goes on until the negative asteroid gets destroyed or all positive ones against it get destroyed.
vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;
    for(int a : asteroids) {
        bool exploded = false;
        while(!st.empty() && st.top() > 0 && a < 0) {
            if(st.top() < -a) {
                st.pop();
                continue;
            } else if(st.top() == -a) {
                st.pop();
            }
            exploded = true;
            break;
        }
        if(!exploded) st.push(a);
    }
    vector<int> res(st.size());
    for(int i = res.size()-1; i >= 0; i--) {
        res[i] = st.top();
        st.pop();
    }
    return res;
}




/*Problem 3: Next Greater element in clockwise for each element in an array. If none, -1*/
//This is one of the problems I tried bt couldnt get it fully, hence i did take some external help.
vector<int> nextGreaterElements(vector<int>& nums) {
    stack<int> st;
    vector<int> res(nums.size(), -1);
    for(int i = 0; i < nums.size(); i++) {
        while(!st.empty() && nums[st.top()] < nums[i]) {
            res[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}



/*Problem 4: Max number seen by a sliding window sliding from left to right of size k*/
//I found a normal solution without stacks or queues but it was not optimized enough.
//When i looked at the solution provided, I involved deques. This was not something that was mentioned in the theory, but i found out that it is quite important.
//Hence, even though the below solution is not mine, I am still including it, because it involves a special queue which can have insertions and deletions from both ends.
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> res;
    for(int i = 0; i < nums.size(); i++) {
        if(!dq.empty() && dq.front() == i-k) dq.pop_front();
        while(!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if(i >= k-1) res.push_back(nums[dq.front()]);
    }
    return res;
}




/*Problem 5: Largest rectangle area in a Histogram*/
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int max_area = 0;
    heights.push_back(0); // Sentinel value
    for(int i = 0; i < heights.size(); i++) {
        while(!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            int w = st.empty() ? i : i - st.top() - 1;
            max_area = max(max_area, h * w);
        }
        st.push(i);
    }
    return max_area;
}
//This was rather easier to do as a I had done a rather similar question to this.