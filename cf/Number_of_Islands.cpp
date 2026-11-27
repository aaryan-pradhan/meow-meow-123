// orz
// 200. Number of Islands · LeetCode · Medium
//
// Question:
// given an m x n grid of '1' (land) and '0' (water), return the number of
// islands. an island is land connected horizontally or vertically, surrounded
// by water. all four edges of the grid are surrounded by water.
// Example 1: grid = [["1","1","1","1","0"],
//                    ["1","1","0","1","0"],
//                    ["1","1","0","0","0"],
//                    ["0","0","0","0","0"]]  -> 1
// Example 2: grid = [["1","1","0","0","0"],
//                    ["1","1","0","0","0"],
//                    ["0","0","1","0","0"],
//                    ["0","0","0","1","1"]]  -> 3
// Constraints: 1 <= m , n <= 300, grid[i][j] is '0' or '1'
//
// 1. Mathematical statement
//    graph: one node per land cell, an edge between land cells that share a side.
//    return the number of connected components of this graph.
//
// 2. Brute force
//    for every land cell, flood fill its whole island from scratch and give the island
//    the name of its smallest cell. count the different names.
//    O((m * n)^2) = 8 * 10^9 for an all-land 300 x 300 grid. dead.
//
// 3. What the brute force wastes
//    all the cells of one island fill the same island again, once each.
//
// 4. Key breaking point
//    a count of regions is my Counting Rooms: flood fill once per region, and a cell
//    visited by any fill is never started again. the answer is the number of launches.
//    I fill with bfs, not dfs: an all-land grid would make the dfs 9 * 10^4 calls deep.
//
// 5. Method
//    step 1 : vis[x][y] = 0 for every cell, dx / dy for the 4 neighbours.
//    step 2 : scan every cell. a land cell with vis = 0 starts a new island: ans++, bfs from it.
//    step 3 : bfs(x , y): queue of cells, mark vis when pushed, push every neighbour that
//             is inside the grid, land, and not visited.
//    step 4 : return ans.
//
// 6. Why it works
//    a bfs from a cell marks exactly the cells of its island: every land neighbour is pushed,
//    and it never crosses water. so the first unvisited land cell of an island launches one bfs,
//    which marks the whole island, and no other cell of it launches again.
//    so launches = islands. time O(m * n): every cell is pushed at most once and has 4 neighbours.
//    space O(m * n) for vis and the queue.
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
void bfs(ll sx , ll sy , ll n , ll m , vector<vector<char>>& grid)
{
    // this marks every land cell of the island of (sx , sy) as visited
    queue < pll > q ;
    q.push({sx , sy}) ;
    vis[sx][sy] = 1 ;
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
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && grid[nx][ny] == '1')
            {
                vis[nx][ny] = 1 ;
                q.push({nx , ny}) ;
            }
        }
    }
}
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        ll n = grid.size() ;
        ll m = grid[0].size() ;
        // step 1 : reset vis, LeetCode keeps globals between test cases
        vis.assign(n , vector < ll > (m , 0)) ;
        // step 2 : every unvisited land cell starts a new island
        ll ans = 0 ;
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll j = 0 ; j < m ; j++)
            {
                if(!vis[i][j] && grid[i][j] == '1')
                {
                    ans++ ;
                    // step 3 : mark the whole island
                    bfs(i , j , n , m , grid) ;
                }
                else
                {
                    continue ;
                }
            }
        }
        // step 4
        return ans ;
    }
};
