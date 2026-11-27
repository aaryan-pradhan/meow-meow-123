// orz
// 274. H-Index · LeetCode · Medium
//
// Question:
// citations[i] is the number of citations of a researcher's i-th paper.
// the h-index is the maximum h such that the researcher has at least h papers
// that each have at least h citations. return the h-index.
// Example 1: citations = [3,0,6,1,5]   -> 3   (3 papers with >= 3 citations: 3, 6, 5)
// Example 2: citations = [1,3,1]       -> 1
// Constraints: 1 <= n <= 5000, 0 <= citations[i] <= 1000
//
// 1. Mathematical statement
//    cnt(h) = number of i with citations[i] >= h.
//    find the largest h in 0 .. n with cnt(h) >= h. (h = 0 always works, h > n never does.)
//
// 2. Brute force
//    try every h from n down to 0, count cnt(h) with a full scan, stop at the first that works.
//    O(n^2) = 2.5 * 10^7. passes here, but it scans the array for every h.
//
// 3. What the brute force wastes
//    the answer to "does h work?" has a shape, and the brute force ignores it.
//    if h works, every smaller h works too, so most of the h values never need a check.
//
// 4. Key breaking point
//    monotone: if cnt(h) >= h, then for h' < h, cnt(h') >= cnt(h) >= h > h'
//    (a lower bar lets in at least the same papers). so "h works" is true .. true false .. false,
//    and the largest true is my binary search on answer: lo / hi / ans + bool check.
//
// 5. Method
//    step 1 : check(h) : count the papers with citations >= h, return true if count >= h.
//    step 2 : lo = 0, hi = n, ans = 0 (h = 0 always works).
//    step 3 : mid = lo + (hi - lo) / 2. if check(mid), ans = mid and look right: lo = mid + 1.
//             else look left: hi = mid - 1.
//    step 4 : return ans.
//
// 6. Why it works
//    the true h values are exactly 0 .. H (monotone, from 4), and every step keeps H inside
//    lo .. hi or already in ans, so ans ends at H.
//    time O(n log n): log n checks of O(n). extra space O(1).
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
bool check(ll h , vector<int>& citations)
{
    // this returns true if at least h papers have at least h citations each
    ll n = citations.size() ;
    ll cnt = 0 ;
    for(ll i = 0 ; i < n ; i++)
    {
        if(citations[i] >= h)
        {
            cnt++ ;
        }
    }
    if(cnt >= h)
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
    int hIndex(vector<int>& citations) {
        ll n = citations.size() ;
        // step 2 : h = 0 always works
        ll lo = 0 , hi = n , ans = 0 ;
        // step 3 : binary search on the answer
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2 ;
            if(check(mid , citations))
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
