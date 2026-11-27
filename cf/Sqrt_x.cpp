// orz
// 69. Sqrt(x) · LeetCode · Easy
//
// Question:
// given a non-negative integer x, return the square root of x rounded down to the
// nearest integer. the returned integer should be non-negative as well.
// you must not use any built-in exponent function or operator (no pow(x , 0.5), no sqrt).
// Example 1: x = 4 -> 2
// Example 2: x = 8 -> 2  (sqrt(8) = 2.828.., rounded down)
// Constraints: 0 <= x <= 2^31 - 1
//
// 1. Mathematical statement
//    find the largest integer r >= 0 with r * r <= x.
//
// 2. Brute force
//    r = 0, 1, 2, .. while (r + 1) * (r + 1) <= x.
//    sqrt(2^31) is about 46341 steps. it passes, but it is a linear scan of a
//    sorted yes / no line, which binary search does in 32 steps.
//
// 3. What the brute force wastes
//    "r * r <= x" is true for r = 0 .. ans and false after it.
//    one check at mid tells me which side the answer is on, so I can throw half away.
//
// 4. Key breaking point
//    this is my binary search on the answer: a monotone bool check(mid),
//    and I want the last mid where it is true.
//
// 5. Method
//    step 1 : check(mid , x) returns true if mid * mid <= x. mid and mid * mid are ll,
//             mid <= 2^31 - 1 so mid * mid < 4.7 * 10^18 fits.
//    step 2 : lo = 0, hi = x, ans = 0 (r = 0 always works).
//    step 3 : while lo <= hi : mid = lo + (hi - lo) / 2.
//             check(mid) true  -> ans = mid, the answer is mid or bigger, lo = mid + 1.
//             check(mid) false -> the answer is smaller, hi = mid - 1.
//    step 4 : return ans.
//
// 6. Why it works
//    check is true on 0 .. r and false after r, and the answer r lies in [0 , x]
//    (x * x >= x for x >= 1, and r = 0 for x = 0). every true mid is stored in ans
//    before lo jumps past it, and the loop only drops halves that cannot hold a larger
//    true value, so ans ends at r.
//    time O(log x), extra space O(1).
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
bool check(ll mid , ll x)
{
    // this returns true if mid * mid <= x
    if(mid * mid <= x)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
class Solution {
public:
    int mySqrt(int x) {
        // step 2
        ll lo = 0 , hi = x , ans = 0 ;
        // step 3 : last mid where check is true
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2 ;
            if(check(mid , x))
            {
                ans = mid ;
                lo = mid + 1 ;
            }
            else
            {
                hi = mid - 1 ;
            }
        }
        // step 4
        return ans ;
    }
};
