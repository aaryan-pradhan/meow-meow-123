// orz
// 121. Best Time to Buy and Sell Stock · LeetCode · Easy
//
// Question:
// prices[i] is the price of a stock on day i. choose one day to buy one share and a
// later day to sell it. return the maximum profit, or 0 if no profit is possible.
// Example 1: prices = [7,1,5,3,6,4]   -> 5   (buy at 1 on day 1, sell at 6 on day 4)
// Example 2: prices = [7,6,4,3,1]     -> 0   (prices only fall, don't trade)
// Constraints: 1 <= n <= 10^5, 0 <= prices[i] <= 10^4
//
// 1. Mathematical statement
//    maximise prices[j] - prices[i] over all i < j, and 0 if that max is negative
//    (or there is no pair, n = 1).
//
// 2. Brute force
//    try every pair i < j. O(n^2) = 10^10. dead.
//
// 3. What the brute force wastes
//    for a fixed sell day j, only the cheapest buy day before j matters,
//    and the brute force scans all of them again for every j.
//
// 4. Key breaking point
//    max difference with i < j: fix the sell day j, the best buy is
//    minsofar = min(prices[0 .. j - 1]). that min grows one element per day,
//    so keep it as a running min.
//
// 5. Method
//    step 1 : ans = 0 (not trading is allowed), minsofar = prices[0].
//    step 2 : for j = 1 .. n - 1:
//             score selling on day j FIRST: ans = max(ans , prices[j] - minsofar).
//             then minsofar = min(minsofar , prices[j]).
//             first score, then update, because buy and sell can't be the same day
//             (that pair gives 0 anyway, ans already starts at 0).
//    step 3 : return ans.
//
// 6. Why it works
//    when day j is scored, minsofar = min(prices[0 .. j - 1]), the best buy for selling on j.
//    every sell day is scored, so the best pair is found.
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
        ll minsofar = prices[0] ; // this stores the cheapest price before day j
        // step 2 : score day j, then update the min
        for(ll j = 1 ; j < n ; j++)
        {
            ans = max(ans , prices[j] - minsofar) ;
            minsofar = min(minsofar , (ll)prices[j]) ;
        }
        // step 3
        return ans ;
    }
};
