// orz
// 52. N-Queens II · LeetCode · Hard
//
// Question:
// the n-queens puzzle is placing n queens on an n x n chessboard so that no two queens
// attack each other (same row, same column or same diagonal).
// given an integer n, return the number of distinct solutions.
// Example 1: n = 4 -> 2
// Example 2: n = 1 -> 1
// Constraints: 1 <= n <= 9.
//
// 1. Mathematical statement
//    count the sets of n cells (r , c) where no two share a row, a column, r - c, or r + c.
//
// 2. Brute force
//    choose any n cells out of n^2 and check them. C(81 , 9) = 2.6 * 10^11. dead.
//
// 3. What the brute force wastes
//    n queens in n rows with no two in one row means exactly one queen per row,
//    and a set that already has two attacking queens gets completed anyway.
//
// 4. Key breaking point
//    this is my Chessboard and Queens rec: place the queen of row 0, then row 1, ...
//    in row `row` only try the columns where check(row , col) says nothing above attacks it.
//    a dead start is cut the moment it happens.
//
// 5. Method
//    step 1 : v = side x side board, v[r][c] = 1 if a queen stands there.
//    step 2 : check(row , col) : look straight up, up-left and up-right from (row , col).
//             only rows above have queens, so those 3 directions are enough.
//    step 3 : rec(row) = number of ways to place queens in rows row .. side - 1.
//             row = side : every row has its queen, that is 1 way.
//    step 4 : else for every col with check(row , col) : put the queen, cnt += rec(row + 1), take it away.
//    step 5 : reset the board, return rec(0).
//
// 6. Why it works
//    every solution has exactly one queen per row, so it is exactly one path of the rec
//    (its column in row 0, row 1, ...). check rejects a column iff a queen above attacks it,
//    so the paths that reach row = side are exactly the solutions.
//    time O(n!) at most (each row tries fewer columns), check is O(n). space O(n^2) for the board.
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
ll side ; // the board is side x side (n)
// step 1 : the board
vector < vector < ll > > v ;
bool check(ll row , ll col)
{
    // step 2 : this returns true if no queen above row attacks (row , col)
    for(ll i = 0 ; i < row ; i++)
    {
        if(v[i][col] == 1)
        {
            return false ;
        }
    }
    for(ll i = row - 1 , j = col - 1 ; i >= 0 && j >= 0 ; i-- , j--)
    {
        if(v[i][j] == 1)
        {
            return false ;
        }
    }
    for(ll i = row - 1 , j = col + 1 ; i >= 0 && j < side ; i-- , j++)
    {
        if(v[i][j] == 1)
        {
            return false ;
        }
    }
    return true ;
}
ll rec(ll row)
{
    // step 3 : this returns the number of ways to place queens from row to side - 1
    if(row == side)
    {
        return 1 ;
    }
    // step 4 : try every safe column of this row
    ll cnt = 0 ;
    for(ll col = 0 ; col < side ; col++)
    {
        if(check(row , col))
        {
            v[row][col] = 1 ;
            cnt += rec(row + 1) ;
            v[row][col] = 0 ;
        }
    }
    return cnt ;
}
class Solution {
public:
    int totalNQueens(int n) {
        // step 5 : reset every global, LeetCode keeps them between test cases
        side = n ;
        v.assign(side , vector < ll > (side , 0)) ;
        return rec(0) ;
    }
};
