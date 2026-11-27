// orz
// 909. Snakes and Ladders · LeetCode · Medium
//
// Question:
// an n x n board has its squares labelled 1 .. n^2 in boustrophedon order: starting at the
// bottom-left board[n - 1][0], the bottom row goes left to right, the next row up goes
// right to left, and so on, alternating. you start on square 1. in one move from curr,
// pick next in [curr + 1 , min(curr + 6 , n^2)] (a die roll). if board at next is not -1,
// a snake or ladder sends you to square board[r][c]. you follow at most one snake or
// ladder per move, even if it lands you on the start of another one.
// the game ends on square n^2. return the fewest moves to reach n^2, or -1 if you can't.
// Example 1: board = [[-1,-1,-1,-1,-1,-1],
//                     [-1,-1,-1,-1,-1,-1],
//                     [-1,-1,-1,-1,-1,-1],
//                     [-1,35,-1,-1,13,-1],
//                     [-1,-1,-1,-1,-1,-1],
//                     [-1,15,-1,-1,-1,-1]]  -> 4   (1 -> 2 (ladder 15) -> 17 (snake 13) -> 14 (ladder 35) -> 36)
// Example 2: board = [[-1,-1],[-1,3]]       -> 1
// Constraints: 2 <= n <= 20, board[r][c] is -1 or in [1 , n^2],
//              squares 1 and n^2 are not the start of a snake or ladder.
//
// 1. Mathematical statement
//    jump(s) = board value at square s if it is not -1, else s.
//    graph on squares 1 .. n^2: edge s -> jump(s + d) for d = 1 .. 6, s + d <= n^2.
//    return the length of the shortest path 1 -> n^2, or -1.
//
// 2. Brute force
//    try every sequence of die rolls of length 1, 2, 3, .. until one reaches n^2.
//    6^k sequences of length k, and k can be about n^2 / 6 = 67. dead.
//
// 3. What the brute force wastes
//    many roll sequences end on the same square after the same number of moves,
//    and from there they all continue the same way.
//
// 4. Key breaking point
//    the state is just the square. every move costs 1, so "fewest moves" is my
//    unweighted BFS (Message Route): dist[child] = dist[node] + 1, mark when pushed.
//    the only work is turning a label s into (row , col) on the board.
//
// 5. Method
//    step 1 : for every s: k = (s - 1) / n is the row counted from the bottom,
//             c = (s - 1) % n, flipped to n - 1 - c on odd k (those rows go right to left).
//             board row r = n - 1 - k. jump[s] = board[r][c] if it is not -1, else s.
//    step 2 : g[s].push_back(jump[s + d]) for d = 1 .. 6 with s + d <= n^2.
//    step 3 : bfs from 1, dist = -1 means not visited.
//    step 4 : return dist[n^2] (-1 if never reached).
//
// 6. Why it works
//    one move from s lands exactly on jump(s + d) for the rolled d: the move follows the
//    snake or ladder at s + d (if any) once and stops, which is what jump does.
//    so moves = edges of g, and BFS gives the fewest edges. time O(n^2 * 6),
//    space O(n^2).
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
    int snakesAndLadders(vector<vector<int>>& board) {
        ll n = board.size() ;
        ll last = n * n ;
        // step 1 : jump[s] = the square you end on when a roll lands on s
        vector < ll > jump(last + 1 , 0) ;
        for(ll s = 1 ; s <= last ; s++)
        {
            ll k = (s - 1) / n ; // row counted from the bottom
            ll c = (s - 1) % n ;
            if(k % 2 == 1)
            {
                c = n - 1 - c ; // odd rows from the bottom go right to left
            }
            ll r = n - 1 - k ;
            if(board[r][c] == -1)
            {
                jump[s] = s ;
            }
            else
            {
                jump[s] = board[r][c] ;
            }
        }
        // step 2 : one move = a roll of 1 .. 6, then at most one jump
        vector < vector < ll > > g(last + 1) ;
        for(ll s = 1 ; s <= last ; s++)
        {
            for(ll d = 1 ; d <= 6 ; d++)
            {
                if(s + d <= last)
                {
                    g[s].push_back(jump[s + d]) ;
                }
            }
        }
        // step 3 : bfs from square 1
        vector < ll > dist(last + 1 , -1) ;
        queue < ll > q ;
        q.push(1) ;
        dist[1] = 0 ;
        while(!q.empty())
        {
            ll node = q.front() ;
            q.pop() ;
            for(auto child : g[node])
            {
                if(dist[child] == -1)
                {
                    dist[child] = dist[node] + 1 ;
                    q.push(child) ;
                }
            }
        }
        // step 4
        return dist[last] ;
    }
};
