// orz
// 56. Merge Intervals · LeetCode · Medium
//
// Question:
// given an array of intervals where intervals[i] = [start, end], merge all the
// overlapping intervals (touching ones like [1,4] and [4,5] overlap too), and
// return the non-overlapping intervals that cover exactly the same points.
// Example 1: intervals = [[1,3],[2,6],[8,10],[15,18]]   -> [[1,6],[8,10],[15,18]]
// Example 2: intervals = [[1,4],[4,5]]                  -> [[1,5]]
// Example 3: intervals = [[4,7],[1,4]]                  -> [[1,7]]
// Constraints: 1 <= n <= 10^4, intervals[i].length == 2, 0 <= start <= end <= 10^4
//
// 1. Mathematical statement
//    U = union of all [start, end]. output the connected pieces of U, each as
//    [its min, its max], in any order.
//
// 2. Brute force
//    keep merging: find any two intervals that overlap, replace them by their union,
//    repeat until no pair overlaps. each round is O(n^2) pair checks, up to n rounds.
//    O(n^3) = 10^12. dead.
//
// 3. What the brute force wastes
//    it compares intervals that are far apart and can never touch. if the intervals
//    are in order of start, an interval can only touch the piece that is being
//    built right now, never an older one.
//
// 4. Key breaking point
//    sort by start. then it is my painted bricks sweep: keep the current piece
//    [curl, curr]. the next interval either starts inside it (l <= curr: extend curr)
//    or starts after it (l > curr: the piece is finished, flush it, start a new one).
//
// 5. Method
//    step 1 : sort the intervals by start (sort on vector < int > compares start first).
//    step 2 : curl, curr = the first interval.
//    step 3 : for every next [l , r]:
//             if l <= curr, it overlaps or touches: curr = max(curr , r).
//             else flush [curl , curr] and start the new piece [l , r].
//    step 4 : flush the last piece after the loop, return.
//
// 6. Why it works
//    after the sort, every later interval starts at l >= curl. if l > curr then
//    every later one also starts after curr, so nothing can join the piece anymore:
//    flushing it is safe. if l <= curr the two touch, so they belong to one piece.
//    time O(n log n) for the sort, extra space O(1) besides the answer.
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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        ll n = intervals.size() ;
        // step 1 : sort by start
        sort(intervals.begin() , intervals.end()) ;
        // step 2 : the piece being built
        vector < vector < int > > ans ;
        ll curl = intervals[0][0] ;
        ll curr = intervals[0][1] ;
        // step 3 : extend or flush
        for(ll i = 1 ; i < n ; i++)
        {
            ll l = intervals[i][0] ;
            ll r = intervals[i][1] ;
            if(l <= curr)
            {
                curr = max(curr , r) ;
            }
            else
            {
                ans.push_back({(int)curl , (int)curr}) ;
                curl = l ;
                curr = r ;
            }
        }
        // step 4 : the last piece
        ans.push_back({(int)curl , (int)curr}) ;
        return ans ;
    }
};
