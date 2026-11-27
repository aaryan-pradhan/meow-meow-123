// orz
// 11. Container With Most Water · LeetCode · Medium
//
// Question:
// height has n numbers. there are n vertical lines, line i goes from (i, 0) to
// (i, height[i]). pick two lines that, together with the x-axis, form a container
// holding the most water (the container can not be tilted). return that amount.
// Example 1: height = [1,8,6,2,5,4,8,3,7] -> 49  (lines 1 and 8: width 7, min(8, 7) = 7)
// Example 2: height = [1,1]               -> 1
// Constraints: 2 <= n <= 10^5, 0 <= height[i] <= 10^4
//
// 1. Mathematical statement
//    maximise area(i, j) = (j - i) * min(height[i], height[j]) over 0 <= i < j < n.
//
// 2. Brute force
//    try every pair. O(n^2), n = 10^5 gives 5 * 10^9. dead.
//
// 3. What the brute force wastes
//    once the shorter line of a pair is known, every narrower pair that keeps that
//    line can not beat it: the width drops and the water level can not go above
//    the shorter line. the brute force still checks all of them.
//
// 4. Key breaking point
//    converging two pointers. start with the widest pair (0, n - 1).
//    the shorter of the two lines is finished: drop it and move inwards.
//
// 5. Method
//    step 1 : l = 0, r = n - 1, ans = 0.
//    step 2 : while l < r : ans = max(ans, (r - l) * min(height[l], height[r])).
//    step 3 : if height[l] <= height[r], l++ (l is the shorter line), else r--.
//    step 4 : return ans.
//
// 6. Why it works
//    say height[l] <= height[r]. any other pair (l, k) with l < k < r has
//    width k - l < r - l and level min(height[l], height[k]) <= height[l],
//    so area(l, k) <= (r - l) * height[l] = area(l, r), already counted.
//    pairs (k, l) with k < l were dropped earlier the same way. so line l has
//    no better pair left and dropping it loses nothing. same for r.
//    time O(n), extra space O(1). the area is at most 10^5 * 10^4 = 10^9, fits in int.
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
    int maxArea(vector<int>& height) {
        ll n = height.size() ;
        // step 1
        ll l = 0 , r = n - 1 , ans = 0 ;
        while(l < r)
        {
            // step 2 : water between line l and line r
            ll level = min(height[l] , height[r]) ;
            ll area = (r - l) * level ;
            ans = max(ans , area) ;
            // step 3 : the shorter line is finished
            if(height[l] <= height[r])
            {
                l++ ;
            }
            else
            {
                r-- ;
            }
        }
        // step 4
        return ans ;
    }
};
