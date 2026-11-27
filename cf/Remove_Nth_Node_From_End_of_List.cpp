// orz
// 19. Remove Nth Node From End of List · LeetCode · Medium
//
// Question:
// given the head of a linked list, remove the n-th node from the end of the list
// and return its head.
// Example 1: head = [1,2,3,4,5], n = 2 -> [1,2,3,5]
// Example 2: head = [1], n = 1         -> []
// Example 3: head = [1,2], n = 1       -> [1]
// Constraints: 1 <= sz <= 30 (sz = number of nodes), 0 <= Node.val <= 100, 1 <= n <= sz
// Follow up: could you do this in one pass? -> done here, one pass.
//
// 1. Mathematical statement
//    list a1 .. aL. the n-th node from the end is a(L - n + 1).
//    make a(L - n) point to a(L - n + 2), where a0 is a dummy so that L - n = 0 also works.
//
// 2. Brute force
//    pass 1: walk the list to count L. pass 2: walk L - n steps from the dummy to
//    reach a(L - n), and skip its next. O(L), but two passes.
//
// 3. What the brute force wastes
//    pass 2 walks again over the first L - n nodes that pass 1 already walked over.
//    it only needs to know when L - n steps are done, i.e. when n steps are left.
//
// 4. Key breaking point
//    a ruler of fixed length n: keep a back pointer exactly n nodes behind a front pointer.
//    when the front pointer stands on the last node aL, the back pointer stands on a(L - n),
//    which is the node pass 2 was looking for.
//
// 5. Method
//    step 1 : dummy -> head, so position 0 exists and removing the head needs no special case.
//    step 2 : front = dummy, move front n steps. now front is at position n.
//    step 3 : back = dummy (position 0). the gap is n.
//    step 4 : while front->next is not NULL, move both one step. the gap stays n.
//             at the end front is at position L, so back is at position L - n.
//    step 5 : back->next = back->next->next (skip the n-th node from the end).
//    step 6 : return dummy->next, because the head itself goes when n = L.
//
// 6. Why it works
//    front - back = n all the time. front stops at position L, so back stops at L - n,
//    the node right before a(L - n + 1). n <= L, so step 2 never walks off the list,
//    and back->next exists in step 5.
//    time O(L) in one pass, extra space O(1).
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // step 1 : dummy node in front of head
        ListNode* dummy = new ListNode(0) ;
        dummy->next = head ;
        // step 2 : front goes n steps ahead
        ListNode* front = dummy ;
        for(ll i = 0 ; i < n ; i++)
        {
            front = front->next ;
        }
        // step 3 : back starts at the dummy, n behind front
        ListNode* back = dummy ;
        // step 4 : slide the ruler until front is the last node
        while(front->next != NULL)
        {
            front = front->next ;
            back = back->next ;
        }
        // step 5 : back is right before the node to remove
        back->next = back->next->next ;
        // step 6
        return dummy->next ;
    }
};
