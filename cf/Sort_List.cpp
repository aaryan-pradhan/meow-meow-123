// orz
// 148. Sort List · LeetCode · Medium
//
// Question:
// given the head of a linked list, return the list after sorting it in ascending order.
// Example 1: head = [4,2,1,3]      -> [1,2,3,4]
// Example 2: head = [-1,5,3,4,0]   -> [-1,0,3,4,5]
// Example 3: head = []             -> []
// Constraints: 0 <= number of nodes <= 5 * 10^4, -10^5 <= Node.val <= 10^5
// Follow up: sort in O(n log n) time and O(1) memory (constant space). -> done here, bottom-up merge sort.
//
// 1. Mathematical statement
//    list a1 .. an. relink the same nodes so the values read in non-decreasing order,
//    in O(n log n) time with O(1) extra space.
//
// 2. Brute force
//    insertion sort on the list: take each node and walk the sorted part to find its place.
//    O(n^2) = 2.5 * 10^9. dead. (copying the values into a vector and sorting is O(n) extra space.)
//
// 3. What the brute force wastes
//    every insert walks the sorted part from the start again, one node at a time.
//    two sorted pieces can be joined in one walk instead (merge), never going back.
//
// 4. Key breaking point
//    merge sort on the links. the usual top-down one (find the middle, cut, recurse, merge)
//    uses O(log n) recursion stack, so it misses O(1) space. do it bottom-up instead:
//    pass 1 merges neighbour runs of 1 node into sorted runs of 2, pass 2 merges runs of 2 into
//    runs of 4, and so on, width = 1, 2, 4, .. until width >= n. no recursion, only a few pointers.
//
// 5. Method
//    step 1 : count n, the length of the list.
//    step 2 : dummy -> head, so the head can change without a special case.
//    step 3 : cut(start , k) : walk k - 1 nodes from start, set the k-th node's next to NULL,
//             return the node after it (NULL if the list ran out). this splits off a run of k nodes.
//    step 4 : merge(a , b) : the usual merge of two sorted lists into a dummy, take the smaller head
//             each time (a on ties), then hang the leftover list on the end in one splice.
//    step 5 : one pass with width w : tail = dummy (the last node of the part already merged),
//             cur = dummy->next. while cur != NULL :
//               left = cur, right = cut(left , w), cur = cut(right , w).
//               tail->next = merge(left , right), then walk tail to the end of what was just merged.
//    step 6 : run passes for w = 1, 2, 4, .. while w < n. return dummy->next.
//
// 6. Why it works
//    before the pass with width w, every block of w nodes (the last one may be shorter) is sorted.
//    the pass merges blocks two by two, so after it every block of 2w nodes is sorted.
//    once w >= n, the one block is the whole list. there are log n passes, each walks the list
//    a constant number of times: time O(n log n), extra space O(1).
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
ListNode* cut(ListNode* start , ll k)
{
    // step 3 : this keeps the first k nodes of start as their own list and returns the node after them
    ListNode* cur = start ;
    for(ll i = 1 ; i < k && cur != NULL ; i++)
    {
        cur = cur->next ;
    }
    if(cur == NULL)
    {
        return NULL ;
    }
    ListNode* rest = cur->next ;
    cur->next = NULL ;
    return rest ;
}
ListNode* merge(ListNode* a , ListNode* b)
{
    // step 4 : this merges two sorted lists into one sorted list and returns its head
    ListNode start(0) ;         // the dummy lives on the stack, so a merge allocates nothing
    ListNode* tail = &start ;
    while(a != NULL && b != NULL)
    {
        if(a->val <= b->val)
        {
            tail->next = a ;
            tail = a ;
            a = a->next ;
        }
        else
        {
            tail->next = b ;
            tail = b ;
            b = b->next ;
        }
    }
    // the leftover list is already sorted, one splice hangs it on
    if(a != NULL)
    {
        tail->next = a ;
    }
    else
    {
        tail->next = b ;
    }
    return start.next ;
}
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // step 1 : the length
        ll n = 0 ;
        ListNode* walk = head ;
        while(walk != NULL)
        {
            n++ ;
            walk = walk->next ;
        }
        // step 2 : dummy node in front of head
        ListNode* dummy = new ListNode(0) ;
        dummy->next = head ;
        // step 6 : widths 1, 2, 4, ..
        for(ll w = 1 ; w < n ; w *= 2)
        {
            // step 5 : one pass, merge the blocks of w two by two
            ListNode* tail = dummy ;     // last node of the part already merged in this pass
            ListNode* cur = dummy->next ;
            while(cur != NULL)
            {
                ListNode* left = cur ;
                ListNode* right = cut(left , w) ;
                cur = cut(right , w) ;
                tail->next = merge(left , right) ;
                while(tail->next != NULL)
                {
                    tail = tail->next ;
                }
            }
        }
        return dummy->next ;
    }
};
