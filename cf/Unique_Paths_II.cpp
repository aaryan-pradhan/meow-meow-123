// orz
// 63. Unique Paths II · LeetCode · Medium
//
// Question:
// a robot starts at the top left corner of an m x n grid and wants to reach the bottom
// right corner. it can only move down or right. obstacleGrid[i][j] == 1 is an obstacle,
// 0 is free, and a path may not use any obstacle cell. return the number of unique paths.
// the answer is at most 2 * 10^9.
// Example 1: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]] -> 2
// Example 2: obstacleGrid = [[0,1],[0,0]]             -> 1
// Constraints: m == obstacleGrid.length, n == obstacleGrid[i].length, 1 <= m, n <= 100,
//              obstacleGrid[i][j] is 0 or 1
//
// 1. Mathematical statement
//    count the sequences of cells from (0 , 0) to (m - 1 , n - 1), every step (i , j) ->
//    (i + 1 , j) or (i , j + 1), with every cell (both ends too) free.
//
// 2. Brute force
//    walk every path and drop the ones that hit an obstacle.
//    up to C(198 , 99), about 10^58 paths. dead.
//
// 3. What the brute force wastes
//    the number of ways to finish from (i , j) does not depend on how I got there.
//    every path through (i , j) walks all of them again.
//
// 4. Key breaking point
//    state = the cell (i , j), going to the corner: my Grid Paths DP
//    (trap -> 0, destination -> 1, else down + right). two rows are enough.
//
// 5. Method
//    step 1 : FORM = (i , j) -> end. rec(i , j) = the number of free paths from (i , j)
//             to (m - 1 , n - 1).
//    step 2 : CHOICE at (i , j) : down to (i + 1 , j) or right to (i , j + 1).
//    step 3 : CHECK : an obstacle on (i , j) -> 0 (this also covers a blocked start or
//             a blocked corner). the free corner itself -> 1.
//             a move off the grid gives 0.
//    step 4 : MOVE : rec(i , j) = down + right.
//    step 5 : cap. a cell the start cannot reach may still have a huge count
//             (a big free region walled off from the start can have ~10^58 paths to the
//             corner), and ll would overflow. so ways = min(down + right , CAP),
//             CAP = 2 * 10^9 + 1. any cell the start can reach has ways <= answer <= 2 * 10^9,
//             so it is never capped, and capped cells never feed rec(0 , 0).
//             down , right <= CAP, so down + right fits easily.
//    step 6 : COST : 10^4 states, 2 moves each. tiny.
//    step 7 : bottom up, i from m - 1 down to 0, j from n - 1 down to 0.
//    step 8 : rolling rows. dp[i & 1] is row i, dp[(i + 1) & 1] is row i + 1.
//             right reads dp[i & 1][j + 1], already written this pass.
//
// 6. Why it works
//    every free path from (i , j) goes down first or right first, never both, so the
//    counts add. rec(0 , 0) only ever reads cells that the start can reach (an obstacle
//    stops the reading), and those are exact, so the cap never touches the answer.
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
//     // this returns the number of free paths from (i , j) to (m - 1 , n - 1)
//     if(obstacleGrid[i][j] == 1)
//     {
//         return 0 ;
//     }
//     if(i == m - 1 && j == n - 1)
//     {
//         return 1 ;
//     }
//     if(dp[i][j] != -1)
//     {
//         return dp[i][j] ;
//     }
//     ll down = 0 , right = 0 ;
//     if(i + 1 < m)
//     {
//         down = rec(i + 1 , j) ;
//     }
//     if(j + 1 < n)
//     {
//         right = rec(i , j + 1) ;
//     }
//     return dp[i][j] = min(down + right , CAP) ;
// }
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        ll m = obstacleGrid.size() ;
        ll n = obstacleGrid[0].size() ;
        ll CAP = 2000000001 ;
        // step 8 : two rows, dp[i & 1]
        vector < vector < ll > > dp(2 , vector < ll > (n , 0)) ;
        // step 7 : from the corner back to the start
        for(ll i = m - 1 ; i >= 0 ; i--)
        {
            for(ll j = n - 1 ; j >= 0 ; j--)
            {
                // step 3 : obstacle
                if(obstacleGrid[i][j] == 1)
                {
                    dp[i & 1][j] = 0 ;
                    continue ;
                }
                // step 3 : the free corner
                if(i == m - 1 && j == n - 1)
                {
                    dp[i & 1][j] = 1 ;
                    continue ;
                }
                // step 4 : down + right, off the grid is 0
                ll down = 0 , right = 0 ;
                if(i + 1 < m)
                {
                    down = dp[(i + 1) & 1][j] ;
                }
                if(j + 1 < n)
                {
                    right = dp[i & 1][j + 1] ;
                }
                // step 5 : cap the cells the start cannot reach
                dp[i & 1][j] = min(down + right , CAP) ;
            }
        }
        return dp[0][0] ;
    }
};
