// orz
// 149. Max Points on a Line · LeetCode · Hard
//
// Question:
// given an array points where points[i] = [xi, yi] is a point on the X-Y plane,
// return the maximum number of points that lie on the same straight line.
// Example 1: points = [[1,1],[2,2],[3,3]]                     -> 3
// Example 2: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]   -> 4
// Constraints: 1 <= points.length <= 300, points[i].length == 2,
//              -10^4 <= xi, yi <= 10^4, all the points are unique
//
// 1. Mathematical statement
//    max over all lines L of |{ i : point i lies on L }|.
//    points j and k lie on the line through i iff (xj - xi) * (yk - yi) == (xk - xi) * (yj - yi).
//
// 2. Brute force
//    for every pair (i , j), walk all k and count the ones on line(i , j) with the
//    cross product above. O(n^3) = 2.7 * 10^7 at n = 300. it passes here, but the
//    same line is counted again for every pair of points on it.
//
// 3. What the brute force wastes
//    once i is fixed, every line through i is decided by its direction alone.
//    "is k on line(i , j)" = "does i -> k point the same way as i -> j". so instead of
//    testing pairs of directions, give each direction a name and count names.
//
// 4. Key breaking point
//    the direction from i to j as a key: (dx , dy) = (xj - xi , yj - yi), divided by
//    g = gcd(|dx| , |dy|), with one fixed sign. then two points give the same key iff
//    they are on the same line through i. map counting, like my freq map.
//    why not dy / dx as a double : vertical lines divide by 0, and doubles can round
//    two different slopes to the same value. the reduced pair is exact.
//
// 5. Method
//    step 1 : gcd(a , b) helper (a, b >= 0, not both 0).
//    step 2 : n == 1 -> 1. else ans = 1.
//    step 3 : for every anchor i : map < pll , ll > cnt, empty.
//    step 4 : for every j > i : dx = xj - xi, dy = yj - yi. points are unique so not both 0.
//             g = gcd(|dx| , |dy|), dx /= g, dy /= g.
//             fix the sign : make dx > 0, and if dx == 0 make dy > 0 (multiply both by -1).
//             cnt[{dx , dy}]++.
//    step 5 : for every it in cnt : ans = max(ans , it.sc + 1). the + 1 is point i itself.
//    step 6 : return ans.
//
// 6. Why it works
//    (dx , dy) and (dx' , dy') are on the same line through i iff one is a nonzero
//    multiple of the other. dividing by the gcd and fixing the sign maps every multiple
//    to one unique key, so cnt[key] + 1 = the points on that line through i.
//    the best line has some leftmost-index point i on it; with that i as the anchor all
//    its other points have j > i, so j > i loses nothing.
//    time O(n^2 log n) (map + gcd), extra space O(n).
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
// step 1
ll gcd(ll a , ll b)
{
    // this returns the greatest common divisor of a and b
    while(b)
    {
        a %= b ;
        swap(a , b) ;
    }
    return a ;
}
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        ll n = points.size() ;
        // step 2
        if(n == 1)
        {
            return 1 ;
        }
        ll ans = 1 ;
        // step 3 : fix the anchor i
        for(ll i = 0 ; i < n ; i++)
        {
            map < pll , ll > cnt ; // this stores how many points j > i go in each reduced direction from i
            // step 4 : the reduced direction from i to j
            for(ll j = i + 1 ; j < n ; j++)
            {
                ll dx = points[j][0] - points[i][0] ;
                ll dy = points[j][1] - points[i][1] ;
                ll g = gcd(abs(dx) , abs(dy)) ;
                dx /= g ;
                dy /= g ;
                if(dx < 0)
                {
                    dx = -dx ;
                    dy = -dy ;
                }
                else if(dx == 0 && dy < 0)
                {
                    dy = -dy ;
                }
                cnt[{dx , dy}]++ ;
            }
            // step 5 : best line through i
            for(auto it : cnt)
            {
                ans = max(ans , it.sc + 1) ;
            }
        }
        // step 6
        return ans ;
    }
};
