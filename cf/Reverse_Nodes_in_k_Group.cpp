// orz
// 25. Reverse Nodes in k-Group · LeetCode · Hard
//
// Question:
// given the head of a linked list, reverse the nodes of the list k at a time and
// return the modified list. k is a positive integer <= the length of the list.
// if the number of nodes is not a multiple of k, the nodes left at the end stay as they are.
// you may not change the values in the nodes, only the nodes themselves.
// Example 1: head = [1,2,3,4,5], k = 2 -> [2,1,4,3,5]
// Example 2: head = [1,2,3,4,5], k = 3 -> [3,2,1,4,5]
// Constraints: 1 <= k <= n <= 5000, 0 <= Node.val <= 1000
// Follow up: can you solve it in O(1) extra memory space? -> done here.
//
// 1. Mathematical statement
//    cut a1 .. an into blocks of k: [a1 .. ak], [a(k + 1) .. a2k], .., and a last part of
//    n % k nodes. reverse every full block in place, keep the last part, keep the block order.
//
// 2. Brute force
//    copy the values into an array, reverse each full block of the array, write the values
//    back. O(n) time but O(n) extra memory, and it changes values, both banned.
//
// 3. What the brute force wastes
//    it moves the values out and back when only the arrows inside each block need to turn around.
//
// 4. Key breaking point
//    each full block is Reverse Linked List II on that block: the block touches the rest
//    through two arrows only, (node before -> first) and (last -> node after).
//    turn the inside arrows with the three-pointer reverse, fix those two arrows.
//    after that the old first node is the block's last node, so it is the
//    "node before" of the next block. a dummy node gives the first block a node before.
//
// 5. Method
//    step 1 : dummy -> head, before = dummy (the node before the current block).
//    step 2 : count up to k nodes after before. fewer than k -> they stay as they are, stop.
//    step 3 : first = before->next. after reversing, first becomes the LAST node of the block.
//    step 4 : reverse k nodes: nxt = cur->next, cur->next = prev, prev = cur, cur = nxt.
//             after the loop prev = the new block head, cur = the node right after the block.
//    step 5 : stitch the two outside arrows: before->next = prev, first->next = cur.
//    step 6 : before = first, go back to step 2 for the next block.
//    step 7 : return dummy->next, because the head changes (k >= 2) or stays (k = 1).
//
// 6. Why it works
//    every full block gets its inside arrows turned exactly once (step 4) and its two border
//    arrows fixed (step 5), the same argument as Reverse Linked List II. step 6 moves before
//    to the true node before the next block. the last part is never touched because step 2
//    stops before it.
//    time O(n): each node is counted once in step 2 and reversed once in step 4.
//    extra space O(1): a few pointers.
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        // step 1 : dummy node in front of head
        ListNode* dummy = new ListNode(0) ;
        dummy->next = head ;
        ListNode* before = dummy ;
        while(true)
        {
            // step 2 : are there k nodes after before?
            ListNode* walk = before ;
            ll cnt = 0 ;
            while(cnt < k && walk->next != NULL)
            {
                walk = walk->next ;
                cnt++ ;
            }
            if(cnt < k)
            {
                break ;
            }
            // step 3 : first node of the block, it ends up last
            ListNode* first = before->next ;
            // step 4 : three-pointer reverse of k nodes
            ListNode* prev = NULL ;
            ListNode* cur = first ;
            for(ll i = 0 ; i < k ; i++)
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
            // step 6 : the old first is the node before the next block
            before = first ;
        }
        // step 7
        return dummy->next ;
    }
};
