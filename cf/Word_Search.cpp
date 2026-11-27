// orz
// 79. Word Search · LeetCode · Medium
//
// Question:
// given an m x n grid of characters board and a string word, return true if word exists
// in the grid. the word must be built from letters of sequentially adjacent cells
// (horizontal or vertical neighbours). the same cell may not be used more than once.
// Example 1: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED" -> true
// Example 2: same board, word = "SEE"  -> true
// Example 3: same board, word = "ABCB" -> false
// Constraints: 1 <= m, n <= 6, 1 <= word.length <= 15, board and word are upper and lower case English letters.
//
// 1. Mathematical statement
//    is there a sequence of distinct cells c0 .. c(L - 1), each next to the one before,
//    with board[ci] = word[i] for every i ?
//
// 2. Brute force
//    walk every path of L distinct cells from every start, compare at the end.
//    36 starts * 4 * 3^14 paths. dead.
//
// 3. What the brute force wastes
//    a path whose first letters already differ from word is still walked to full length.
//
// 4. Key breaking point
//    compare letter by letter while walking: my grid dfs (dx / dy, vis), where a cell is only
//    entered if its letter is the next letter of word. a wrong letter kills the path at once.
//    vis is undone when the dfs leaves a cell, because another path may use that cell.
//
// 5. Method
//    step 1 : dfs(x , y , i) = true if word[i ..] can be spelled with the path starting at (x , y),
//             using only cells not in vis.
//    step 2 : board[x][y] != word[i] : false.
//    step 3 : i = L - 1 : the last letter matched, true.
//    step 4 : vis[x][y] = 1. for each of the 4 neighbours inside the board and not visited:
//             if dfs(nx , ny , i + 1) is true, return true. then vis[x][y] = 0, return false.
//    step 5 : reset vis, try dfs(x , y , 0) from every cell.
//
// 6. Why it works
//    the dfs walks exactly the paths of distinct cells whose letters match word[0 .. i],
//    and it tries every neighbour, so if a matching path of length L exists it is found.
//    time O(m * n * 4 * 3^(L - 1)) in the worst case, space O(m * n + L).
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
ll n , m ;
vector < vector < ll > > vis ;
ll dx[] = {0, 0, 1, -1};
ll dy[] = {1, -1, 0, 0};
bool dfs(ll x , ll y , ll i , vector < vector < char > >& board , string& word)
{
    // step 1 : this returns true if word[i ..] can be spelled starting at (x , y) with unvisited cells
    // step 2 : wrong letter
    if(board[x][y] != word[i])
    {
        return false ;
    }
    // step 3 : last letter matched
    if(i == (ll)word.size() - 1)
    {
        return true ;
    }
    // step 4 : go on to the neighbours
    vis[x][y] = 1 ;
    for(ll k = 0 ; k < 4 ; k++)
    {
        ll nx = x + dx[k] ;
        ll ny = y + dy[k] ;
        if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny])
        {
            if(dfs(nx , ny , i + 1 , board , word))
            {
                vis[x][y] = 0 ;
                return true ;
            }
        }
    }
    vis[x][y] = 0 ;
    return false ;
}
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // step 5 : reset every global, LeetCode keeps them between test cases
        n = board.size() ;
        m = board[0].size() ;
        vis.assign(n , vector < ll > (m , 0)) ;
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll j = 0 ; j < m ; j++)
            {
                if(dfs(i , j , 0 , board , word))
                {
                    return true ;
                }
            }
        }
        return false ;
    }
};
