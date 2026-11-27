// orz
// 188. Best Time to Buy and Sell Stock IV · LeetCode · Hard
//
// Question:
// given an integer k and an array prices where prices[i] is the price of a given stock
// on day i, find the maximum profit you can achieve with at most k transactions.
// you may not hold more than one share at a time (sell before you buy again).
// Example 1: k = 2, prices = [2,4,1]         -> 2  (buy 2 sell 4)
// Example 2: k = 2, prices = [3,2,6,5,0,3]   -> 7  (buy 2 sell 6, buy 0 sell 3)
// Constraints: 1 <= k <= 100, 1 <= prices.length <= 1000, 0 <= prices[i] <= 1000
//
// 1. Mathematical statement
//    choose t <= k pairs of days b1 < s1 <= b2 < s2 <= .. <= bt < st,
//    maximise sum of (prices[sj] - prices[bj]) over j = 1 .. t. t = 0 gives 0.
//
// 2. Brute force
//    try every choice of up to k (buy , sell) pairs: about C(n , 2k) choices,
//    n = 1000, k = 100. dead.
//
// 3. What the brute force wastes
//    on day i the future only depends on two things: do I hold a share right now,
//    and how many buys do I still have. every past that agrees on those two solves
//    the same future again.
//
// 4. Key breaking point
//    the same DP as Stock III with 2 replaced by k: state (i , buys left , hold).
//    each day : buy, sell or do nothing. day i reads only day i + 1, so two rows.
//
// 5. Method
//    step 1 : FORM = i -> end. rec(i , b , hold) = the most profit from days i .. n - 1,
//             with b buys still allowed and hold = 1 if I hold a share now.
//    step 2 : CHECK : i == n, no days left, 0. (a share still held is worth nothing,
//             and it is never better than not buying it.)
//    step 3 : CHOICE + MOVE when hold == 1 :
//             sell = prices[i] + rec(i + 1 , b , 0), keep = rec(i + 1 , b , 1).
//    step 4 : CHOICE + MOVE when hold == 0 :
//             skip = rec(i + 1 , b , 0),
//             buy = -prices[i] + rec(i + 1 , b - 1 , 1), allowed only if b > 0.
//    step 5 : rec = max of the allowed choices. answer rec(0 , K , 0), K = the given k.
//    step 6 : COST : n * (K + 1) * 2 = 1000 * 101 * 2 = 2 * 10^5 states, 2 moves each. fine.
//    step 7 : bottom up, i from n down to 0.
//    step 8 : rolling rows. dp[i & 1][b][hold] is day i, dp[(i + 1) & 1][..][..] is day i + 1.
//
// 6. Why it works
//    each day I do exactly one of: buy (only without a share, using up one buy),
//    sell (only with a share), nothing. every plan of at most K transactions is one
//    path through these states, and every path is such a plan, so the max is exact.
//    a buy is counted when it happens, so b starting at K caps the transactions at K.
//    time O(n * K), extra space O(K).
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
// ll rec(ll i , ll b , ll hold)
// {
//     // this returns the most profit from days i to n - 1 with b buys left, hold = 1 if I hold a share now
//     if(i == n)
//     {
//         return 0 ;
//     }
//     if(dp[i][b][hold] != -1)
//     {
//         return dp[i][b][hold] ;
//     }
//     ll ans = 0 ;
//     if(hold == 1)
//     {
//         ll sell = prices[i] + rec(i + 1 , b , 0) ;
//         ll keep = rec(i + 1 , b , 1) ;
//         ans = max(sell , keep) ;
//     }
//     else
//     {
//         ll skip = rec(i + 1 , b , 0) ;
//         ll buy = -INF ;
//         if(b > 0)
//         {
//             buy = -prices[i] + rec(i + 1 , b - 1 , 1) ;
//         }
//         ans = max(skip , buy) ;
//     }
//     return dp[i][b][hold] = ans ;
// }
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        ll n = prices.size() ;
        ll K = k ;
        // step 8 : two days, dp[i & 1][b][hold]
        vector < vector < vector < ll > > > dp(2 , vector < vector < ll > > (K + 1 , vector < ll > (2 , 0))) ;
        // step 7 : i from n down to 0
        for(ll i = n ; i >= 0 ; i--)
        {
            for(ll b = 0 ; b <= K ; b++)
            {
                for(ll hold = 0 ; hold <= 1 ; hold++)
                {
                    // step 2 : no days left
                    if(i == n)
                    {
                        dp[i & 1][b][hold] = 0 ;
                        continue ;
                    }
                    if(hold == 1)
                    {
                        // step 3 : sell today or keep the share
                        ll sell = prices[i] + dp[(i + 1) & 1][b][0] ;
                        ll keep = dp[(i + 1) & 1][b][1] ;
                        // step 5
                        dp[i & 1][b][hold] = max(sell , keep) ;
                    }
                    else
                    {
                        // step 4 : skip today or buy (if a buy is left)
                        ll skip = dp[(i + 1) & 1][b][0] ;
                        ll buy = -INF ;
                        if(b > 0)
                        {
                            buy = -prices[i] + dp[(i + 1) & 1][b - 1][1] ;
                        }
                        // step 5
                        dp[i & 1][b][hold] = max(skip , buy) ;
                    }
                }
            }
        }
        return dp[0][K][0] ;
    }
};
