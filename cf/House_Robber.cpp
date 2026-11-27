// orz
// 198. House Robber · LeetCode · Medium
//
// Question:
// houses stand in a row and nums[i] is the money in house i. robbing two
// adjacent houses on the same night calls the police. return the most money
// you can rob tonight without calling the police.
// Example 1: nums = [1,2,3,1]   -> 4   (rob house 0 and house 2: 1 + 3)
// Example 2: nums = [2,7,9,3,1] -> 12  (rob houses 0, 2, 4: 2 + 9 + 1)
// Constraints: 1 <= n <= 100, 0 <= nums[i] <= 400
//
// 1. Mathematical statement
//    choose a set S of indices with no two consecutive (i and i + 1 never both in S).
//    maximise the sum of nums[i] over i in S.
//
// 2. Brute force
//    try every subset of houses, keep the ones with no two neighbours, take the best sum.
//    2^n subsets, n = 100 gives 2^100. dead.
//
// 3. What the brute force wastes
//    once houses 0 .. i - 1 are decided, the rest only depends on one thing:
//    may house i be robbed? every subset that agrees on that solves the same
//    leftover problem again and again.
//
// 4. Key breaking point
//    don't carry "was the previous house robbed" in the state.
//    robbing house i forbids i + 1, so robbing is a jump i -> i + 2 and skipping
//    is a step i -> i + 1. now the state is the index alone: a take / skip DP.
//
// 5. Method
//    step 1 : FORM = i -> end. rec(i) = the most money from houses i .. n - 1.
//             because every decision only cuts off a suffix.
//    step 2 : CHOICE at level i : rob house i, or skip it.
//    step 3 : CHECK : i >= n means no houses are left, value 0.
//             i can reach n + 1 because of the i + 2 jump, so both n and n + 1 are base cases.
//    step 4 : MOVE : nottake = rec(i + 1), take = nums[i] + rec(i + 2), keep the max.
//    step 5 : COST : n + 2 states, 2 transitions each. tiny.
//    step 6 : bottom up, i from n + 1 down to 0, so i + 1 and i + 2 are ready before i.
//    step 7 : rolling rows. rec(i) only reads i + 1 and i + 2, so 2 slots are enough.
//             dp[(i + 1) & 1] holds dp[i + 1].
//             dp[i & 1] still holds dp[i + 2] (same parity as i) until I overwrite it.
//
// 6. Why it works
//    every valid robbery of houses i .. n - 1 either skips house i (the rest is a valid
//    robbery of i + 1 ..) or robs it (then i + 1 is forbidden and the rest is a valid
//    robbery of i + 2 ..). the two cases cover everything, so the max of the two is exact.
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
// ll rec(ll i)
// {
//     // this returns the most money we can rob from houses i to n - 1
//     if(i >= n)
//     {
//         return 0 ;
//     }
//     if(dp[i] != -1)
//     {
//         return dp[i] ;
//     }
//     ll nottake = rec(i + 1) ;
//     ll take = nums[i] + rec(i + 2) ;
//     return dp[i] = max(nottake , take) ;
// }
class Solution {
public:
    int rob(vector<int>& nums) {
        ll n = nums.size() ;
        // step 7 : two slots, dp[i & 1]
        vector < ll > dp(2 , 0) ;
        // step 6 : i from n + 1 down to 0
        for(ll i = n + 1 ; i >= 0 ; i--)
        {
            // step 3 : no houses left
            if(i >= n)
            {
                dp[i & 1] = 0 ;
                continue ;
            }
            // step 4 : skip house i or rob house i
            ll nottake = dp[(i + 1) & 1] ;
            ll take = nums[i] + dp[i & 1] ; // dp[i & 1] still holds dp[i + 2] here
            dp[i & 1] = max(nottake , take) ;
        }
        return dp[0] ;
    }
};
