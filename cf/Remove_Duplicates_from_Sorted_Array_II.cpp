// orz
// 80. Remove Duplicates from Sorted Array II · LeetCode · Medium
//
// Question:
// nums is sorted in non-decreasing order. remove some duplicates in place so that
// each unique element appears at most twice, keeping the relative order.
// return k, the length of the result; the first k elements of nums must be the
// result, what is after them does not matter. use O(1) extra memory.
// Example 1: nums = [1,1,1,2,2,3]         -> 5, nums = [1,1,2,2,3,_]
// Example 2: nums = [0,0,1,1,1,1,2,3,3]   -> 7, nums = [0,0,1,1,2,3,3,_,_]
// Constraints: 1 <= n <= 3 * 10^4, -10^4 <= nums[i] <= 10^4, nums is sorted non-decreasing
//
// 1. Mathematical statement
//    for every value x with c copies, keep min(c , 2) copies.
//    nums[0 .. k - 1] = the kept elements in order, k = sum of min(c , 2) over all values.
//
// 2. Brute force
//    find a third copy (nums[i] == nums[i - 2]), shift everything after it one place left, repeat.
//    up to n shifts of O(n) each, O(n^2) = 9 * 10^8. too slow.
//
// 3. What the brute force wastes
//    every element is shifted again for every extra copy before it,
//    when it only needs to move once, straight to its final slot.
//
// 4. Key breaking point
//    treat nums[0 .. k - 1] as a stack of the answer, built in place: my stack template
//    (pop while the top breaks the rule, then push).
//    the rule: never three equal values in a row. the array is sorted, so all copies of x
//    are next to each other, and x breaks the rule exactly when the top two are x.
//    so only the top two have to be checked.
//
// 5. Method
//    step 1 : k = 0, the stack is empty. nums[k - 1] is the top, nums[k - 2] is below it.
//    step 2 : for i = 0 .. n - 1, x = nums[i]:
//             while the stack has 2 elements and the top two are both x, pop: k--.
//             (it pops at most once: after one pop the top two are not both x any more.)
//    step 3 : push x: nums[k] = x, then k++.
//    step 4 : return k.
//
// 6. Why it works
//    when the top two are x, step 2 pops one x and step 3 pushes x back, so the stack
//    is unchanged: the third, fourth, .. copy of x is dropped. otherwise x is pushed.
//    so each value keeps its first min(c , 2) copies, in order.
//    k <= i at each write, so nums[i] is read before slot i can be written.
//    time O(n), extra space O(1).
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
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1 : nums[0 .. k - 1] is the stack
        ll k = 0 ;
        for(ll i = 0 ; i < n ; i++)
        {
            ll x = nums[i] ;
            // step 2 : pop while the top two are already x
            while(k >= 2 && nums[k - 1] == x && nums[k - 2] == x)
            {
                k-- ;
            }
            // step 3 : push x
            nums[k] = x ;
            k++ ;
        }
        // step 4
        return k ;
    }
};
