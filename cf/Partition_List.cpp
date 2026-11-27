// orz
// 86. Partition List · LeetCode · Medium
//
// Question:
// given the head of a linked list and a value x, partition it so that all nodes less
// than x come before the nodes greater than or equal to x. keep the original relative
// order of the nodes inside each of the two parts.
// Example 1: head = [1,4,3,2,5,2], x = 3 -> [1,2,2,4,3,5]
// Example 2: head = [2,1], x = 2         -> [1,2]
// Constraints: 0 <= n <= 200, -100 <= Node.val <= 100, -200 <= x <= 200
//
// 1. Mathematical statement
//    S = the nodes with val < x in list order, B = the nodes with val >= x in list order.
//    output S followed by B (a stable partition), by changing next pointers only.
//
// 2. Brute force
//    walk once and copy the values < x into new nodes, walk again and copy the values >= x,
//    return the new list. O(n) time but O(n) new nodes, when every node already exists.
//
// 3. What the brute force wastes
//    it builds a second list. the nodes are already there, only their arrows have to change.
//
// 4. Key breaking point
//    build the two parts S and B at the same time as two separate chains, each behind
//    its own dummy node. every node goes to the end of its chain, in the order it is met,
//    so each chain keeps the original order. then hang B behind S.
//
// 5. Method
//    step 1 : two dummy nodes small and big, tails stail = small, btail = big.
//    step 2 : walk cur over the list. val < x -> hang cur after stail, else after btail.
//             then cur = cur->next (cur's own next is not touched by hanging it).
//    step 3 : btail->next = NULL, because the last big node may still point at a small node.
//    step 4 : stail->next = big->next (glue B behind S).
//    step 5 : return small->next.
//
// 6. Why it works
//    every node lands in exactly one chain, at its end, in the order of the walk, so S and B
//    each keep their relative order. step 3 ends B, step 4 joins S and B.
//    time O(n), extra space O(1): two dummies and a few pointers.
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
    ListNode* partition(ListNode* head, int x) {
        // step 1 : one dummy per part, tails = last node of each part
        ListNode* small = new ListNode(0) ;
        ListNode* big = new ListNode(0) ;
        ListNode* stail = small ;
        ListNode* btail = big ;
        // step 2 : every node goes to the end of its part
        ListNode* cur = head ;
        while(cur != NULL)
        {
            if(cur->val < x)
            {
                stail->next = cur ;
                stail = cur ;
            }
            else
            {
                btail->next = cur ;
                btail = cur ;
            }
            cur = cur->next ;
        }
        // step 3 : end the big part
        btail->next = NULL ;
        // step 4 : big part behind the small part
        stail->next = big->next ;
        // step 5
        return small->next ;
    }
};
