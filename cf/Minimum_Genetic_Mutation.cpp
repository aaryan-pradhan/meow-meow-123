// orz
// 433. Minimum Genetic Mutation · LeetCode · Medium
//
// Question:
// a gene string has 8 characters, each one of 'A', 'C', 'G', 'T'. one mutation
// changes exactly one character. a gene is valid only if it is in the bank
// (startGene is valid and may be missing from the bank). return the fewest mutations
// to turn startGene into endGene through valid genes, or -1 if it can't be done.
// Example 1: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]   -> 1
// Example 2: startGene = "AACCGGTT", endGene = "AAACGGTA",
//            bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]                          -> 2
// Example 3: startGene = "AAAAACCC", endGene = "AACCCCCC",
//            bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]                          -> 3
// Constraints: 0 <= bank.length <= 10, startGene.length == endGene.length == bank[i].length == 8,
//              all characters are in "ACGT".
//
// 1. Mathematical statement
//    graph: nodes = startGene and the bank genes, an edge between two genes that differ
//    in exactly one position. return the length of the shortest path startGene -> endGene,
//    or -1 if endGene is not a node or is not reachable.
//
// 2. Brute force
//    try every sequence of mutations through the bank (dfs over all paths).
//    up to 10! orders of the bank genes. it works for 10 genes, but it is exponential.
//
// 3. What the brute force wastes
//    many sequences arrive at the same gene after the same number of mutations,
//    and from there they all continue the same way.
//
// 4. Key breaking point
//    every mutation costs 1, so "fewest mutations" is my unweighted BFS on g.
//    to build g, for each gene try all 8 * 3 one-letter changes and look each one up in
//    a map of the genes (the same build as Word Ladder).
//
// 5. Method
//    step 1 : ids: startGene gets id 0, every new bank gene gets the next id. w[id] = the gene.
//    step 2 : for every gene, every position, every other letter of "ACGT": if the changed
//             string has an id, g[gene].push_back(that id).
//    step 3 : bfs from 0, dist = -1 means not visited.
//    step 4 : endGene has no id -> -1. else return dist[id of endGene] (-1 if never reached).
//
// 6. Why it works
//    step 2 makes exactly the edges "differ in one position" between valid genes,
//    so a mutation sequence is a path in g and BFS gives the fewest edges.
//    endGene == startGene gets id 0, dist 0. endGene not in the bank (and not the start)
//    is not valid, so -1. time O(b * 8 * 3 * log b) to build, O(b + edges) for bfs,
//    tiny. space O(b * 8) plus the edges.
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
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        // step 1 : gene -> id. start is 0
        map < string , ll > id ;
        vector < string > w ; // w[id] = the gene with this id
        id[startGene] = 0 ;
        w.push_back(startGene) ;
        for(auto s : bank)
        {
            if(id.find(s) == id.end())
            {
                id[s] = w.size() ;
                w.push_back(s) ;
            }
        }
        ll n = w.size() ;
        // step 2 : edges = one letter changed, and the result is a valid gene
        string letters = "ACGT" ;
        vector < vector < ll > > g(n) ;
        for(ll i = 0 ; i < n ; i++)
        {
            for(ll pos = 0 ; pos < (ll)w[i].size() ; pos++)
            {
                for(auto ch : letters)
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
        // step 3 : bfs from the start gene
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
        // step 4 : end gene not valid, or not reached
        if(id.find(endGene) == id.end())
        {
            return -1 ;
        }
        else
        {
            return dist[id[endGene]] ;
        }
    }
};
