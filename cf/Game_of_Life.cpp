// orz
// 289. Game of Life · LeetCode · Medium
//
// Question:
// an m x n board, every cell is live (1) or dead (0). each cell looks at its 8
// neighbours (horizontal, vertical, diagonal):
//   a live cell with fewer than 2 live neighbours dies,
//   a live cell with 2 or 3 live neighbours lives on,
//   a live cell with more than 3 live neighbours dies,
//   a dead cell with exactly 3 live neighbours becomes live.
// all cells change at the same time. write the next state into board (return nothing).
// Example 1: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]] -> [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
// Example 2: board = [[1,1],[1,0]]                     -> [[1,1],[1,1]]
// Constraints: 1 <= m, n <= 25, board[i][j] is 0 or 1
// Follow up: solve it in place (every cell must still see its neighbours' OLD state). -> done here.
//
// 1. Mathematical statement
//    live(i, j) = number of (x, y) != (i, j) with |x - i| <= 1, |y - j| <= 1, inside the
//    board, and old[x][y] == 1.
//    new[i][j] = 1 iff live(i, j) == 3, or old[i][j] == 1 and live(i, j) == 2.
//
// 2. Brute force
//    copy the board, count every neighbour in the copy, write into board.
//    O(m * n * 8) time, but O(m * n) extra space for the copy.
//
// 3. What the brute force wastes
//    each cell is 0 or 1, so it uses one bit of an int. the copy is only there to keep
//    the old state readable, and the spare bits of the same int can hold the new state.
//
// 4. Key breaking point
//    keep two states in one cell: bit 0 = old state, bit 1 = new state.
//    neighbours read only bit 0 (board[x][y] & 1), which nobody changes during the pass.
//    at the end shift every cell right by one: the new state drops into bit 0.
//
// 5. Method
//    step 1 : for every cell, count live = neighbours with (board[x][y] & 1) == 1,
//             using my 8 dx / dy moves and the inside-the-board check.
//    step 2 : next = 1 if (old is live and live is 2 or 3) or (old is dead and live is 3), else 0.
//    step 3 : if next == 1, board[i][j] |= 2 (set bit 1, bit 0 stays the old state).
//    step 4 : second pass, board[i][j] >>= 1.
//
// 6. Why it works
//    during the first pass bit 0 of every cell is never changed, so every count sees only
//    old states, as if all cells changed at the same time. step 2 is the four rules merged
//    (a live cell survives on 2 or 3, a dead cell is born on 3, every other case is dead).
//    step 4 turns 0b(new)(old) into new.
//    time O(m * n * 8), extra space O(1).
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
ll dx[] = {-1, -1, -1, 0, 0, 1, 1, 1} ;
ll dy[] = {-1, 0, 1, -1, 1, -1, 0, 1} ;
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        ll m = board.size() ;
        ll n = board[0].size() ;
        for(ll i = 0 ; i < m ; i++)
        {
            for(ll j = 0 ; j < n ; j++)
            {
                // step 1 : live neighbours, old state is bit 0
                ll live = 0 ;
                for(ll d = 0 ; d < 8 ; d++)
                {
                    ll nx = i + dx[d] , ny = j + dy[d] ;
                    if(nx >= 0 && nx < m && ny >= 0 && ny < n && (board[nx][ny] & 1) == 1)
                    {
                        live++ ;
                    }
                }
                // step 2 : the four rules
                ll next = 0 ;
                if((board[i][j] & 1) == 1)
                {
                    if(live == 2 || live == 3)
                    {
                        next = 1 ;
                    }
                }
                else
                {
                    if(live == 3)
                    {
                        next = 1 ;
                    }
                }
                // step 3 : new state into bit 1
                if(next == 1)
                {
                    board[i][j] |= 2 ;
                }
            }
        }
        // step 4 : new state drops into bit 0
        for(ll i = 0 ; i < m ; i++)
        {
            for(ll j = 0 ; j < n ; j++)
            {
                board[i][j] >>= 1 ;
            }
        }
    }
};
