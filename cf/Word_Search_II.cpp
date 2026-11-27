// orz
// 212. Word Search II · LeetCode · Hard
//
// Question:
// given an m x n board of characters and a list of strings words, return all words
// that are on the board. a word is on the board if it can be spelled by a path of
// sequentially adjacent cells (up, down, left, right), with no cell used twice in one word.
// the answer can be in any order.
// Example 1: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
//            words = ["oath","pea","eat","rain"] -> ["eat","oath"]
// Example 2: board = [["a","b"],["c","d"]], words = ["abcb"] -> []
// Constraints: 1 <= m, n <= 12, board[i][j] is a lowercase letter,
//              1 <= words.length <= 3 * 10^4, 1 <= words[i].length <= 10,
//              words[i] is lowercase letters, all words are unique.
//
// 1. Mathematical statement
//    a path is a sequence of distinct cells, each next to the one before.
//    return every word w in words such that some path spells w.
//
// 2. Brute force
//    run Word Search (79) for every word: start at every cell, dfs along the word.
//    3 * 10^4 words * 144 cells * up to 4 * 3^9 paths each. dead.
//
// 3. What the brute force wastes
//    "oath", "oat", "oak" walk the same board paths for their shared start "oa" again,
//    once per word. and a path whose letters start no word at all keeps being walked by every word.
//
// 4. Key breaking point
//    run ONE dfs over the board for all words together, and carry along the trie node of the
//    letters on the path so far (the trie of 208, node 0 = root). the trie answers two things at once:
//    "does some word still start like this path?" (the child exists, else stop) and
//    "is this path a whole word?" (endhere of the node).
//
// 5. Method
//    step 1 : build the trie of all words. nxt[node][c] = child by letter c (0 = no child),
//             endhere[node] = 1 + index of the word that ends at node (0 = no word ends here),
//             so the node tells me which word to report.
//    step 2 : dfs(x , y , node) : the path ends at cell (x , y), node = the trie node of its letters.
//             if endhere[node] != 0, the path spells a word: report it and set endhere[node] = 0,
//             so the same word is never reported twice.
//    step 3 : vis[x][y] = 1. for each of the 4 neighbours (nx , ny) inside the board and not visited,
//             with letter c : if nxt[node][c] != 0 go dfs(nx , ny , nxt[node][c]), else no word starts
//             like that, skip it. then vis[x][y] = 0, so other paths can use the cell.
//    step 4 : start a dfs from every cell whose letter is a child of the root.
//
// 6. Why it works
//    every path the dfs walks spells a prefix of some word (it stops as soon as the trie has no child),
//    and every path that spells a prefix of a word is walked (all neighbours are tried, vis keeps the
//    cells distinct). so every word on the board is reached at its trie node and reported, once.
//    time O(m * n * 4 * 3^(L - 1)) with L <= 10 in the worst case, usually far less because of the trie.
//    space O(26 * total letters) for the trie.
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
vector < vector < ll > > nxt ; // nxt[node][c] = child of node by letter c, 0 means no child
vector < ll > endhere ;        // endhere[node] = 1 + index of the word that ends at node, 0 means none
vector < vector < ll > > vis ;
vector < string > ans ;
ll dx[] = {0, 0, 1, -1};
ll dy[] = {1, -1, 0, 0};
ll newnode()
{
    // this makes an empty trie node and returns its id
    nxt.push_back(vector < ll > (26 , 0)) ;
    endhere.push_back(0) ;
    return (ll)nxt.size() - 1 ;
}
void insert(string& w , ll idx)
{
    // this puts word number idx into the trie
    ll node = 0 ;
    for(ll i = 0 ; i < (ll)w.size() ; i++)
    {
        ll c = w[i] - 'a' ;
        if(nxt[node][c] == 0)
        {
            // newnode() grows nxt, so make the node first and store its id after
            ll id = newnode() ;
            nxt[node][c] = id ;
        }
        node = nxt[node][c] ;
    }
    endhere[node] = idx + 1 ;
}
void dfs(ll x , ll y , ll node , vector < vector < char > >& board , vector < string >& words)
{
    // node = the trie node of the letters on the path, the path ends at (x , y)
    // step 2 : the path spells a whole word
    if(endhere[node] != 0)
    {
        ans.push_back(words[endhere[node] - 1]) ;
        endhere[node] = 0 ; // cross it out, report it only once
    }
    // step 3 : go on to the neighbours that keep the path a prefix of some word
    vis[x][y] = 1 ;
    for(ll k = 0 ; k < 4 ; k++)
    {
        ll nx = x + dx[k] ;
        ll ny = y + dy[k] ;
        if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny])
        {
            ll c = board[nx][ny] - 'a' ;
            if(nxt[node][c] != 0)
            {
                dfs(nx , ny , nxt[node][c] , board , words) ;
            }
            else
            {
                continue ;
            }
        }
    }
    vis[x][y] = 0 ;
}
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // reset every global, LeetCode keeps them between test cases
        n = board.size() ;
        m = board[0].size() ;
        nxt.clear() ;
        endhere.clear() ;
        vis.assign(n , vector < ll > (m , 0)) ;
        ans.clear() ;
        // step 1 : the trie of all words, root = 0
        newnode() ;
        for(ll i = 0 ; i < (ll)words.size() ; i++)
        {
            insert(words[i] , i) ;
        }
        // step 4 : a dfs from every cell that starts some word
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll j = 0 ; j < m ; j++)
            {
                ll c = board[i][j] - 'a' ;
                if(nxt[0][c] != 0)
                {
                    dfs(i , j , nxt[0][c] , board , words) ;
                }
            }
        }
        return ans ;
    }
};
