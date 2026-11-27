// orz
// 120. Triangle · LeetCode · Medium
//
// Question:
// given a triangle array, return the minimum path sum from top to bottom.
// from index j on row i you may move to index j or index j + 1 on row i + 1.
// Example 1: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]] -> 11  (2 + 3 + 5 + 1)
// Example 2: triangle = [[-10]]                       -> -10
// Constraints: 1 <= triangle.length <= 200, triangle[0].length == 1,
//              triangle[i].length == triangle[i - 1].length + 1, -10^4 <= triangle[i][j] <= 10^4
// Follow up: only O(n) extra space, n = the number of rows. -> done here.
//
// 1. Mathematical statement
//    choose j0 = 0 and j(i + 1) in {j(i) , j(i) + 1} for every row i.
//    minimise the sum of triangle[i][j(i)] over i = 0 .. n - 1.
//
// 2. Brute force
//    every path makes n - 1 left / right choices: 2^(n - 1) paths, n = 200. dead.
//
// 3. What the brute force wastes
//    once a path stands on (i , j), the best way down from there does not care how
//    it got there. every path through (i , j) recomputes the same way down.
//
// 4. Key breaking point
//    state = the cell (i , j), going down to the last row: a grid DP with 2 moves.
//    row i only reads row i + 1, so two rows are enough (the follow up).
//
// 5. Method
//    step 1 : FORM = i -> end. rec(i , j) = the smallest sum of a path from (i , j)
//             down to the last row, triangle[i][j] included.
//    step 2 : CHOICE at (i , j) : go to (i + 1 , j) or to (i + 1 , j + 1).
//    step 3 : CHECK : i == n - 1 is the last row, rec = triangle[i][j].
//             both moves always exist above the last row (row i + 1 has i + 2 cells).
//    step 4 : MOVE : down = rec(i + 1 , j), downright = rec(i + 1 , j + 1),
//             rec(i , j) = triangle[i][j] + min(down , downright).
//    step 5 : COST : n^2 / 2 = 2 * 10^4 states, 2 moves each. tiny.
//    step 6 : bottom up, i from n - 1 down to 0, j from 0 to i.
//    step 7 : rolling rows. row i only reads row i + 1.
//             dp[i & 1] is row i, dp[(i + 1) & 1] is row i + 1. answer dp[0][0].
//
// 6. Why it works
//    a path from (i , j) takes triangle[i][j] and then is a path from (i + 1 , j) or
//    from (i + 1 , j + 1). the best of the two best continuations is the best path.
//    sums stay within 200 * 10^4 in size, no overflow.
//    time O(n^2), extra space O(n): 2 rows of n.
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
// ll rec(ll i , ll j)
// {
//     // this returns the smallest sum of a path from (i , j) down to the last row
//     if(i == n - 1)
//     {
//         return triangle[i][j] ;
//     }
//     if(dp[i][j] != -1)
//     {
//         return dp[i][j] ;
//     }
//     ll down = rec(i + 1 , j) ;
//     ll downright = rec(i + 1 , j + 1) ;
//     return dp[i][j] = triangle[i][j] + min(down , downright) ;
// }
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        ll n = triangle.size() ;
        // step 7 : two rows, dp[i & 1]
        vector < vector < ll > > dp(2 , vector < ll > (n , 0)) ;
        // step 6 : i from the last row up to the top
        for(ll i = n - 1 ; i >= 0 ; i--)
        {
            for(ll j = 0 ; j <= i ; j++)
            {
                // step 3 : last row
                if(i == n - 1)
                {
                    dp[i & 1][j] = triangle[i][j] ;
                    continue ;
                }
                // step 4 : go down or down right
                ll down = dp[(i + 1) & 1][j] ;
                ll downright = dp[(i + 1) & 1][j + 1] ;
                dp[i & 1][j] = triangle[i][j] + min(down , downright) ;
            }
        }
        return dp[0][0] ;
    }
};
