/*
Ordered Checkpoints Shortest Path (source: pasted OA problem)

Problem Statement
You are given an undirected weighted graph containing N cities and M roads. Each road connects two
cities and has a positive travel time. You are also given a starting city S and an ordered sequence of K
special cities: A1, A2, ..., AK.
The special cities must be traversed in the given order. Once you have reached Ai, you are allowed to
proceed to Ai+1 (and you may move back toward the previously reached special city as needed). You
cannot skip an unreached special city. Ordinary cities and roads may be used freely while travelling
between consecutive special cities.
Your task is to determine the minimum total travel time required to start at S, visit A1, A2, ..., AK in
that order, and finish at AK. If the destination cannot be reached while respecting the required order,
output -1.

Important Interpretation
The phrase "ordered traversal" means that the required special cities are checkpoints. The traveller
must reach A1 before A2, A2 before A3, and so on. The shortest path used between two consecutive
checkpoints may contain any ordinary graph vertices.

Input Format
N M
U1 V1 T1
U2 V2 T2
...
UM VM TM
S K
A1 A2 ... AK
Each road (Ui, Vi) has travel time Ti and can be traversed in either direction.

Output Format
Print a single integer: the minimum total travel time required to start from S, visit all K special cities in
the specified order, and finish at AK. Print -1 if it is impossible.

Constraints
1 <= N <= 100,000
1 <= M <= 100,000
1 <= U, V <= N   (endpoints are valid city numbers)
1 <= T <= 10^9   (exponent garbled in source, assumed 10^9)
1 <= S <= N
1 <= K <= min(N - 1, 10)
1 <= Ai <= N
Roads are bidirectional

Sample Test Case 1
Input:
5 6
1 2 2
2 3 3
1 4 1
4 3 1
3 5 4
2 5 10
1 2
3 5
Output: 6
Explanation: Start at 1 and reach 3 using 1 -> 4 -> 3 with cost 2. Then travel 3 -> 5 with cost 4. Total = 2 + 4 = 6.

Sample Test Case 2
Input:
6 7
1 2 2
2 3 2
3 4 1
1 5 10
5 4 1
4 6 3
5 6 1
1 3
2 4 6
Output: 8
Explanation: 1 -> 2 costs 2, 2 -> 4 costs 3 via city 3, and 4 -> 6 costs 3. Therefore the answer is 2 + 3 + 3 = 8.

Sample Test Case 3
Input:
4 2
1 2 1
3 4 1
1 2
3 4
Output: -1
Explanation: The required first checkpoint, city 3, is unreachable from the start city 1.
*/

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
vector < vector < pll > > graph ; 
vector < ll > dist ;
vector < ll > vis ; 
void dij(ll s )
{
    dist[s] = 0 ;
    priority_queue < pll , vector < pll > , greater < pll > > pq ;
    pq.push({0, s}) ;
    while(!pq.empty())
    {
        pll u = pq.top() ;
        ll n = u.sc ;
        ll d = u.fr ;
        pq.pop() ;
        if(vis[n])
        {
            continue ; 
        }
        vis[n] = 1 ;
        for(auto& [w , ch] : graph[n])
        {
            if(dist[ch] > d + w)
            {
                dist[ch] = d + w ;
                pq.push({dist[ch], ch}) ;
            }
        }

    }
}
void solve()
{
    ll n , m ; 
    cin >> n >> m ;
    graph.assign(n + 1 , vector < pll > () ) ;
    dist.assign(n + 1 , INF) ;
    vis.assign(n + 1 , 0) ;
    for(ll i = 0 ; i < m ; i++)
    {
        ll u , v , t ;
        cin >> u >> v >> t ;
        graph[u].push_back({t, v}) ;
        graph[v].push_back({t, u}) ;
    }
    ll s , k ; 
    cin >> s >> k ;
    vector < ll > c(k) ;
    for(ll i = 0 ; i < k ; i++)
        cin >> c[i] ;
    ll ans = 0 ; 
    for(ll i = 0 ; i < k ; i++)
    {
        dij(s) ;
        if(dist[c[i]] == INF)
        {
            cout << -1 << endl ;
            return ;
        }
        s = c[i] ;
        ans += dist[s] ;
        dist.assign(n + 1 , INF) ;
        vis.assign(n + 1 , 0) ;
    }
    cout << ans << endl ;
    


}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
