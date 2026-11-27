// orz
// 57. Insert Interval · LeetCode · Medium
//
// Question:
// given an array of non-overlapping intervals sorted by start, and one more
// interval newInterval = [start, end], insert newInterval so that the intervals
// stay sorted by start and non-overlapping (merge where needed, touching counts
// as overlapping). return the result.
// Example 1: intervals = [[1,3],[6,9]], newInterval = [2,5]   -> [[1,5],[6,9]]
// Example 2: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
//            -> [[1,2],[3,10],[12,16]]
// Constraints: 0 <= n <= 10^4, intervals[i].length == 2, 0 <= start <= end <= 10^5,
//              intervals is sorted by start and non-overlapping,
//              newInterval.length == 2, 0 <= start <= end <= 10^5
//
// 1. Mathematical statement
//    output the connected pieces of (union of intervals) + [L, R], sorted,
//    where [L, R] = newInterval.
//
// 2. Brute force
//    append newInterval and run 56 Merge Intervals: sort + sweep. O(n log n).
//
// 3. What the brute force wastes
//    the input is already sorted and already merged. only one interval is out of
//    place, and the sort spends n log n to fix one position.
//
// 4. Key breaking point
//    against [L, R] every old interval [l, r] is one of three kinds, and they come
//    in this order: fully left (r < L), touching (l <= R and r >= L), fully right
//    (l > R). the touching ones all melt into [L, R]. so: copy, melt, copy. one pass.
//
// 5. Method
//    step 1 : i = 0. while intervals[i] ends before L (r < L), copy it.
//    step 2 : while intervals[i] starts at or before R (l <= R), it touches:
//             L = min(L , l), R = max(R , r).
//    step 3 : push the melted [L, R].
//    step 4 : copy every interval that is left (all start after R), return.
//
// 6. Why it works
//    sorted and disjoint means the ends are sorted too, so the r < L ones form a
//    prefix. after them every interval has r >= L, so it touches [L, R] exactly
//    when l <= R, and since the starts are sorted the touching ones come first.
//    R only grows while melting, so the melt loop takes exactly them. the rest
//    start after the final R and stay as they are, already sorted.
//    time O(n), extra space O(1) besides the answer.
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
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        ll n = intervals.size() ;
        ll L = newInterval[0] ;
        ll R = newInterval[1] ;
        vector < vector < int > > ans ;
        // step 1 : copy the intervals fully left of [L, R]
        ll i = 0 ;
        while(i < n && intervals[i][1] < L)
        {
            ans.push_back(intervals[i]) ;
            i++ ;
        }
        // step 2 : melt every interval that touches [L, R]
        while(i < n && intervals[i][0] <= R)
        {
            L = min(L , (ll)intervals[i][0]) ;
            R = max(R , (ll)intervals[i][1]) ;
            i++ ;
        }
        // step 3
        ans.push_back({(int)L , (int)R}) ;
        // step 4 : copy the intervals fully right
        while(i < n)
        {
            ans.push_back(intervals[i]) ;
            i++ ;
        }
        return ans ;
    }
};
