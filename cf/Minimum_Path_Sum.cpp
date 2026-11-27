// orz
// 64. Minimum Path Sum · LeetCode · Medium
//
// Question:
// given an m x n grid of non-negative numbers, find a path from the top left to the
// bottom right which minimises the sum of all numbers along its path.
// you can only move either down or right at any point in time.
// Example 1: grid = [[1,3,1],[1,5,1],[4,2,1]] -> 7   (1 -> 3 -> 1 -> 1 -> 1)
// Example 2: grid = [[1,2,3],[4,5,6]]         -> 12  (1 -> 2 -> 3 -> 6)
// Constraints: m == grid.length, n == grid[i].length, 1 <= m, n <= 200,
//              0 <= grid[i][j] <= 200
//
// 1. Mathematical statement
//    a path is a sequence of cells from (0 , 0) to (m - 1 , n - 1), every step (i , j) ->
//    (i + 1 , j) or (i , j + 1). minimise the sum of grid over the cells of the path.
//
// 2. Brute force
//    every path is a choice of which m - 1 of the m + n - 2 steps go down:
//    C(398 , 199) paths. dead.
//
// 3. What the brute force wastes
//    the best way from (i , j) to the corner does not care how I reached (i , j).
//    every path through (i , j) solves that same rest again.
//
// 4. Key breaking point
//    state = the cell (i , j), going to the bottom right corner. two moves, min.
//    row i reads only row i + 1 and itself, so two rows are enough.
//
// 5. Method
//    step 1 : FORM = (i , j) -> end. rec(i , j) = the smallest sum of a path from (i , j)
//             to (m - 1 , n - 1), grid[i][j] included.
//    step 2 : CHOICE at (i , j) : down to (i + 1 , j) or right to (i , j + 1).
//    step 3 : CHECK : (m - 1 , n - 1) is the corner, rec = grid[m - 1][n - 1].
//             a move off the grid is not allowed, it counts as INF.
//    step 4 : MOVE : down = rec(i + 1 , j) (INF if i + 1 == m), right = rec(i , j + 1)
//             (INF if j + 1 == n). rec(i , j) = grid[i][j] + min(down , right).
//    step 5 : COST : 4 * 10^4 states, 2 moves each. tiny.
//    step 6 : bottom up, i from m - 1 down to 0, j from n - 1 down to 0, so the cell
//             below and the cell to the right are ready.
//    step 7 : rolling rows. dp[i & 1] is row i, dp[(i + 1) & 1] is row i + 1.
//             right reads dp[i & 1][j + 1], already written this pass.
//
// 6. Why it works
//    a path from (i , j) takes grid[i][j] and then is a path from the cell below or
//    from the cell to the right, whichever exists. the better of the two best
//    continuations is the best path. away from the corner at least one move exists,
//    so INF never reaches the answer.
//    time O(m * n), extra space O(n).
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
//     // this returns the smallest sum of a path from (i , j) to (m - 1 , n - 1)
//     if(i == m - 1 && j == n - 1)
//     {
//         return grid[i][j] ;
//     }
//     if(dp[i][j] != -1)
//     {
//         return dp[i][j] ;
//     }
//     ll down = INF , right = INF ;
//     if(i + 1 < m)
//     {
//         down = rec(i + 1 , j) ;
//     }
//     if(j + 1 < n)
//     {
//         right = rec(i , j + 1) ;
//     }
//     return dp[i][j] = grid[i][j] + min(down , right) ;
// }
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        ll m = grid.size() ;
        ll n = grid[0].size() ;
        // step 7 : two rows, dp[i & 1]
        vector < vector < ll > > dp(2 , vector < ll > (n , 0)) ;
        // step 6 : from the corner back to the start
        for(ll i = m - 1 ; i >= 0 ; i--)
        {
            for(ll j = n - 1 ; j >= 0 ; j--)
            {
                // step 3 : the corner
                if(i == m - 1 && j == n - 1)
                {
                    dp[i & 1][j] = grid[i][j] ;
                    continue ;
                }
                // step 4 : down or right, off the grid is INF
                ll down = INF , right = INF ;
                if(i + 1 < m)
                {
                    down = dp[(i + 1) & 1][j] ;
                }
                if(j + 1 < n)
                {
                    right = dp[i & 1][j + 1] ;
                }
                dp[i & 1][j] = grid[i][j] + min(down , right) ;
            }
        }
        return dp[0][0] ;
    }
};
