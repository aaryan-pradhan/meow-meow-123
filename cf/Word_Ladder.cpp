// orz
// 127. Word Ladder · LeetCode · Hard
//
// Question:
// a transformation sequence from beginWord to endWord is beginWord -> s1 -> s2 -> .. -> sk
// where every two neighbours differ in exactly one letter, every si is in wordList
// (beginWord does not need to be), and sk == endWord. return the number of words in the
// shortest such sequence (beginWord included), or 0 if there is none.
// Example 1: beginWord = "hit", endWord = "cog",
//            wordList = ["hot","dot","dog","lot","log","cog"] -> 5  (hit -> hot -> dot -> dog -> cog)
// Example 2: beginWord = "hit", endWord = "cog",
//            wordList = ["hot","dot","dog","lot","log"]       -> 0  (cog is not in wordList)
// Constraints: 1 <= beginWord.length <= 10, endWord.length == beginWord.length,
//              1 <= wordList.length <= 5000, wordList[i].length == beginWord.length,
//              all lowercase letters, beginWord != endWord, the words in wordList are distinct.
//
// 1. Mathematical statement
//    graph: nodes = beginWord and the words of wordList, an edge between two words that
//    differ in exactly one position. d = fewest edges from beginWord to endWord.
//    return d + 1 (words, not edges), or 0 if endWord is not a node or not reachable.
//
// 2. Brute force
//    try every sequence of words (dfs over all paths). exponential, dead at 5000 words.
//    even building the graph by comparing every pair of words is
//    n^2 * L = 5000^2 * 10 = 2.5 * 10^8. too slow.
//
// 3. What the brute force wastes
//    many sequences reach the same word after the same number of steps, and from there
//    they all continue the same way. and the pair compare checks millions of pairs
//    that differ in many letters.
//
// 4. Key breaking point
//    every step costs 1, so "shortest" is my unweighted BFS on g.
//    and the neighbours of a word can be generated, not searched: change one position
//    to one of the 25 other letters, and look the result up in a map of the words.
//    that is L * 25 = 250 lookups per word instead of n compares.
//
// 5. Method
//    step 1 : ids: beginWord gets id 0, every new word of wordList gets the next id. w[id] = the word.
//    step 2 : for every word, every position, every other letter 'a' .. 'z': if the changed
//             string has an id, g[word].push_back(that id).
//    step 3 : bfs from 0, dist = -1 means not visited.
//    step 4 : endWord has no id, or dist = -1 -> 0. else return dist + 1.
//
// 6. Why it works
//    step 2 makes exactly the edges "differ in one position" between allowed words,
//    so a transformation sequence is a path in g and BFS gives the fewest edges.
//    the sequence has one more word than edges, so + 1. endWord != beginWord, so
//    endWord gets an id only from wordList, which is exactly the rule.
//    time O(n * L * 25 * L log n) to build, O(n + edges) for bfs. space O(n * L) plus the edges.
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
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // step 1 : word -> id. beginWord is 0
        map < string , ll > id ;
        vector < string > w ; // w[id] = the word with this id
        id[beginWord] = 0 ;
        w.push_back(beginWord) ;
        for(auto s : wordList)
        {
            if(id.find(s) == id.end())
            {
                id[s] = w.size() ;
                w.push_back(s) ;
            }
        }
        ll n = w.size() ;
        // step 2 : edges = one letter changed, and the result is an allowed word
        vector < vector < ll > > g(n) ;
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll pos = 0 ; pos < (ll)w[i].size() ; pos++)
            {
                for(char ch = 'a' ; ch <= 'z' ; ch++)
                {
                    if(ch == w[i][pos])
                    {
                        continue ;
                    }
                    string t = w[i] ;
                    t[pos] = ch ;
                    if(id.find(t) != id.end())
                    {
                        g[i].push_back(id[t]) ;
                    }
                }
            }
        }
        // step 3 : bfs from beginWord
        vector < ll > dist(n , -1) ;
        queue < ll > q ;
        q.push(0) ;
        dist[0] = 0 ;
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
        // step 4 : count words, not edges
        if(id.find(endWord) == id.end() || dist[id[endWord]] == -1)
        {
            return 0 ;
        }
        else
        {
            return dist[id[endWord]] + 1 ;
        }
    }
};
