// orz
// 36. Valid Sudoku · LeetCode · Medium
//
// Question:
// decide if a 9 x 9 sudoku board is valid. only the filled cells are checked:
// every row has the digits 1-9 at most once, every column has them at most once,
// and each of the nine 3 x 3 sub-boxes has them at most once.
// a valid board does not have to be solvable.
// Example 1: board =
//   ["53..7....","6..195...",".98....6.","8...6...3","4..8.3..1",
//    "7...2...6",".6....28.","...419..5","....8..79"]            -> true
// Example 2: the same board with board[0][0] = '8'               -> false
//            (two 8s in column 0 and two 8s in the top-left box)
// Constraints: board is 9 x 9, board[i][j] is a digit '1'-'9' or '.'
//
// 1. Mathematical statement
//    box(i, j) = (i / 3) * 3 + j / 3. valid iff no two different filled cells share a
//    digit and also share a row, or a column, or a box.
//
// 2. Brute force
//    for every filled cell, scan its row, its column and its box for the same digit.
//    81 cells * 24 other cells. fixed size, so it is fast, but it looks at every pair twice.
//
// 3. What the brute force wastes
//    it compares cells pair by pair, when a unit only needs to remember which
//    digits it has already seen.
//
// 4. Key breaking point
//    a repeat = some (row, digit), (column, digit) or (box, digit) is seen twice.
//    three seen tables, one pass over the board.
//
// 5. Method
//    step 1 : row[i][d], col[j][d], box[b][d] = 1 if digit d was already seen there. all 0.
//    step 2 : for every cell (i, j) : if it is '.', skip it.
//             d = board[i][j] - '0', b = (i / 3) * 3 + j / 3.
//    step 3 : if row[i][d] or col[j][d] or box[b][d] is already 1, return false.
//    step 4 : mark row[i][d] = col[j][d] = box[b][d] = 1.
//    step 5 : no repeat found, return true.
//
// 6. Why it works
//    when cell (i, j) is reached, row[i][d] == 1 exactly when an earlier cell of row i has d,
//    same for the column and the box. so step 3 fires on the second cell of every repeated
//    pair, and never otherwise.
//    time O(81), extra space O(3 * 9 * 10).
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
    bool isValidSudoku(vector<vector<char>>& board) {
        // step 1 : seen tables, index 1 .. 9 for the digit
        vector < vector < ll > > row(9 , vector < ll >(10 , 0)) ;
        vector < vector < ll > > col(9 , vector < ll >(10 , 0)) ;
        vector < vector < ll > > box(9 , vector < ll >(10 , 0)) ;
        for(ll i = 0 ; i < 9 ; i++)
        {
            for(ll j = 0 ; j < 9 ; j++)
            {
                // step 2
                if(board[i][j] == '.')
                {
                    continue ;
                }
                ll d = board[i][j] - '0' ;
                ll b = (i / 3) * 3 + j / 3 ;
                // step 3 : this digit is already in the row, the column or the box
                if(row[i][d] == 1 || col[j][d] == 1 || box[b][d] == 1)
                {
                    return false ;
                }
                // step 4
                row[i][d] = 1 ;
                col[j][d] = 1 ;
                box[b][d] = 1 ;
            }
        }
        // step 5
        return true ;
    }
};
