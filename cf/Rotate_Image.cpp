// orz
// 48. Rotate Image · LeetCode · Medium
//
// Question:
// given an n x n matrix (an image), rotate it by 90 degrees clockwise.
// do it in place: change the input matrix, do not make another 2D matrix.
// Example 1: matrix = [[1,2,3],[4,5,6],[7,8,9]] -> [[7,4,1],[8,5,2],[9,6,3]]
// Example 2: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
//            -> [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
// Constraints: 1 <= n <= 20, -1000 <= matrix[i][j] <= 1000
//
// 1. Mathematical statement
//    the value at (i, j) moves to (j, n - 1 - i).
//    (row 0 becomes the last column, read top to bottom.)
//
// 2. Brute force
//    make a new matrix b, b[j][n - 1 - i] = a[i][j], copy b back.
//    O(n^2) time but O(n^2) extra space, which is banned.
//
// 3. What the brute force wastes
//    the copy. the move (i, j) -> (j, n - 1 - i) is two simple moves glued together,
//    and each of them only swaps pairs of cells, which needs no copy.
//
// 4. Key breaking point
//    (i, j) -> (j, i)          is the transpose (mirror on the main diagonal),
//    (j, i) -> (j, n - 1 - i)  is mirroring every row (left <-> right).
//    together : (i, j) -> (j, n - 1 - i), the rotation. both are pair swaps, so in place.
//
// 5. Method
//    step 1 : transpose. for every i and every j > i, swap matrix[i][j] and matrix[j][i].
//             (j > i only, or every pair is swapped twice and nothing moves.)
//    step 2 : mirror every row. l = 0, r = n - 1, swap matrix[i][l] and matrix[i][r],
//             l++, r--, while l < r.
//
// 6. Why it works
//    after step 1 the value from (i, j) sits at (j, i). step 2 moves column c of every row
//    to column n - 1 - c, so it ends at (j, n - 1 - i), the rotated place.
//    time O(n^2), extra space O(1).
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
    void rotate(vector<vector<int>>& matrix) {
        ll n = matrix.size() ;
        // step 1 : transpose, (i, j) -> (j, i)
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll j = i + 1 ; j < n ; j++)
            {
                swap(matrix[i][j] , matrix[j][i]) ;
            }
        }
        // step 2 : mirror every row, (j, i) -> (j, n - 1 - i)
        for(ll i = 0 ; i < n ; i++)
        {
            ll l = 0 , r = n - 1 ;
            while(l < r)
            {
                swap(matrix[i][l] , matrix[i][r]) ;
                l++ ;
                r-- ;
            }
        }
    }
};
