// orz
// 141. Linked List Cycle · LeetCode · Easy
//
// Question:
// given head, the head of a linked list, decide whether the list has a cycle in it.
// there is a cycle if some node can be reached again by following next pointers.
// (pos, the index the tail connects to, is only used by the judge to build the list,
// it is not passed in.) return true if there is a cycle, otherwise false.
// Example 1: head = [3,2,0,-4], pos = 1  -> true   (the tail connects to node 1)
// Example 2: head = [1,2], pos = 0       -> true   (the tail connects to node 0)
// Example 3: head = [1], pos = -1        -> false  (no cycle)
// Constraints: 0 <= n <= 10^4, -10^5 <= Node.val <= 10^5, pos is -1 or a valid index
// Follow up: can you solve it using O(1) (i.e. constant) memory? -> done here, Floyd.
//
// 1. Mathematical statement
//    walk x0 = head, x(k + 1) = next of xk. either some xk is NULL (the list ends),
//    or the walk never ends, which with n nodes means some node repeats: xi = xj with i < j.
//    answer true exactly in the second case.
//
// 2. Brute force
//    walk the list and put every node pointer in a set. a node already in the set -> cycle.
//    reach NULL -> no cycle. O(n) time but O(n) extra memory, the follow-up bans it.
//
// 3. What the brute force wastes
//    the set remembers every node ever seen, only to answer one yes / no question:
//    "does the walk come back?". that can be seen without remembering anything.
//
// 4. Key breaking point
//    two runners on a track: slow moves 1 node per turn, fast moves 2 nodes per turn.
//    if the track ends, fast falls off the end first. if the track has a loop,
//    both get stuck in the loop and fast laps slow: they land on the same node.
//    this is Floyd's tortoise and hare. it needs two pointers only.
//
// 5. Method
//    step 1 : slow = head, fast = head.
//    step 2 : while fast and fast->next are not NULL (so fast can make its 2 steps):
//             slow = slow->next, fast = fast->next->next.
//    step 3 : after the move, if slow == fast, they met inside a cycle -> return true.
//    step 4 : the loop ended, so fast reached NULL, the list ends -> return false.
//
// 6. Why it works
//    no cycle: fast only moves forward, so it hits NULL within n / 2 turns, and slow
//    (always behind fast) can never be on the same node. -> false, correct.
//    cycle of length c, entered after t nodes:
//      - after t turns slow is inside the cycle, and fast (2t steps) is inside too.
//      - let d = how many steps fast is behind slow along the cycle, 0 <= d < c.
//      - each turn slow moves 1 and fast moves 2, so the gap d shrinks by exactly 1.
//        it cannot jump over 0, because it only goes down 1 at a time.
//      - after d more turns d = 0: same node -> true.
//    so they meet within t + c <= n turns.
//    time O(n), extra space O(1): two pointers.
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
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        // step 1 : both runners start at head
        ListNode* slow = head ;
        ListNode* fast = head ;
        // step 2 : slow moves 1, fast moves 2, while fast can still make 2 steps
        while(fast != NULL && fast->next != NULL)
        {
            slow = slow->next ;
            fast = fast->next->next ;
            // step 3 : fast caught up with slow, so they are going round a cycle
            if(slow == fast)
            {
                return true ;
            }
        }
        // step 4 : fast fell off the end, the list ends
        return false ;
    }
};
