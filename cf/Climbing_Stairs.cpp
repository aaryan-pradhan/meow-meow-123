// orz
// 70. Climbing Stairs · LeetCode · Easy
//
// Question:
// you are climbing a staircase. it takes n steps to reach the top. each time you
// can climb either 1 or 2 steps. in how many distinct ways can you climb to the top?
// Example 1: n = 2 -> 2  (1 + 1, 2)
// Example 2: n = 3 -> 3  (1 + 1 + 1, 1 + 2, 2 + 1)
// Constraints: 1 <= n <= 45
//
// 1. Mathematical statement
//    count the sequences (a1 , a2 , .. , ak) with every aj in {1 , 2} and a1 + .. + ak = n.
//
// 2. Brute force
//    try both moves at every step without remembering anything.
//    the call tree has about 1.6^n leaves, 1.6^45 is about 10^9. dead.
//
// 3. What the brute force wastes
//    once I stand on step i, the number of ways to finish only depends on i,
//    not on how I got there. the brute force recounts it for every way of reaching i.
//
// 4. Key breaking point
//    the state is the step i alone: a 1 / 2 jump DP, same shape as House Robber
//    (a step i -> i + 1 and a jump i -> i + 2).
//
// 5. Method
//    step 1 : FORM = i -> end. rec(i) = the number of ways to go from step i to step n.
//    step 2 : CHOICE at level i : climb 1 or climb 2.
//    step 3 : CHECK : i == n means I am on top, 1 way (stop here).
//             i == n + 1 means the 2 jumped over the top, 0 ways.
//    step 4 : MOVE : one = rec(i + 1), two = rec(i + 2), rec(i) = one + two.
//    step 5 : COST : n + 2 states, 2 transitions each. tiny.
//    step 6 : bottom up, i from n + 1 down to 0, so i + 1 and i + 2 are ready before i.
//    step 7 : rolling rows. rec(i) only reads i + 1 and i + 2, so 2 slots are enough.
//             dp[(i + 1) & 1] holds dp[i + 1].
//             dp[i & 1] still holds dp[i + 2] (same parity as i) until I overwrite it.
//
// 6. Why it works
//    every way up from step i starts with a 1 (then it is a way up from i + 1) or a 2
//    (then it is a way up from i + 2). the two groups do not overlap and cover
//    everything, so the counts add. the answer is rec(0) = fib(n + 1) <= 1836311903, fits int.
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
//     // this returns the number of ways to climb from step i to step n
//     if(i > n)
//     {
//         return 0 ;
//     }
//     if(i == n)
//     {
//         return 1 ;
//     }
//     if(dp[i] != -1)
//     {
//         return dp[i] ;
//     }
//     ll one = rec(i + 1) ;
//     ll two = rec(i + 2) ;
//     return dp[i] = one + two ;
// }
class Solution {
public:
    int climbStairs(int n) {
        // step 7 : two slots, dp[i & 1]
        vector < ll > dp(2 , 0) ;
        // step 6 : i from n + 1 down to 0
        for(ll i = n + 1 ; i >= 0 ; i--)
        {
            // step 3 : jumped over the top
            if(i > n)
            {
                dp[i & 1] = 0 ;
                continue ;
            }
            // step 3 : on top
            if(i == n)
            {
                dp[i & 1] = 1 ;
                continue ;
            }
            // step 4 : climb 1 or climb 2
            ll one = dp[(i + 1) & 1] ;
            ll two = dp[i & 1] ; // dp[i & 1] still holds dp[i + 2] here
            dp[i & 1] = one + two ;
        }
        return dp[0] ;
    }
};
