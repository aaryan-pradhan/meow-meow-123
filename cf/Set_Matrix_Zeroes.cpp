// orz
// 73. Set Matrix Zeroes · LeetCode · Medium
//
// Question:
// given an m x n integer matrix, if a cell is 0, set its whole row and its whole
// column to 0. do it in place.
// Example 1: matrix = [[1,1,1],[1,0,1],[1,1,1]]           -> [[1,0,1],[0,0,0],[1,0,1]]
// Example 2: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]     -> [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
// Constraints: 1 <= m, n <= 200, -2^31 <= matrix[i][j] <= 2^31 - 1
// Follow up: O(m * n) space is easy, O(m + n) is better, can you use constant space? -> done here.
//
// 1. Mathematical statement
//    R = rows that have a 0, C = columns that have a 0 (in the ORIGINAL matrix).
//    new[i][j] = 0 if i is in R or j is in C, else matrix[i][j].
//
// 2. Brute force
//    copy the matrix, for every 0 in the copy, zero its row and column in the original.
//    O(m * n * (m + n)) time and O(m * n) extra space.
//
// 3. What the brute force wastes
//    only R and C matter, so m + n flags are enough (no copy). and the matrix already has
//    m + n cells to hold those flags: its first column and its first row.
//
// 4. Key breaking point
//    store "row i has a 0" in matrix[i][0] and "column j has a 0" in matrix[0][j].
//    those two lines get overwritten, so first save in two bools whether row 0 and
//    column 0 had a 0 of their own. then zero the inside, and the two lines LAST,
//    because they hold the flags.
//
// 5. Method
//    step 1 : row0 = row 0 has a 0, col0 = column 0 has a 0.
//    step 2 : for i >= 1, j >= 1 : if matrix[i][j] == 0, mark matrix[i][0] = 0 and matrix[0][j] = 0.
//    step 3 : for i >= 1, j >= 1 : if matrix[i][0] == 0 or matrix[0][j] == 0, matrix[i][j] = 0.
//    step 4 : if row0, zero row 0. if col0, zero column 0.
//
// 6. Why it works
//    after step 2, for i >= 1 : matrix[i][0] == 0 <=> row i is in R (a 0 at column 0 was
//    already there, a 0 further right got marked). same for matrix[0][j] and C. step 3 reads
//    these flags for every inside cell. cell (0, j) must be 0 if row0 or j is in C:
//    step 4 zeroes it when row0, and step 2 already made it 0 when j is in C.
//    column 0 is the same with col0 and R. step 3 reads the flags before step 4 erases them.
//    time O(m * n), extra space O(1).
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
    void setZeroes(vector<vector<int>>& matrix) {
        ll m = matrix.size() ;
        ll n = matrix[0].size() ;
        // step 1 : do row 0 and column 0 have a 0 of their own
        bool row0 = false , col0 = false ;
        for(ll j = 0 ; j < n ; j++)
        {
            if(matrix[0][j] == 0)
            {
                row0 = true ;
            }
        }
        for(ll i = 0 ; i < m ; i++)
        {
            if(matrix[i][0] == 0)
            {
                col0 = true ;
            }
        }
        // step 2 : flags in the first column and the first row
        for(ll i = 1 ; i < m ; i++)
        {
            for(ll j = 1 ; j < n ; j++)
            {
                if(matrix[i][j] == 0)
                {
                    matrix[i][0] = 0 ;
                    matrix[0][j] = 0 ;
                }
            }
        }
        // step 3 : zero the inside from the flags
        for(ll i = 1 ; i < m ; i++)
        {
            for(ll j = 1 ; j < n ; j++)
            {
                if(matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0 ;
                }
            }
        }
        // step 4 : the flag lines last
        if(row0)
        {
            for(ll j = 0 ; j < n ; j++)
            {
                matrix[0][j] = 0 ;
            }
        }
        if(col0)
        {
            for(ll i = 0 ; i < m ; i++)
            {
                matrix[i][0] = 0 ;
            }
        }
    }
};
