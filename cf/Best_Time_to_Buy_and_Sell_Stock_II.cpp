// orz
// 122. Best Time to Buy and Sell Stock II · LeetCode · Medium
//
// Question:
// prices[i] is the price of a stock on day i. on each day you may buy and/or sell,
// but you can hold at most one share at any time. you may buy and sell on the same day.
// return the maximum profit.
// Example 1: prices = [7,1,5,3,6,4]   -> 7   (buy 1 sell 5: +4, buy 3 sell 6: +3)
// Example 2: prices = [1,2,3,4,5]     -> 4   (buy 1 sell 5)
// Example 3: prices = [7,6,4,3,1]     -> 0
// Constraints: 1 <= n <= 3 * 10^4, 0 <= prices[i] <= 10^4
//
// 1. Mathematical statement
//    choose trades (b1 , s1) , (b2 , s2) , .. with b1 < s1 <= b2 < s2 <= .. (one share at a time).
//    maximise the sum of prices[s] - prices[b].
//
// 2. Brute force
//    on every day choose hold or not hold, try all 2^n patterns. n = 3 * 10^4. dead.
//
// 3. What the brute force wastes
//    the profit of a trade does not depend on how it is cut into days.
//    every pattern pays the same day-to-day moves again and again.
//
// 4. Key breaking point
//    a trade split into days: prices[s] - prices[b] = sum of d[t] = prices[t + 1] - prices[t]
//    for t = b .. s - 1. trades don't overlap, so any plan earns sum of d[t] over some
//    set of days t, each t at most once. that is at most the sum of the positive d[t].
//    and that bound is reached: on every day with d[t] > 0, buy on day t and sell on day t + 1.
//
// 5. Method
//    step 1 : ans = 0.
//    step 2 : for t = 0 .. n - 2: d = prices[t + 1] - prices[t].
//             if d > 0, take it: ans += d. else skip that day.
//    step 3 : return ans.
//
// 6. Why it works
//    upper bound: every plan's profit = sum of d[t] over the days it holds, <= sum of positive d[t].
//    reached: the one-day trades on up days are a valid plan (selling and buying again
//    on the same day is allowed) and earn exactly that sum.
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
    int maxProfit(vector<int>& prices) {
        ll n = prices.size() ;
        // step 1
        ll ans = 0 ;
        // step 2 : take every positive day-to-day move
        for(ll t = 0 ; t + 1 < n ; t++)
        {
            ll d = prices[t + 1] - prices[t] ;
            if(d > 0)
            {
                ans += d ;
            }
            else
            {
                continue ;
            }
        }
        // step 3
        return ans ;
    }
};
