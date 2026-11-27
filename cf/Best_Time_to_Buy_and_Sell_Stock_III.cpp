// orz
// 123. Best Time to Buy and Sell Stock III · LeetCode · Hard
//
// Question:
// prices[i] is the price of a given stock on day i. find the maximum profit you can
// achieve with at most two transactions. you may not hold more than one share at a
// time (you must sell the stock before you buy again).
// Example 1: prices = [3,3,5,0,0,3,1,4] -> 6  (buy 0 sell 3, buy 1 sell 4)
// Example 2: prices = [1,2,3,4,5]       -> 4  (buy 1 sell 5)
// Example 3: prices = [7,6,4,3,1]       -> 0  (no transaction)
// Constraints: 1 <= prices.length <= 10^5, 0 <= prices[i] <= 10^5
//
// 1. Mathematical statement
//    choose t <= 2 pairs of days b1 < s1 <= b2 < s2 (only the first t of them),
//    maximise sum of (prices[s] - prices[b]) over the chosen pairs. t = 0 gives 0.
//
// 2. Brute force
//    try every b1, s1, b2, s2. O(n^4), n = 10^5. dead.
//
// 3. What the brute force wastes
//    on day i the future only depends on two things: do I hold a share right now,
//    and how many buys do I still have. every past that agrees on those two solves
//    the same future again.
//
// 4. Key breaking point
//    walk the days with a state (i , k , hold) : k = buys left, hold = 0 / 1.
//    each day : buy, sell or do nothing. a take / skip DP with a tiny extra state.
//    day i reads only day i + 1, so two rows.
//
// 5. Method
//    step 1 : FORM = i -> end. rec(i , k , hold) = the most profit from days i .. n - 1,
//             with k buys still allowed and hold = 1 if I hold a share now.
//    step 2 : CHECK : i == n, no days left, 0. (a share still held is worth nothing,
//             and it is never better than not buying it.)
//    step 3 : CHOICE + MOVE when hold == 1 :
//             sell = prices[i] + rec(i + 1 , k , 0), keep = rec(i + 1 , k , 1).
//    step 4 : CHOICE + MOVE when hold == 0 :
//             skip = rec(i + 1 , k , 0),
//             buy = -prices[i] + rec(i + 1 , k - 1 , 1), allowed only if k > 0.
//    step 5 : rec = max of the allowed choices. answer rec(0 , 2 , 0).
//    step 6 : COST : n * 3 * 2 = 6 * 10^5 states, 2 moves each. fine.
//    step 7 : bottom up, i from n down to 0.
//    step 8 : rolling rows. dp[i & 1][k][hold] is day i, dp[(i + 1) & 1][..][..] is day i + 1.
//
// 6. Why it works
//    each day I do exactly one of: buy (only without a share, using up one buy),
//    sell (only with a share), nothing. every plan of at most 2 transactions is one
//    path through these states, and every path is such a plan, so the max is exact.
//    a buy is counted when it happens, so k <= 2 caps the transactions at 2.
//    profit <= 10^5 * 10^5 / 2, ll is plenty.
//    time O(n * 2 * 3), extra space O(1) (2 * 3 * 2 numbers).
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
// ll rec(ll i , ll k , ll hold)
// {
//     // this returns the most profit from days i to n - 1 with k buys left, hold = 1 if I hold a share now
//     if(i == n)
//     {
//         return 0 ;
//     }
//     if(dp[i][k][hold] != -1)
//     {
//         return dp[i][k][hold] ;
//     }
//     ll ans = 0 ;
//     if(hold == 1)
//     {
//         ll sell = prices[i] + rec(i + 1 , k , 0) ;
//         ll keep = rec(i + 1 , k , 1) ;
//         ans = max(sell , keep) ;
//     }
//     else
//     {
//         ll skip = rec(i + 1 , k , 0) ;
//         ll buy = -INF ;
//         if(k > 0)
//         {
//             buy = -prices[i] + rec(i + 1 , k - 1 , 1) ;
//         }
//         ans = max(skip , buy) ;
//     }
//     return dp[i][k][hold] = ans ;
// }
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        ll n = prices.size() ;
        ll K = 2 ;
        // step 8 : two days, dp[i & 1][k][hold]
        vector < vector < vector < ll > > > dp(2 , vector < vector < ll > > (K + 1 , vector < ll > (2 , 0))) ;
        // step 7 : i from n down to 0
        for(ll i = n ; i >= 0 ; i--)
        {
            for(ll k = 0 ; k <= K ; k++)
            {
                for(ll hold = 0 ; hold <= 1 ; hold++)
                {
                    // step 2 : no days left
                    if(i == n)
                    {
                        dp[i & 1][k][hold] = 0 ;
                        continue ;
                    }
                    if(hold == 1)
                    {
                        // step 3 : sell today or keep the share
                        ll sell = prices[i] + dp[(i + 1) & 1][k][0] ;
                        ll keep = dp[(i + 1) & 1][k][1] ;
                        // step 5
                        dp[i & 1][k][hold] = max(sell , keep) ;
                    }
                    else
                    {
                        // step 4 : skip today or buy (if a buy is left)
                        ll skip = dp[(i + 1) & 1][k][0] ;
                        ll buy = -INF ;
                        if(k > 0)
                        {
                            buy = -prices[i] + dp[(i + 1) & 1][k - 1][1] ;
                        }
                        // step 5
                        dp[i & 1][k][hold] = max(skip , buy) ;
                    }
                }
            }
        }
        return dp[0][K][0] ;
    }
};
