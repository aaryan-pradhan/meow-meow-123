// orz
// 4. Median of Two Sorted Arrays · LeetCode · Hard
//
// Question:
// given two sorted arrays nums1 and nums2 of size m and n, return the median of the
// two sorted arrays together. the overall run time complexity should be O(log (m + n)).
// Example 1: nums1 = [1,3], nums2 = [2]    -> 2.00000   (merged [1,2,3], median 2)
// Example 2: nums1 = [1,2], nums2 = [3,4]  -> 2.50000   (merged [1,2,3,4], median (2 + 3) / 2)
// Constraints: 0 <= m, n <= 1000, 1 <= m + n <= 2000, -10^6 <= nums1[i], nums2[i] <= 10^6
//
// 1. Mathematical statement
//    let c = the merged sorted list of all m + n values, t = m + n.
//    t odd  -> answer c[(t - 1) / 2].
//    t even -> answer (c[t / 2 - 1] + c[t / 2]) / 2.
//
// 2. Brute force
//    merge the two arrays with two pointers and read the middle. O(m + n),
//    the judge asks for O(log(m + n)).
//
// 3. What the brute force wastes
//    it builds the whole merged list, but the median only needs to know where the
//    list is cut in half: which values go to the left half and which to the right.
//
// 4. Key breaking point
//    let half = (t + 1) / 2 = the size of the left half (one more than the right when t is odd).
//    the left half of c is always "the first i values of nums1 plus the first j values of nums2"
//    with i + j = half, because both arrays are sorted. so I only choose i, and j = half - i.
//    write a = nums1, b = nums2, and a[-1] = b[-1] = -INF, a[m] = b[n] = +INF for the borders.
//    a cut i is right when every left value <= every right value. inside a and inside b that is
//    free (sorted), so only the two cross pairs matter:
//        a[i - 1] <= b[j]    and    b[j - 1] <= a[i].
//    check(i) = "b[j - 1] <= a[i]" (with j = half - i).
//    when i grows by 1, a[i] can only grow and j shrinks so b[j - 1] can only shrink:
//    once check is true it stays true. false .. false true .. true. my binary search template.
//    the FIRST i with check true also has the other pair: check(i - 1) is false, so
//    b[j] > a[i - 1] (for i - 1 the j is j + 1, and b[(j + 1) - 1] = b[j]). and if i = 0, a[-1] = -INF.
//
// 5. Method
//    step 1 : make nums1 the shorter array (call again with the two swapped), so m <= n.
//             then j = half - i stays inside [0 , n] for every i in [0 , m].
//    step 2 : at(x , k) returns x[k], or -INF for k < 0, or +INF for k >= size. check(i) as above.
//    step 3 : binary search template over i in [0 , m], ans = m at the start
//             (check(m) is true, a[m] = +INF).
//    step 4 : i = ans, j = half - i.
//             leftmax = max(a[i - 1] , b[j - 1]) = the biggest value of the left half,
//             rightmin = min(a[i] , b[j]) = the smallest value of the right half.
//    step 5 : t odd -> leftmax (the left half has the one extra value, the middle one).
//             t even -> (leftmax + rightmin) / 2.0.
//
// 6. Why it works
//    at the cut from step 3 both cross pairs hold, so every left value <= every right value,
//    so the left half is exactly c[0 .. half - 1]. then leftmax = c[half - 1] and rightmin = c[half],
//    which are the middle values. why m <= n keeps j legal: half - m >= 0 since half >= m,
//    and half - 0 <= n since (m + n + 1) / 2 <= (2n + 1) / 2 = n.
//    time O(log(min(m , n))) which is within O(log(m + n)), extra space O(1) (nothing is copied).
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
// step 2
ll at(vector<int>& x , ll k)
{
    // this returns x[k], with -INF before the start and +INF after the end
    ll sz = x.size() ;
    if(k < 0)
    {
        return -INF ;
    }
    else if(k >= sz)
    {
        return INF ;
    }
    else
    {
        return x[k] ;
    }
}
bool check(ll i , vector<int>& a , vector<int>& b , ll half)
{
    // this returns true if, taking i values from a and half - i from b,
    // the last value taken from b is <= the first value not taken from a
    ll j = half - i ;
    if(at(b , j - 1) <= at(a , i))
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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        ll m = nums1.size() ;
        ll n = nums2.size() ;
        // step 1 : binary search on the shorter array
        if(m > n)
        {
            return findMedianSortedArrays(nums2 , nums1) ;
        }
        ll t = m + n ;
        ll half = (t + 1) / 2 ;
        // step 3 : first i where check is true
        ll lo = 0 , hi = m , ans = m ;
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2 ;
            if(check(mid , nums1 , nums2 , half))
            {
                ans = mid ;
                hi = mid - 1 ;
            }
            else
            {
                lo = mid + 1 ;
            }
        }
        // step 4
        ll i = ans ;
        ll j = half - i ;
        ll leftmax = max(at(nums1 , i - 1) , at(nums2 , j - 1)) ;
        ll rightmin = min(at(nums1 , i) , at(nums2 , j)) ;
        // step 5
        if(t % 2 == 1)
        {
            return leftmax ;
        }
        else
        {
            return (leftmax + rightmin) / 2.0 ;
        }
    }
};
