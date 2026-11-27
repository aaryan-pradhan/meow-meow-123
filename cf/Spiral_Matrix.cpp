// orz
// 54. Spiral Matrix · LeetCode · Medium
//
// Question:
// given an m x n matrix, return all its elements in spiral order (start at the
// top-left, go right, then down, then left, then up, turning inwards).
// Example 1: matrix = [[1,2,3],[4,5,6],[7,8,9]]            -> [1,2,3,6,9,8,7,4,5]
// Example 2: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]   -> [1,2,3,4,8,12,11,10,9,5,6,7]
// Constraints: 1 <= m, n <= 10, -100 <= matrix[i][j] <= 100
//
// 1. Mathematical statement
//    the rows top .. bottom and columns left .. right that are not printed yet always form
//    a rectangle. print its border clockwise (top row, right column, bottom row, left column),
//    then shrink it by one on every side and repeat until it is empty.
//
// 2. Brute force
//    walk with a direction and a visited grid, turn right when the next cell is outside
//    or visited. O(m * n) time, but O(m * n) extra for the visited grid.
//
// 3. What the brute force wastes
//    the visited cells are always whole outer rings, so a whole grid stores what four
//    numbers (top, bottom, left, right) already say.
//
// 4. Key breaking point
//    no trick: simulate the statement literally with four bounds.
//    the only care: after the top row and the right column, the rectangle may already be
//    empty (one row or one column left), so check before the bottom row and the left column.
//
// 5. Method
//    step 1 : top = 0, bottom = m - 1, left = 0, right = n - 1.
//             repeat while top <= bottom and left <= right :
//    step 2 : top row, j = left .. right, then top++.
//    step 3 : right column, i = top .. bottom, then right--.
//    step 4 : if top <= bottom : bottom row, j = right .. left, then bottom--.
//    step 5 : if left <= right : left column, i = bottom .. top, then left++.
//
// 6. Why it works
//    each step prints one side of the current rectangle and removes it, so every cell is
//    printed once, in clockwise ring order. the checks in steps 4 and 5 stop a single
//    remaining row or column from being printed twice.
//    time O(m * n), extra space O(1) besides the answer.
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
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        ll m = matrix.size() ;
        ll n = matrix[0].size() ;
        vector < int > ans ;
        // step 1 : the rectangle not printed yet
        ll top = 0 , bottom = m - 1 , left = 0 , right = n - 1 ;
        while(top <= bottom && left <= right)
        {
            // step 2 : top row, left to right
            for(ll j = left ; j <= right ; j++)
            {
                ans.push_back(matrix[top][j]) ;
            }
            top++ ;
            // step 3 : right column, top to bottom
            for(ll i = top ; i <= bottom ; i++)
            {
                ans.push_back(matrix[i][right]) ;
            }
            right-- ;
            // step 4 : bottom row, right to left, only if a row is left
            if(top <= bottom)
            {
                for(ll j = right ; j >= left ; j--)
                {
                    ans.push_back(matrix[bottom][j]) ;
                }
                bottom-- ;
            }
            // step 5 : left column, bottom to top, only if a column is left
            if(left <= right)
            {
                for(ll i = bottom ; i >= top ; i--)
                {
                    ans.push_back(matrix[i][left]) ;
                }
                left++ ;
            }
        }
        return ans ;
    }
};
