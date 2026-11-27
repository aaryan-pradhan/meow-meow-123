// orz
// 2. Add Two Numbers · LeetCode · Medium
//
// Question:
// given two non-empty linked lists representing two non-negative integers. the digits
// are stored in reverse order (the ones digit first) and each node holds one digit.
// add the two numbers and return the sum as a linked list in the same reverse order.
// the two numbers have no leading zeros, except the number 0 itself.
// Example 1: l1 = [2,4,3], l2 = [5,6,4]               -> [7,0,8]   (342 + 465 = 807)
// Example 2: l1 = [0], l2 = [0]                       -> [0]
// Example 3: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]     -> [8,9,9,9,0,0,0,1]
// Constraints: 1 <= nodes in each list <= 100, 0 <= Node.val <= 9
//
// 1. Mathematical statement
//    A = a0 + a1 * 10 + a2 * 10^2 + .., B = b0 + b1 * 10 + ..
//    output the digits s0, s1, .. of A + B, ones digit first.
//
// 2. Brute force
//    turn both lists into integers, add them, turn the sum back into a list.
//    100 digits means numbers up to 10^100, long long holds about 9 * 10^18. dead (overflow).
//
// 3. What the brute force wastes
//    it builds the whole number when every digit of the sum only needs the two digits
//    in the same column and the carry from the column before.
//
// 4. Key breaking point
//    this is school column addition, and the lists already start at the ones column,
//    which is exactly where column addition starts. walk both lists together, carry one number.
//
// 5. Method
//    step 1 : dummy node, tail = dummy (last node of the answer so far), carry = 0.
//    step 2 : keep going while l1 has digits, or l2 has digits, or carry is not 0.
//    step 3 : s = carry + (digit of l1, 0 if l1 ended) + (digit of l2, 0 if l2 ended),
//             and move l1 / l2 one node forward when they have one.
//    step 4 : the new digit is s % 10, hang it after tail, carry = s / 10.
//    step 5 : return dummy->next.
//
// 6. Why it works
//    column i of A + B is (ai + bi + carry_i) % 10 and sends (ai + bi + carry_i) / 10 to
//    column i + 1. step 3 and 4 do exactly that, column by column. s <= 9 + 9 + 1 = 19,
//    so carry is 0 or 1. a list that ended counts as 0 digits, and the "carry != 0"
//    in step 2 writes the last 1 (999 + 1 = 1000).
//    time O(max(m , n)), extra space O(1) besides the answer list.
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // step 1 : dummy node, tail = last node of the answer
        ListNode* dummy = new ListNode(0) ;
        ListNode* tail = dummy ;
        ll carry = 0 ;
        // step 2 : while some digit or a carry is left
        while(l1 != NULL || l2 != NULL || carry != 0)
        {
            // step 3 : this column's sum
            ll s = carry ;
            if(l1 != NULL)
            {
                s += l1->val ;
                l1 = l1->next ;
            }
            if(l2 != NULL)
            {
                s += l2->val ;
                l2 = l2->next ;
            }
            // step 4 : write the digit, send the carry on
            ListNode* node = new ListNode(s % 10) ;
            tail->next = node ;
            tail = node ;
            carry = s / 10 ;
        }
        // step 5
        return dummy->next ;
    }
};
