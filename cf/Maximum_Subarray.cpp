// orz
// 53. Maximum Subarray · LeetCode · Medium
//
// Question:
// given an integer array nums, find the subarray (contiguous, non-empty) with the
// largest sum, and return its sum.
// Example 1: nums = [-2,1,-3,4,-1,2,1,-5,4] -> 6   (subarray [4,-1,2,1])
// Example 2: nums = [1]                      -> 1
// Example 3: nums = [5,4,-1,7,8]             -> 23  (the whole array)
// Constraints: 1 <= n <= 10^5, -10^4 <= nums[i] <= 10^4
//
// 1. Mathematical statement
//    maximise nums[l] + nums[l + 1] + .. + nums[r] over all 0 <= l <= r < n.
//
// 2. Brute force
//    try every (l , r) and add up the block. O(n^3), or O(n^2) with a running sum for each l.
//    n = 10^5 gives 10^10. dead.
//
// 3. What the brute force wastes
//    the blocks ending at r and at r + 1 share everything except nums[r + 1], yet each l is
//    tried again for every r.
//
// 4. Key breaking point
//    group the blocks by where they END. the best block ending at i either is nums[i] alone,
//    or is the best block ending at i - 1 with nums[i] added (any other block ending at i - 1 is worse).
//    so one number per index is enough: a 1D DP, the "ending at i" form (Kadane).
//
// 5. Method
//    step 1 : FORM = 0 -> i. rec(i) = the best sum of a block that ends exactly at index i.
//    step 2 : CHOICE at level i : extend the block ending at i - 1, or restart at i.
//    step 3 : CHECK : i = 0 has nothing to extend, rec(0) = nums[0].
//    step 4 : MOVE : extend = rec(i - 1) + nums[i], restart = nums[i], keep the max.
//    step 5 : COST : n states, 2 choices each. ans = max of rec(i) over all i, because the best
//             block ends somewhere. ans starts at -INF, the numbers can all be negative.
//    step 6 : bottom up, i from 0 to n - 1, so i - 1 is ready before i.
//    step 7 : rolling rows. rec(i) only reads i - 1, so 2 slots are enough.
//             dp[(i + 1) & 1] holds dp[i - 1] (same parity), dp[i & 1] gets dp[i].
//
// 6. Why it works
//    a block ending at i is nums[i] alone, or (a block ending at i - 1) + nums[i]. the second kind is
//    best when that block is the best one ending at i - 1. so rec(i) is exact, and the answer is the
//    best over all ends. time O(n), extra space O(1).
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
// ll rec(ll i)
// {
//     // this returns the best sum of a block that ends exactly at index i
//     if(i == 0)
//     {
//         return nums[0] ;
//     }
//     ll extend = rec(i - 1) + nums[i] ;   // one call per level, so no memo is needed
//     ll restart = nums[i] ;
//     return max(extend , restart) ;
// }
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        ll n = nums.size() ;
        // step 7 : two slots, dp[i & 1]
        vector < ll > dp(2 , 0) ;
        // step 5 : best over all ends, can be negative
        ll ans = -INF ;
        // step 6 : i from 0 to n - 1
        for(ll i = 0 ; i < n ; i++)
        {
            // step 3 : nothing before index 0
            if(i == 0)
            {
                dp[i & 1] = nums[0] ;
                ans = max(ans , dp[i & 1]) ;
                continue ;
            }
            // step 4 : extend the block ending at i - 1, or restart at i
            ll extend = dp[(i + 1) & 1] + nums[i] ; // dp[(i + 1) & 1] holds dp[i - 1]
            ll restart = nums[i] ;
            dp[i & 1] = max(extend , restart) ;
            ans = max(ans , dp[i & 1]) ;
        }
        return ans ;
    }
};
