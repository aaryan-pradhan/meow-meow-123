// orz
// 42. Trapping Rain Water · LeetCode · Hard
//
// Question:
// given n non-negative integers height[i], the heights of bars of width 1 standing
// side by side, return how much water is trapped between them after raining.
// Example 1: height = [0,1,0,2,1,0,1,3,2,1,2,1] -> 6
// Example 2: height = [4,2,0,3,2,5]             -> 9
// Constraints: 1 <= n <= 2 * 10^4, 0 <= height[i] <= 10^5
//
// 1. Mathematical statement
//    water[i] = max(0 , min(max of h[0 .. i - 1] , max of h[i + 1 .. n - 1]) - h[i]).
//    the two end bars hold nothing. answer = sum of water[i].
//
// 2. Brute force
//    for every i, scan left for the tallest bar and scan right for the tallest bar.
//    O(n^2), n = 2 * 10^4 gives 4 * 10^8. dead.
//
// 3. What the brute force wastes
//    the tallest bar left of i and left of i + 1 differ by one bar only,
//    and each scan finds it again from scratch.
//
// 4. Key breaking point
//    "tallest bar on the left of i" is a prefix max, "tallest on the right" a suffix max.
//    the same prefix / suffix idea as Product of Array Except Self, with max instead of *.
//
// 5. Method
//    step 1 : dp1[i] = max of h[0 .. i], left to right : dp1[i] = max(h[i] , dp1[i - 1]).
//    step 2 : dp2[i] = max of h[i .. n - 1], right to left : dp2[i] = max(h[i] , dp2[i + 1]).
//    step 3 : for i = 1 .. n - 2, water = min(dp1[i - 1] , dp2[i + 1]) - h[i].
//             if it is below 0 (bar i is taller than a side) the bar holds 0. add it up.
//
// 6. Why it works
//    water above bar i rises until it spills over the lower of the two tallest walls
//    around it, so the level is min(left wall , right wall) and the depth is that minus h[i].
//    time O(n), extra space O(n).
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
    int trap(vector<int>& height) {
        ll n = height.size() ;
        // step 1 : dp1[i] stores the tallest bar in 0 .. i
        vector < ll > dp1(n , 0) ;
        dp1[0] = height[0] ;
        for(ll i = 1 ; i < n ; i++)
        {
            dp1[i] = max((ll)height[i] , dp1[i - 1]) ;
        }
        // step 2 : dp2[i] stores the tallest bar in i .. n - 1
        vector < ll > dp2(n , 0) ;
        dp2[n - 1] = height[n - 1] ;
        for(ll i = n - 2 ; i >= 0 ; i--)
        {
            dp2[i] = max((ll)height[i] , dp2[i + 1]) ;
        }
        // step 3 : water above every inner bar
        ll ans = 0 ;
        for(ll i = 1 ; i < n - 1 ; i++)
        {
            ll water = min(dp1[i - 1] , dp2[i + 1]) - height[i] ;
            if(water < 0)
            {
                water = 0 ;
            }
            ans += water ;
        }
        return ans ;
    }
};
