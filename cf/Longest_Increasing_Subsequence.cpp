// orz
// 300. Longest Increasing Subsequence · LeetCode · Medium
//
// Question:
// given an integer array nums, return the length of the longest strictly increasing
// subsequence (keep the order, any elements may be skipped).
// Example 1: nums = [10,9,2,5,3,7,101,18] -> 4   (2, 3, 7, 101)
// Example 2: nums = [0,1,0,3,2,3]         -> 4   (0, 1, 2, 3)
// Example 3: nums = [7,7,7,7,7,7,7]       -> 1
// Constraints: 1 <= nums.length <= 2500, -10^4 <= nums[i] <= 10^4
// Follow up: an algorithm that runs in O(n log(n)) time. -> done here.
//
// 1. Mathematical statement
//    the largest k with indices i1 < i2 < .. < ik and nums[i1] < nums[i2] < .. < nums[ik].
//
// 2. Brute force
//    try every subsequence, keep the increasing ones: 2^n, n = 2500. dead.
//
// 3. What the brute force wastes
//    how an increasing subsequence can grow only depends on where it ends.
//    every subsequence ending at i is extended the same way, over and over.
//
// 4. Key breaking point
//    first: FORM = ending at i. rec(i) = the longest one ending exactly at i, O(n^2).
//    then the follow up: for each length keep only the smallest possible last value.
//    those values are sorted, so the one update per element is a binary search.
//
// 5. Method
//    the O(n^2) dp (the commented rec):
//    step 1 : FORM = ending at i. rec(i) = the longest increasing subsequence that
//             ends exactly at nums[i]. answer = max of rec(i) over all i.
//    step 2 : CHOICE = the previous element j < i. CHECK : nums[j] < nums[i].
//             MOVE : rec(i) = 1 + max rec(j) over the allowed j (just 1 if none).
//             COST : n states * n choices = 6.25 * 10^6. this alone passes, the follow
//             up asks for better.
//    the O(n log n) follow up, in small steps:
//    step 3 : among all increasing subsequences of length k + 1 seen so far, only the
//             smallest last value matters: a smaller end can be extended by every value
//             a bigger end can. call it tails[k]. tails starts empty.
//    step 4 : tails is strictly increasing. take the one of length k + 2 ending at
//             tails[k + 1] and drop its last value: a length k + 1 one ending at some
//             v < tails[k + 1]. so tails[k] <= v < tails[k + 1].
//    step 5 : a new value x extends exactly the subsequences ending below x.
//             let p = the first index with tails[p] >= x (lower_bound, tails is sorted).
//             tails[p - 1] < x, so x makes a length p + 1 subsequence ending at x,
//             and x <= tails[p], so tails[p] = x (better or equal).
//             no such p (x is bigger than every tail) -> push x, a new longest length.
//             lower_bound and not upper_bound: an equal value must replace, never extend
//             (strictly increasing).
//    step 6 : answer = tails.size().
//
// 6. Why it works
//    step 5 keeps the meaning of step 3 true after every element: x can only end
//    subsequences of length <= p + 1, it does not improve tails[p - 1] or below
//    (those are already < x), and it cannot reach length p + 2 (tails[p] >= x).
//    so at the end tails has one entry per achievable length, its size is the LIS.
//    tails is not itself a subsequence, only its size means something.
//    time O(n log n), extra space O(n).
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
// step 1 and step 2 : the O(n^2) dp
// ll rec(ll i)
// {
//     // this returns the length of the longest increasing subsequence that ends exactly at index i
//     if(dp[i] != -1)
//     {
//         return dp[i] ;
//     }
//     ll ans = 1 ;
//     for(ll j = 0 ; j < i ; j++)
//     {
//         if(nums[j] < nums[i])
//         {
//             ans = max(ans , 1 + rec(j)) ;
//         }
//     }
//     return dp[i] = ans ;
//     // answer = max of rec(i) over every i
//     // but this is O(n^2), the follow up wants O(n log n)
// }
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        ll n = nums.size() ;
        // step 3 : tails[k] is the smallest value that can be the last element of an increasing subsequence of length k + 1
        vector < ll > tails ;
        // step 5 : put every value where it belongs
        for(ll i = 0 ; i < n ; i++)
        {
            auto it = lower_bound(tails.begin() , tails.end() , nums[i]) ;
            // this returns the first element in tails which is greater than or equal to nums[i]
            // if there is no such element then it returns tails.end()
            if(it == tails.end())
            {
                // nums[i] is bigger than every tail, it makes a new longest length
                tails.push_back(nums[i]) ;
            }
            else
            {
                // nums[i] is a smaller end for that length
                *it = nums[i] ;
            }
        }
        // step 6
        return tails.size() ;
    }
};
