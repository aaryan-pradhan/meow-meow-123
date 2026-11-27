// orz
// 130. Surrounded Regions · LeetCode · Medium
//
// Question:
// given an m x n board of 'X' and 'O', capture every surrounded region in place.
// a region is a group of 'O' cells connected horizontally or vertically. it is
// surrounded when none of its cells is on the edge of the board. capturing a
// region turns all of its 'O' into 'X'. return nothing, change board itself.
// Example 1: board = [["X","X","X","X"],
//                     ["X","O","O","X"],
//                     ["X","X","O","X"],
//                     ["X","O","X","X"]]
//            ->       [["X","X","X","X"],
//                      ["X","X","X","X"],
//                      ["X","X","X","X"],
//                      ["X","O","X","X"]]   (the bottom 'O' is on the edge, it stays)
// Example 2: board = [["X"]] -> [["X"]]
// Constraints: 1 <= m , n <= 200, board[i][j] is 'X' or 'O'
//
// 1. Mathematical statement
//    graph: one node per 'O' cell, an edge between 'O' cells that share a side.
//    an 'O' cell stays 'O'  <=>  its component holds a cell on the border.
//    every other 'O' becomes 'X'.
//
// 2. Brute force
//    for every 'O' cell, flood fill from it and check if the fill touches the border.
//    O((m * n)^2) = 1.6 * 10^9 for an all-'O' 200 x 200 board. dead.
//
// 3. What the brute force wastes
//    every cell of a region fills the same region again, to get the same yes / no.
//
// 4. Key breaking point
//    turn the question around: the cells that stay are exactly the 'O' cells that can
//    be reached from a border 'O'. so start one bfs from ALL the border 'O' cells at once
//    (my multi-source bfs, like the monsters in Monsters). what it marks stays,
//    everything else that is 'O' is captured.
//
// 5. Method
//    step 1 : vis[x][y] = 0 for every cell, dx / dy for the 4 neighbours.
//    step 2 : push every 'O' on the border into the queue and mark it.
//    step 3 : bfs: push every neighbour that is inside the board, 'O', and not visited.
//    step 4 : scan the board: an 'O' with vis = 0 is surrounded, make it 'X'.
//
// 6. Why it works
//    a multi-source bfs marks exactly the cells joined to some source by a path of 'O' cells,
//    i.e. exactly the 'O' cells whose region touches the border. those must stay, and every
//    other 'O' sits in a region with no border cell, which is the definition of surrounded.
//    time O(m * n), every cell is pushed at most once. space O(m * n) for vis and the queue.
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
ll dx[] = {0 , 0 , 1 , -1} ;
ll dy[] = {1 , -1 , 0 , 0} ;
vector < vector < ll > > vis ;
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        ll n = board.size() ;
        ll m = board[0].size() ;
        // step 1 : reset vis, LeetCode keeps globals between test cases
        vis.assign(n , vector < ll > (m , 0)) ;
        // step 2 : every 'O' on the border is a source
        queue < pll > q ;
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll j = 0 ; j < m ; j++)
            {
                bool border = (i == 0 || i == n - 1 || j == 0 || j == m - 1) ;
                if(border && board[i][j] == 'O')
                {
                    vis[i][j] = 1 ;
                    q.push({i , j}) ;
                }
                else
                {
                    continue ;
                }
            }
        }
        // step 3 : bfs over 'O' cells from all the sources at once
        while(!q.empty())
        {
            pll p = q.front() ;
            q.pop() ;
            ll x = p.fr ;
            ll y = p.sc ;
            for(ll i = 0 ; i < 4 ; i++)
            {
                ll nx = x + dx[i] ;
                ll ny = y + dy[i] ;
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && board[nx][ny] == 'O')
                {
                    vis[nx][ny] = 1 ;
                    q.push({nx , ny}) ;
                }
            }
        }
        // step 4 : an 'O' the bfs never reached is surrounded
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll j = 0 ; j < m ; j++)
            {
                if(board[i][j] == 'O' && !vis[i][j])
                {
                    board[i][j] = 'X' ;
                }
                else
                {
                    continue ;
                }
            }
        }
    }
};
