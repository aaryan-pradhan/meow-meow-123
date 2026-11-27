// orz
// 82. Remove Duplicates from Sorted List II · LeetCode · Medium
//
// Question:
// given the head of a sorted linked list, delete all nodes that have duplicate numbers,
// leaving only the numbers that appear exactly once in the original list.
// return the linked list, still sorted.
// Example 1: head = [1,2,3,3,4,4,5] -> [1,2,5]
// Example 2: head = [1,1,1,2,3]     -> [2,3]
// Constraints: 0 <= n <= 300, -100 <= Node.val <= 100, the list is sorted in ascending order
//
// 1. Mathematical statement
//    cnt(v) = how many nodes hold value v. keep a node exactly when cnt(its value) = 1,
//    in the original order.
//
// 2. Brute force
//    for every node, walk the whole list to count its value, keep it if the count is 1.
//    O(n^2). (a map of counts makes it O(n) but costs O(n) extra memory.)
//
// 3. What the brute force wastes
//    the list is sorted, so all the copies of a value sit next to each other in one run.
//    cnt(v) is just the length of v's run, no need to walk the whole list for it.
//
// 4. Key breaking point
//    walk the list run by run. a run of length 1 is kept, a longer run is dropped whole.
//    the head itself may be dropped, so build the answer behind a dummy node.
//
// 5. Method
//    step 1 : dummy node, tail = dummy (last kept node), cur = head (start of the current run).
//    step 2 : end = cur, move end forward while end->next has the same value as cur.
//             now the run is cur .. end.
//    step 3 : if end == cur, the run has length 1: tail->next = cur, tail = cur.
//             else the value repeats, skip the whole run.
//    step 4 : cur = end->next, the start of the next run. repeat from step 2 while cur != NULL.
//    step 5 : tail->next = NULL, because the last kept node may still point into a dropped run.
//    step 6 : return dummy->next.
//
// 6. Why it works
//    sorted means equal values form one run, so "run length 1" is exactly "cnt(v) = 1".
//    kept nodes are appended in the order they are met, so the answer stays sorted.
//    step 5 cuts off anything after the last kept node.
//    time O(n): every node is passed once by end. extra space O(1).
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
    ListNode* deleteDuplicates(ListNode* head) {
        // step 1 : dummy node, tail = last kept node
        ListNode* dummy = new ListNode(0) ;
        ListNode* tail = dummy ;
        ListNode* cur = head ;
        while(cur != NULL)
        {
            // step 2 : the run of cur's value is cur .. end
            ListNode* end = cur ;
            while(end->next != NULL && end->next->val == cur->val)
            {
                end = end->next ;
            }
            // step 3 : keep a run of length 1, a longer run is skipped whole
            if(end == cur)
            {
                tail->next = cur ;
                tail = cur ;
            }
            // step 4 : start of the next run
            cur = end->next ;
        }
        // step 5 : cut off whatever was after the last kept node
        tail->next = NULL ;
        // step 6
        return dummy->next ;
    }
};
