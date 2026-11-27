// orz
// 452. Minimum Number of Arrows to Burst Balloons · LeetCode · Medium
//
// Question:
// balloons are on a wall, balloon i spans points[i] = [xstart, xend] on the x axis.
// an arrow shot straight up at x bursts every balloon with xstart <= x <= xend,
// and keeps flying. return the minimum number of arrows that burst all balloons.
// Example 1: points = [[10,16],[2,8],[1,6],[7,12]]   -> 2   (x = 6 and x = 11)
// Example 2: points = [[1,2],[3,4],[5,6],[7,8]]      -> 4
// Example 3: points = [[1,2],[2,3],[3,4],[4,5]]      -> 2   (x = 2 and x = 4)
// Constraints: 1 <= n <= 10^5, points[i].length == 2, -2^31 <= xstart < xend <= 2^31 - 1
//
// 1. Mathematical statement
//    the smallest set of points X such that every interval [a, b] holds some x in X.
//
// 2. Brute force
//    an arrow can always slide right to the nearest balloon end, so only the n ends
//    matter. try every subset of ends, keep the smallest that hits every balloon.
//    O(2^n * n). dead.
//
// 3. What the brute force wastes
//    it tries arrows in places that are clearly worse. look at the balloon that ends
//    first: some arrow must hit it, so some arrow is at x <= its end. moving that
//    arrow right to exactly its end only gains balloons (every balloon that the
//    arrow hit still holds the end). so the first arrow can be fixed.
//
// 4. Key breaking point
//    that is my Movie Festival greedy: sort by end, shoot at the first end, skip every
//    balloon the arrow already hits (start <= arrow), and the first balloon that
//    starts after the arrow forces the next arrow at its own end.
//
// 5. Method
//    step 1 : sort the balloons by end.
//    step 2 : last = -INF (position of the last arrow, below every start).
//    step 3 : for every balloon [a, b] in that order:
//             if a > last, the last arrow misses it: shoot a new arrow at b, ans++, last = b.
//             else the last arrow already bursts it (a <= last <= b), skip.
//    step 4 : return ans.
//
// 6. Why it works
//    in end order, last is always the end of some earlier balloon, so last <= b for
//    every balloon still to come. so "a <= last" really means the arrow hits it.
//    a balloon with a > last is missed by every arrow so far and ends first among the
//    rest, so by 3 an optimal answer puts its next arrow exactly at b.
//    time O(n log n) for the sort, extra space O(1).
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
    int findMinArrowShots(vector<vector<int>>& points) {
        ll n = points.size() ;
        // step 1 : sort by end
        sort(points.begin() , points.end() , [](const vector < int > &a , const vector < int > &b)
        {
            return a[1] < b[1] ;
        }) ;
        // step 2 : no arrow yet, -INF is below every start
        ll last = -INF ;
        ll ans = 0 ;
        // step 3 : shoot only when the last arrow misses
        for(ll i = 0 ; i < n ; i++)
        {
            ll a = points[i][0] ;
            ll b = points[i][1] ;
            if(a > last)
            {
                ans++ ;
                last = b ;
            }
            else
            {
                continue ;
            }
        }
        // step 4
        return ans ;
    }
};
