// orz
// 92. Reverse Linked List II · LeetCode · Medium
//
// Question:
// given the head of a singly linked list and two integers left <= right,
// reverse the nodes of the list from position left to position right
// (positions start at 1), and return the reversed list.
// Example 1: head = [1,2,3,4,5], left = 2, right = 4 -> [1,4,3,2,5]
// Example 2: head = [5], left = 1, right = 1         -> [5]
// Constraints: 1 <= n <= 500, -500 <= Node.val <= 500, 1 <= left <= right <= n
// Follow up: could you do it in one pass? -> done here, one pass.
//
// 1. Mathematical statement
//    list a1 .. an. output a1 .. a(left - 1), a(right), a(right - 1) .. a(left), a(right + 1) .. an,
//    by changing next pointers only, with O(1) extra space.
//
// 2. Brute force
//    for k = 0, 1, .. swap the values at positions left + k and right - k, walking
//    from head to find each of them. O(n) per walk, O(n^2) total, and it moves
//    values instead of nodes.
//
// 3. What the brute force wastes
//    every walk starts again from head, and it moves the values when only the
//    arrows between the nodes need to turn around.
//
// 4. Key breaking point
//    reversing a block = reversing the arrows inside it. the block touches the rest
//    of the list through only two arrows: (node before the block -> first node of the block)
//    and (last node of the block -> node after the block). reverse the inside arrows with
//    the three-pointer reverse, then fix those two arrows.
//    a dummy node in front of head makes "the node before the block" exist even when left = 1.
//
// 5. Method
//    step 1 : dummy -> head, so position 0 exists and the head needs no special case.
//    step 2 : walk before from dummy, left - 1 steps. now before is at position left - 1.
//    step 3 : first = before->next. after reversing, first becomes the LAST node of the block.
//    step 4 : reverse right - left + 1 nodes: nxt = cur->next, cur->next = prev, prev = cur, cur = nxt.
//             after the loop prev = the old node at right (the new block head),
//             cur = the node at right + 1 (NULL if right = n).
//    step 5 : stitch the two outside arrows: before->next = prev, first->next = cur.
//    step 6 : return dummy->next, because the head itself changes when left = 1.
//
// 6. Why it works
//    nodes outside [left, right] keep their arrows. inside, every arrow is turned around
//    exactly once by step 4. step 5 fixes the only two arrows that cross the block border.
//    time O(n) in one pass, extra space O(1).
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // step 1 : dummy node in front of head
        ListNode* dummy = new ListNode(0) ;
        dummy->next = head ;
        // step 2 : before = the node at position left - 1
        ListNode* before = dummy ;
        for(ll i = 1 ; i < left ; i++)
        {
            before = before->next ;
        }
        // step 3 : first node of the block, it ends up last
        ListNode* first = before->next ;
        // step 4 : three-pointer reverse of right - left + 1 nodes
        ListNode* prev = NULL ;
        ListNode* cur = first ;
        for(ll i = left ; i <= right ; i++)
        {
            ListNode* nxt = cur->next ;
            cur->next = prev ;
            prev = cur ;
            cur = nxt ;
        }
        // now prev = new head of the block, cur = node right after the block
        // step 5 : stitch the block back in
        before->next = prev ;
        first->next = cur ;
        // step 6
        return dummy->next ;
    }
};
