// orz
// 399. Evaluate Division · LeetCode · Medium
//
// Question:
// equations[i] = [Ai, Bi] and values[i] mean Ai / Bi = values[i], where every Ai, Bi
// is a variable name. queries[j] = [Cj, Dj] asks for Cj / Dj. answer every query;
// when the answer can't be determined (for example a variable never seen), answer -1.0.
// the input is valid: no division by zero and no contradiction.
// Example 1: equations = [["a","b"],["b","c"]], values = [2.0,3.0],
//            queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
//            -> [6.00000,0.50000,-1.00000,1.00000,-1.00000]
// Example 2: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
//            queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
//            -> [3.75000,0.40000,5.00000,0.20000]
// Example 3: equations = [["a","b"]], values = [0.5],
//            queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
//            -> [0.50000,2.00000,-1.00000,-1.00000]
// Constraints: 1 <= equations.length <= 20, 1 <= Ai.length , Bi.length <= 5,
//              0.0 < values[i] <= 20.0, 1 <= queries.length <= 20,
//              1 <= Cj.length , Dj.length <= 5, names are lowercase letters and digits.
//
// 1. Mathematical statement
//    unknown positive reals x(v), one per variable. given x(Ai) / x(Bi) = values[i].
//    for each query, return x(C) / x(D) if every solution of the equations gives the
//    same value, else -1.
//
// 2. Brute force
//    graph: variables are nodes, equation a / b = v is an edge a -> b with weight v and
//    b -> a with weight 1 / v. try every simple path from C to D and multiply the weights.
//    exponential in the number of variables.
//
// 3. What the brute force wastes
//    there is no contradiction, so every path from C to D gives the SAME product.
//    after the first path, every other path is wasted.
//
// 4. Key breaking point
//    along a path C = u0 , u1 , .. , uk = D:
//    x(C) / x(D) = (x(u0) / x(u1)) * (x(u1) / x(u2)) * .. * (x(u(k-1)) / x(uk)),
//    a product of edge weights. so one bfs from C that carries r[node] = x(C) / x(node)
//    answers the query: r[child] = r[node] * w. my weighted g, weight first then node.
//    and if D is not reachable from C, the answer is not determined: multiply every
//    x in D's component by 2, all equations still hold, but x(C) / x(D) changes. -> -1.
//
// 5. Method
//    step 1 : give every variable an id 1 .. n with a map (in order of first appearance).
//    step 2 : g[a].push_back({v , b}) and g[b].push_back({1 / v , a}) for every equation.
//    step 3 : for every query (C , D): if C or D has no id -> -1.
//    step 4 : bfs from C with r[C] = 1. when node is popped, every unvisited child gets
//             r[child] = r[node] * w and is marked when pushed.
//    step 5 : D visited -> r[D], else -1.
//
// 6. Why it works
//    by induction along the bfs tree, r[node] = x(C) / x(node) for every visited node,
//    because each edge weight w on node -> child is x(node) / x(child).
//    no contradiction means any path gives the same value, so the bfs path is fine.
//    unreachable D is not determined (see the key point), so -1 is right.
//    C = D known gives r = 1. time O(q * (n + e)) plus map lookups, tiny here.
//    space O(n + e).
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
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // step 1 : variable name -> id 1 .. n
        map < string , ll > id ;
        ll n = 0 ;
        for(auto e : equations)
        {
            for(auto s : e)
            {
                if(id.find(s) == id.end())
                {
                    n++ ;
                    id[s] = n ;
                }
            }
        }
        // step 2 : weighted g, weight first then node. a / b = v
        vector < vector < pair < double , ll > > > g(n + 1) ;
        for(ll i = 0 ; i < (ll)equations.size() ; i++)
        {
            ll a = id[equations[i][0]] ;
            ll b = id[equations[i][1]] ;
            double v = values[i] ;
            g[a].push_back({v , b}) ;
            g[b].push_back({1.0 / v , a}) ;
        }
        vector < double > ans ;
        for(auto qr : queries)
        {
            // step 3 : a variable never seen
            if(id.find(qr[0]) == id.end() || id.find(qr[1]) == id.end())
            {
                ans.push_back(-1.0) ;
                continue ;
            }
            ll src = id[qr[0]] ;
            ll dst = id[qr[1]] ;
            // step 4 : bfs from src, r[node] = x(src) / x(node)
            vector < ll > vis(n + 1 , 0) ;
            vector < double > r(n + 1 , 0) ;
            queue < ll > q ;
            q.push(src) ;
            vis[src] = 1 ;
            r[src] = 1.0 ;
            while(!q.empty())
            {
                ll node = q.front() ;
                q.pop() ;
                for(auto y : g[node])
                {
                    double w = y.fr ;
                    ll child = y.sc ;
                    if(!vis[child])
                    {
                        vis[child] = 1 ;
                        r[child] = r[node] * w ;
                        q.push(child) ;
                    }
                }
            }
            // step 5 : not reachable means not determined
            if(vis[dst])
            {
                ans.push_back(r[dst]) ;
            }
            else
            {
                ans.push_back(-1.0) ;
            }
        }
        return ans ;
    }
};
