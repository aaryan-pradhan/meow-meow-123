// orz
// 209. Minimum Size Subarray Sum · LeetCode · Medium
//
// Question:
// given an array of positive integers nums and a positive integer target, return
// the smallest length of a subarray whose sum is greater than or equal to target.
// if there is no such subarray, return 0.
// Example 1: target = 7, nums = [2,3,1,2,4,3]        -> 2  ([4,3])
// Example 2: target = 4, nums = [1,4,4]              -> 1  ([4])
// Example 3: target = 11, nums = [1,1,1,1,1,1,1,1]   -> 0  (the whole array sums to 8)
// Constraints: 1 <= target <= 10^9, 1 <= n <= 10^5, 1 <= nums[i] <= 10^4
//
// 1. Mathematical statement
//    minimise h - t + 1 over all 0 <= t <= h < n with nums[t] + .. + nums[h] >= target.
//    0 if no pair (t, h) works.
//
// 2. Brute force
//    every t, every h >= t, running sum. O(n^2), n = 10^5 gives 5 * 10^9. dead.
//
// 3. What the brute force wastes
//    for a fixed t, only the FIRST h where the sum reaches target matters (longer is worse).
//    and when t moves right, that first h can only move right too, because the numbers
//    are positive: dropping nums[t] makes every sum smaller. the brute force restarts h from t.
//
// 4. Key breaking point
//    "sum >= target" with positive numbers is monotone in the window: my sliding window
//    t / h. for every tail t, push the head h while the window is still short of target.
//
// 5. Method
//    step 1 : t = 0, h = -1 (empty window), sum = 0, ans = n + 1 (means "none yet").
//    step 2 : while h + 1 < n and sum < target : h++, sum += nums[h].
//    step 3 : if sum >= target, [t, h] is the shortest good window starting at t,
//             ans = min(ans, h - t + 1).
//    step 4 : remove nums[t] from the window, t++ (empty window: t++, h = t - 1).
//    step 5 : ans still n + 1 means no window ever reached target, return 0. else ans.
//
// 6. Why it works
//    for each t, step 2 stops at the first h with sum >= target (or at h = n - 1).
//    that first h never moves left as t grows (positive numbers), so starting it from the
//    old h skips nothing. every t gets its best window, ans is the min of all of them.
//    t and h each move at most n times: time O(n), extra space O(1).
//    sum <= 10^5 * 10^4 = 10^9, but it is ll anyway.
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
    int minSubArrayLen(int target, vector<int>& nums) {
        ll n = nums.size() ;
        // step 1
        ll t = 0 , h = -1 , sum = 0 , ans = n + 1 ;
        while(t < n)
        {
            // step 2 : grow while the window is still short of target
            while(h + 1 < n && sum < target)
            {
                h++ ;
                sum += nums[h] ;
            }
            // step 3 : shortest good window starting at t
            if(sum >= target)
            {
                ans = min(ans , h - t + 1) ;
            }
            // step 4 : drop nums[t]
            if(t > h)
            {
                t++ ;
                h = t - 1 ;
            }
            else
            {
                sum -= nums[t] ;
                t++ ;
            }
        }
        // step 5
        if(ans == n + 1)
        {
            return 0 ;
        }
        else
        {
            return ans ;
        }
    }
};
