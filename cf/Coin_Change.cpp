// orz
// 322. Coin Change · LeetCode · Medium
//
// Question:
// coins[i] are coin values and amount is a total amount of money. return the fewest
// number of coins needed to make up exactly that amount. if no combination of the
// coins makes the amount, return -1. there is an infinite number of each kind of coin.
// Example 1: coins = [1,2,5], amount = 11 -> 3   (5 + 5 + 1)
// Example 2: coins = [2], amount = 3      -> -1
// Example 3: coins = [1], amount = 0      -> 0
// Constraints: 1 <= coins.length <= 12, 1 <= coins[i] <= 2^31 - 1, 0 <= amount <= 10^4
//
// 1. Mathematical statement
//    minimise k1 + k2 + .. + km over integers kj >= 0 with
//    k1 * coins[0] + .. + km * coins[m - 1] = amount. no solution -> -1.
//
// 2. Brute force
//    try every coin as the next coin until the sum hits or passes amount.
//    with a coin of 1 the tree is 12 wide and up to 10^4 deep. dead.
//
// 3. What the brute force wastes
//    after some coins, what is left to pay is a sum s, and the best way to pay s
//    does not care which coins paid the rest. every path that leaves s solves s again.
//
// 4. Key breaking point
//    the state is the sum s still to pay, the choice is the last coin.
//    my Minimizing Coins DP: min DP with base 0 and INF for "impossible".
//
// 5. Method
//    step 1 : FORM = the sum. rec(s) = the fewest coins that make exactly s.
//    step 2 : CHOICE at level s : the coin c used last.
//    step 3 : CHECK : s == 0 needs 0 coins.
//             a coin c is allowed only if c <= s (else the sum goes negative).
//    step 4 : MOVE : take = rec(s - c) + 1, rec(s) = min of take over the allowed coins.
//             no allowed coin, or every s - c impossible -> rec(s) stays INF.
//    step 5 : COST : amount + 1 states, 12 coins each, 1.2 * 10^5. tiny.
//    step 6 : bottom up, s from 0 up to amount, since s - c < s is ready before s.
//             no rolling: s - c can be anything below s.
//    step 7 : dp[amount] == INF -> -1, else dp[amount].
//
// 6. Why it works
//    any way to pay s has a last coin c <= s, and the coins before it pay s - c,
//    at best in rec(s - c) coins. trying every c covers every way, so the min is exact.
//    INF + 1 never beats a real count, so impossible sums stay exactly INF.
//    time O(amount * m), extra space O(amount).
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
// ll rec(ll s)
// {
//     // this returns the fewest coins that make exactly the sum s (INF if no way)
//     if(s == 0)
//     {
//         return 0 ;
//     }
//     if(dp[s] != -1)
//     {
//         return dp[s] ;
//     }
//     ll ans = INF ;
//     for(auto c : coins)
//     {
//         if(c <= s)
//         {
//             ll take = rec(s - c) + 1 ;
//             ans = min(ans , take) ;
//         }
//     }
//     return dp[s] = ans ;
// }
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector < ll > dp(amount + 1 , INF) ;
        // step 6 : s from 0 up to amount
        for(ll s = 0 ; s <= amount ; s++)
        {
            // step 3 : nothing to pay
            if(s == 0)
            {
                dp[s] = 0 ;
                continue ;
            }
            // step 2 : try every coin as the last one
            ll ans = INF ;
            for(auto c : coins)
            {
                // step 3 : the coin must fit
                if(c <= s)
                {
                    // step 4
                    ll take = dp[s - c] + 1 ;
                    ans = min(ans , take) ;
                }
                else
                {
                    continue ;
                }
            }
            dp[s] = ans ;
        }
        // step 7
        if(dp[amount] == INF)
        {
            return -1 ;
        }
        else
        {
            return dp[amount] ;
        }
    }
};
