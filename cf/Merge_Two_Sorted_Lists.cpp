// orz
// 21. Merge Two Sorted Lists · LeetCode · Easy
//
// Question:
// given the heads of two sorted (non-decreasing) linked lists list1 and list2,
// merge them into one sorted list made by splicing together the nodes of the
// two lists, and return the head of the merged list.
// Example 1: list1 = [1,2,4], list2 = [1,3,4] -> [1,1,2,3,4,4]
// Example 2: list1 = [], list2 = []           -> []
// Example 3: list1 = [], list2 = [0]          -> [0]
// Constraints: 0 <= nodes in each list <= 50, -100 <= Node.val <= 100,
//              both lists are sorted in non-decreasing order
//
// 1. Mathematical statement
//    a1 <= a2 <= .. <= am and b1 <= b2 <= .. <= bn.
//    chain all m + n nodes into one list c1 <= c2 <= .. <= c(m + n), by changing next pointers only.
//
// 2. Brute force
//    m + n times: scan every node not used yet, take the smallest, hang it at the end.
//    O((m + n)^2).
//
// 3. What the brute force wastes
//    it scans everything to find the smallest node left, but both lists are sorted,
//    so the smallest node left is always one of the two heads.
//
// 4. Key breaking point
//    compare only the two heads, take the smaller one: the merge step of merge sort.
//    a dummy node in front means the first taken node needs no special case.
//
// 5. Method
//    step 1 : dummy node, tail = dummy (last node of the merged list so far).
//    step 2 : while both lists are non-empty, take the smaller head (list1 on a tie),
//             hang it after tail, move that list one node forward.
//    step 3 : one list is empty now. the other one is sorted and every node in it is
//             >= everything taken, so hang the whole rest after tail at once.
//    step 4 : return dummy->next.
//
// 6. Why it works
//    each step of step 2 takes the smallest node still left (it is one of the two heads),
//    so the merged list grows in sorted order. step 3 adds an already sorted tail whose
//    nodes are all >= the last taken node.
//    time O(m + n), extra space O(1): only the dummy and a few pointers.
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
#define fr first
#define sc second
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define mp make_pair
#define PI acos(-1)
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define pll pair<ll,ll>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // step 1 : dummy node, tail = last node of the merged list
        ListNode* dummy = new ListNode(0) ;
        ListNode* tail = dummy ;
        // step 2 : take the smaller of the two heads
        while(list1 != NULL && list2 != NULL)
        {
            if(list1->val <= list2->val)
            {
                tail->next = list1 ;
                tail = list1 ;
                list1 = list1->next ;
            }
            else
            {
                tail->next = list2 ;
                tail = list2 ;
                list2 = list2->next ;
            }
        }
        // step 3 : hang the leftover list whole
        if(list1 != NULL)
        {
            tail->next = list1 ;
        }
        else
        {
            tail->next = list2 ;
        }
        // step 4
        return dummy->next ;
    }
};
