// orz
// 23. Merge k Sorted Lists · LeetCode · Hard
//
// Question:
// you are given an array of k linked lists, each sorted in ascending order.
// merge all of them into one sorted linked list and return it.
// Example 1: lists = [[1,4,5],[1,3,4],[2,6]] -> [1,1,2,3,4,4,5,6]
// Example 2: lists = []                      -> []
// Example 3: lists = [[]]                    -> []
// Constraints: 0 <= k <= 10^4, 0 <= lists[i].length <= 500, -10^4 <= lists[i][j] <= 10^4,
//              every lists[i] is sorted ascending, the total number of nodes N <= 10^4.
//
// 1. Mathematical statement
//    relink all N nodes of the k lists into one list whose values are non-decreasing.
//
// 2. Brute force
//    to pick each next node, look at the front of all k lists and take the smallest.
//    O(k) per node, O(N * k) = 10^8 in the worst case. too slow, and most of that look is repeated.
//
// 3. What the brute force wastes
//    after taking one node only ONE front changes (the list it came from), but the brute force
//    compares all k fronts again from scratch.
//
// 4. Key breaking point
//    keep the k fronts in a min-heap of (value , list index). the smallest front is the top,
//    and after taking it only one new front (its next node) goes in. O(log k) per node instead of O(k).
//    the nodes themselves are relinked with my dummy + tail, no values are copied.
//
// 5. Method
//    step 1 : push (lists[i]->val , i) for every non-empty list. lists[i] is the front of list i from now on.
//    step 2 : dummy node, tail = dummy (last node of the merged list so far).
//    step 3 : while the heap is not empty : pop (val , i). node = lists[i], move lists[i] to node->next.
//             tail->next = node, tail = node.
//    step 4 : if lists[i] is not NULL, push its new front (lists[i]->val , i).
//    step 5 : return dummy->next. the last node taken is the end of some list, so its next is already NULL.
//
// 6. Why it works
//    every list is sorted, so the smallest node not yet taken is the front of some list, and the heap
//    holds exactly the fronts. taking the heap top each time gives the nodes in sorted order.
//    time O(N log k), extra space O(k) for the heap.
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ll k = lists.size() ;
        // step 1 : this stores (value of the front node , list index) for every non-empty list, smallest on top
        priority_queue < pll , vector < pll > , greater < pll > > pq ;
        for(ll i = 0 ; i < k ; i++)
        {
            if(lists[i] != NULL)
            {
                pq.push(mp(lists[i]->val , i)) ;
            }
        }
        // step 2 : dummy node
        ListNode* dummy = new ListNode(0) ;
        ListNode* tail = dummy ;
        while(!pq.empty())
        {
            // step 3 : take the smallest front
            pll top = pq.top() ;
            pq.pop() ;
            ll i = top.sc ;
            ListNode* node = lists[i] ;
            lists[i] = node->next ;
            tail->next = node ;
            tail = node ;
            // step 4 : list i has a new front
            if(lists[i] != NULL)
            {
                pq.push(mp(lists[i]->val , i)) ;
            }
        }
        // step 5
        return dummy->next ;
    }
};
