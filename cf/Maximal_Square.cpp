// orz
// 221. Maximal Square · LeetCode · Medium
//
// Question:
// given an m x n binary matrix filled with '0's and '1's, find the largest square
// containing only '1's and return its area.
// Example 1: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],
//                      ["1","1","1","1","1"],["1","0","0","1","0"]] -> 4
// Example 2: matrix = [["0","1"],["1","0"]]                         -> 1
// Example 3: matrix = [["0"]]                                       -> 0
// Constraints: m == matrix.length, n == matrix[i].length, 1 <= m, n <= 300,
//              matrix[i][j] is '0' or '1'
//
// 1. Mathematical statement
//    the largest s >= 0 such that some s x s block matrix[i .. i + s - 1][j .. j + s - 1]
//    is all '1'. return s * s.
//
// 2. Brute force
//    every top left corner, every side, check every cell of the block.
//    O(m * n * min(m , n) * s^2), about 300^5 = 2.4 * 10^12. dead.
//
// 3. What the brute force wastes
//    checking the s x s block at (i , j) re-checks the (s - 1) x (s - 1) blocks at
//    (i , j + 1), (i + 1 , j) and (i + 1 , j + 1), which were already checked.
//
// 4. Key breaking point
//    an s x s block of '1' at (i , j) = cell (i , j) is '1' and the three
//    (s - 1) x (s - 1) blocks at right, down and diagonal are all '1' (together they
//    cover the whole block except (i , j)). so the biggest side at (i , j) is
//    1 + min of the three biggest sides. a grid DP, two rows.
//
// 5. Method
//    step 1 : FORM = (i , j) -> end. rec(i , j) = the side of the largest all '1' square
//             whose top left corner is (i , j).
//    step 2 : CHECK : matrix[i][j] == '0' -> 0.
//             last row or last column (and '1') -> 1, no room to grow.
//    step 3 : MOVE : right = rec(i , j + 1), down = rec(i + 1 , j), diag = rec(i + 1 , j + 1),
//             rec(i , j) = 1 + min(right , down , diag).
//    step 4 : COST : 9 * 10^4 states, 3 moves. tiny.
//    step 5 : bottom up, i from m - 1 down to 0, j from n - 1 down to 0.
//    step 6 : rolling rows. dp[i & 1] is row i, dp[(i + 1) & 1] is row i + 1.
//             right reads dp[i & 1][j + 1], already written this pass.
//    step 7 : best = max of every rec(i , j). return best * best.
//
// 6. Why it works
//    if rec(i , j) = 1 + t with t = the min of the three, the three t x t squares plus
//    the cell (i , j) cover the (t + 1) x (t + 1) block, so it is all '1'. and a
//    (t + 2) x (t + 2) block would need all three neighbours to have side t + 1, which
//    the smallest one does not. so rec(i , j) is exact, and the best corner gives the answer.
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
//     // this returns the side of the largest all '1' square with its top left corner at (i , j)
//     if(matrix[i][j] == '0')
//     {
//         return 0 ;
//     }
//     if(i == m - 1 || j == n - 1)
//     {
//         return 1 ;
//     }
//     if(dp[i][j] != -1)
//     {
//         return dp[i][j] ;
//     }
//     ll right = rec(i , j + 1) ;
//     ll down = rec(i + 1 , j) ;
//     ll diag = rec(i + 1 , j + 1) ;
//     return dp[i][j] = 1 + min({right , down , diag}) ;
// }
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        ll m = matrix.size() ;
        ll n = matrix[0].size() ;
        // step 6 : two rows, dp[i & 1]
        vector < vector < ll > > dp(2 , vector < ll > (n , 0)) ;
        ll best = 0 ;
        // step 5 : from the bottom right back to the top left
        for(ll i = m - 1 ; i >= 0 ; i--)
        {
            for(ll j = n - 1 ; j >= 0 ; j--)
            {
                // step 2 : a '0' starts no square
                if(matrix[i][j] == '0')
                {
                    dp[i & 1][j] = 0 ;
                    continue ;
                }
                // step 2 : last row or last column
                if(i == m - 1 || j == n - 1)
                {
                    dp[i & 1][j] = 1 ;
                }
                // step 3 : grow from right, down and diagonal
                else
                {
                    ll right = dp[i & 1][j + 1] ;
                    ll down = dp[(i + 1) & 1][j] ;
                    ll diag = dp[(i + 1) & 1][j + 1] ;
                    dp[i & 1][j] = 1 + min({right , down , diag}) ;
                }
                // step 7 : biggest side so far
                best = max(best , dp[i & 1][j]) ;
            }
        }
        // step 7
        return best * best ;
    }
};
