// orz
// 918. Maximum Sum Circular Subarray · LeetCode · Medium
//
// Question:
// given a circular integer array nums of length n (the next element of nums[n - 1] is nums[0]),
// return the maximum possible sum of a non-empty subarray of nums.
// a subarray may wrap around the end, but may include each element at most once.
// Example 1: nums = [1,-2,3,-2]  -> 3   (subarray [3])
// Example 2: nums = [5,-3,5]     -> 10  (subarray [5,5], it wraps)
// Example 3: nums = [-3,-2,-3]   -> -2  (subarray [-2])
// Constraints: 1 <= n <= 3 * 10^4, -3 * 10^4 <= nums[i] <= 3 * 10^4
//
// 1. Mathematical statement
//    a circular subarray is either a normal block nums[l .. r], or a wrapping one
//    nums[l .. n - 1] + nums[0 .. r] with r + 1 < l. maximise its sum over all of them (non-empty).
//
// 2. Brute force
//    for every start l, walk up to n steps around the circle with a running sum.
//    O(n^2) = 9 * 10^8. too slow.
//
// 3. What the brute force wastes
//    the normal blocks are exactly Maximum Subarray (53), which is O(n). the brute force redoes
//    that work for every start just to also cover the wrapping blocks.
//
// 4. Key breaking point
//    a wrapping block = the whole array MINUS the middle block nums[r + 1 .. l - 1] it skips.
//    so best wrapping sum = total - (smallest sum of a normal block). that is Kadane again, with min.
//    the skipped middle must not be the whole array (the answer is non-empty). that only matters
//    when every number is negative: then the best normal block (the largest number) is the answer.
//
// 5. Method
//    step 1 : dp "ending at i" twice, as in 53.
//             mx(i) = the largest sum of a block ending at i  = max(mx(i - 1) + nums[i] , nums[i]).
//             mn(i) = the smallest sum of a block ending at i = min(mn(i - 1) + nums[i] , nums[i]).
//             CHECK : i = 0, both are nums[0].
//    step 2 : bottom up i from 0 to n - 1 with rolling rows: [(i + 1) & 1] holds i - 1, [i & 1] gets i.
//             best = max of mx(i), worst = min of mn(i), total = sum of nums.
//    step 3 : best < 0 means every number is negative : return best.
//    step 4 : else return max(best , total - worst) (normal block, or wrapping block).
//
// 6. Why it works
//    every circular block is normal (counted in best) or wrapping (= total - a normal middle block,
//    so the best wrapping one is total - worst). if best >= 0 and worst happens to be the whole array,
//    total - worst = 0 <= best, so the empty answer never wins. if best < 0, all numbers are negative,
//    and adding more numbers only lowers a sum, so the best block is one number, which best already is.
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
// ll recmx(ll i)
// {
//     // this returns the largest sum of a block that ends exactly at index i
//     if(i == 0)
//     {
//         return nums[0] ;
//     }
//     ll extend = recmx(i - 1) + nums[i] ;
//     ll restart = nums[i] ;
//     return max(extend , restart) ;
// }
// ll recmn(ll i)
// {
//     // this returns the smallest sum of a block that ends exactly at index i
//     if(i == 0)
//     {
//         return nums[0] ;
//     }
//     ll extend = recmn(i - 1) + nums[i] ;
//     ll restart = nums[i] ;
//     return min(extend , restart) ;
// }
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1 : two slots each, mx[i & 1] / mn[i & 1]
        vector < ll > mx(2 , 0) , mn(2 , 0) ;
        ll best = -INF ;  // largest normal block
        ll worst = INF ;  // smallest normal block
        ll total = 0 ;
        // step 2 : i from 0 to n - 1
        for(ll i = 0 ; i < n ; i++)
        {
            total += nums[i] ;
            if(i == 0)
            {
                mx[i & 1] = nums[0] ;
                mn[i & 1] = nums[0] ;
                best = max(best , mx[i & 1]) ;
                worst = min(worst , mn[i & 1]) ;
                continue ;
            }
            // extend the block ending at i - 1, or restart at i
            ll extendmx = mx[(i + 1) & 1] + nums[i] ; // mx[(i + 1) & 1] holds mx(i - 1)
            ll extendmn = mn[(i + 1) & 1] + nums[i] ;
            ll restart = nums[i] ;
            mx[i & 1] = max(extendmx , restart) ;
            mn[i & 1] = min(extendmn , restart) ;
            best = max(best , mx[i & 1]) ;
            worst = min(worst , mn[i & 1]) ;
        }
        // step 3 : all numbers negative, the wrapping formula would give the empty block
        if(best < 0)
        {
            return best ;
        }
        else
        {
            // step 4 : normal block or wrapping block
            return max(best , total - worst) ;
        }
    }
};
