#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

struct ListNode{
    int data;
    int val;
    ListNode* prev;
    ListNode* next;
};

/*Problem 1: Reversing a Linked List*/
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *curr = head, *next = nullptr;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}



/*Problem 2: Segregate Even and Odd Nodes and produce them as even first then odd*/
ListNode* segregateEvenOdd(ListNode* head) {
    ListNode evenDummy, oddDummy;
    ListNode *evenTail = &evenDummy, *oddTail = &oddDummy;
    while (head) {
        if (head->val % 2 == 0) {
            evenTail->next = head;
            evenTail = evenTail->next;
        } else {
            oddTail->next = head;
            oddTail = oddTail->next;
        }
        head = head->next;
    }
    evenTail->next = oddDummy.next;
    oddTail->next = nullptr;
    return evenDummy.next;
}




/*Problem 3: Delete All Occurrences in a Doubly Linked List*/
ListNode* deleteAllOccurrences(ListNode* head, int target) {
    ListNode *curr = head;
    while (curr) {
        if (curr->data == target) {
            if (curr->prev) curr->prev->next = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            if (curr == head) head = curr->next;
        }
        curr = curr->next;
    }
    return head;
}



/*Problem 4: Reverse Linked List in Groups of Size k. If a remainder is there, leave it untouched*/
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode *curr = head;
    int count = 0;
    while (curr && count < k) {
        curr = curr->next;
        count++;
    }
    if (count == k) {
        curr = reverseKGroup(curr, k);
        while (count--) {
            ListNode *tmp = head->next;
            head->next = curr;
            curr = head;
            head = tmp;
        }
        head = curr;
    }
    return head;
}




/*Problem 5: Sort a Linked List*/
ListNode* sortLinkedList(ListNode* head) {
    if (!head || !head->next) return head;
    vector<int> vals;
    ListNode* curr = head;
    while (curr) {
        vals.push_back(curr->val);
        curr = curr->next;
    }
    sort(vals.begin(), vals.end());
    curr = head;
    for (int val : vals) {
        curr->val = val;
        curr = curr->next;
    }
    return head;
}
