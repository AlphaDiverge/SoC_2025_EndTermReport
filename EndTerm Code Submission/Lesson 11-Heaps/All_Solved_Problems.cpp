#include <unordered_set>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <set>
#include <numeric>
#include <queue>
using namespace std;

/*Problem 1: Implement a Min Heap with insert, getMin, extractMin, heapSize, isEmpty, and changeKey operations.*/
class MinHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap.size() && heap[left] < heap[smallest]) 
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest]) 
            smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void initializeHeap() {
        heap.clear();
    }

    void insert(int x) {
        heap.push_back(x);
        heapifyUp(heap.size() - 1);
    }

    int getMin() {
        return heap.empty() ? -1 : heap[0];
    }

    int extractMin() {
        if (heap.empty()) return -1;
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return minVal;
    }

    int heapSize() {
        return heap.size();
    }

    bool isEmpty() {
        return heap.empty();
    }

    void changeKey(int index, int val) {
        if (index >= heap.size()) return;
        int oldVal = heap[index];
        heap[index] = val;
        if (val < oldVal) heapifyUp(index);
        else heapifyDown(index);
    }
};




/*Problem 2: Merge k sorted linked lists into one sorted list*/
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;
    for (ListNode* list : lists) {
        if (list) minHeap.push(list);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next) minHeap.push(node->next);
    }
    return dummy.next;
}


/*Problem 3: Given an array nums, return the kth largest element in the array*/
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}



/*Problem 4: You have some sticks with positive integer lengths. You can connect any two sticks together to form a longer stick by paying a cost equal to the sum of their lengths. You must connect all the sticks into one single stick. Return the minimum cost of connecting all the sticks.*/
int connectSticks(vector<int>& sticks) {
    priority_queue<int, vector<int>, greater<int>> minHeap(sticks.begin(), sticks.end());
    int totalCost = 0;
    while (minHeap.size() > 1) {
        int a = minHeap.top(); minHeap.pop();
        int b = minHeap.top(); minHeap.pop();
        int cost = a + b;
        totalCost += cost;
        minHeap.push(cost);
    }
    return totalCost;
}



/*Problem 5: Find the top k maximum sums from combinations of elements in two arrays*/
vector<int> maxSumCombination(vector<int>& nums1, vector<int>& nums2, int k) {
    sort(nums1.rbegin(), nums1.rend());
    sort(nums2.rbegin(), nums2.rend());
    priority_queue<pair<int, pair<int, int>>> maxHeap;
    unordered_set<string> visited;
    vector<int> result;

    maxHeap.push({nums1[0] + nums2[0], {0, 0}});
    visited.insert("0,0");

    while (k-- && !maxHeap.empty()) {
        auto [sum, indices] = maxHeap.top();
        maxHeap.pop();
        result.push_back(sum);
        int i = indices.first, j = indices.second;

        if (i + 1 < nums1.size() && !visited.count(to_string(i + 1) + "," + to_string(j))) {
            maxHeap.push({nums1[i + 1] + nums2[j], {i + 1, j}});
            visited.insert(to_string(i + 1) + "," + to_string(j));
        }
        if (j + 1 < nums2.size() && !visited.count(to_string(i) + "," + to_string(j + 1))) {
            maxHeap.push({nums1[i] + nums2[j + 1], {i, j + 1}});
            visited.insert(to_string(i) + "," + to_string(j + 1));
        }
    }
    return result;
}