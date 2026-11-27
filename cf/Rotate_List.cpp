// orz
// 61. Rotate List · LeetCode · Medium
//
// Question:
// given the head of a linked list, rotate the list to the right by k places.
// (one rotation moves the last node to the front.)
// Example 1: head = [1,2,3,4,5], k = 2 -> [4,5,1,2,3]
// Example 2: head = [0,1,2], k = 4     -> [2,0,1]
// Constraints: 0 <= n <= 500, -100 <= Node.val <= 100, 0 <= k <= 2 * 10^9
//
// 1. Mathematical statement
//    list a1 .. an. output a(n - r + 1) .. an, a1 .. a(n - r), where r = k % n.
//
// 2. Brute force
//    k times: walk to the last node and move it to the front. O(n) per rotation,
//    O(n * k) total, k = 2 * 10^9 and n = 500 gives 10^12. dead.
//
// 3. What the brute force wastes
//    n rotations give the same list back, so all but k % n rotations are useless.
//    and r single rotations do the same as cutting the list once.
//
// 4. Key breaking point
//    rotating right by r = cut after the first n - r nodes and swap the two pieces:
//    the old last node points to the old head, node n - r becomes the new last node.
//    only three arrows change.
//
// 5. Method
//    step 1 : dummy -> head, so position 0 exists.
//    step 2 : last = dummy, walk to the last node, counting n.
//    step 3 : n = 0 -> return head (nothing to rotate). r = k % n. r = 0 -> return head.
//    step 4 : newtail = dummy, walk n - r steps. now newtail is at position n - r.
//    step 5 : newhead = newtail->next (position n - r + 1).
//             newtail->next = NULL, last->next = head (old head behind the old last).
//    step 6 : return newhead.
//
// 6. Why it works
//    after step 5 the list is newhead = a(n - r + 1) .. an = last -> a1 .. a(n - r) = newtail -> NULL,
//    exactly the statement. 1 <= r <= n - 1 here, so newtail is not last and newhead is not NULL.
//    time O(n) (two walks), extra space O(1). k is never looped over, only k % n.
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
    ListNode* rotateRight(ListNode* head, int k) {
        // step 1 : dummy node in front of head
        ListNode* dummy = new ListNode(0) ;
        dummy->next = head ;
        // step 2 : find the last node and count n
        ListNode* last = dummy ;
        ll n = 0 ;
        while(last->next != NULL)
        {
            last = last->next ;
            n++ ;
        }
        // step 3 : only k % n rotations matter
        if(n == 0)
        {
            return head ;
        }
        ll r = k % n ;
        if(r == 0)
        {
            return head ;
        }
        // step 4 : newtail = the node at position n - r
        ListNode* newtail = dummy ;
        for(ll i = 0 ; i < n - r ; i++)
        {
            newtail = newtail->next ;
        }
        // step 5 : cut after newtail, hang the old head behind the old last
        ListNode* newhead = newtail->next ;
        newtail->next = NULL ;
        last->next = head ;
        // step 6
        return newhead ;
    }
};
