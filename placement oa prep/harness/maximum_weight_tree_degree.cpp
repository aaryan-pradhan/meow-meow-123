/*
Maximum Weight Tree After Degree Constraints
Difficulty: Hard

You are given an undirected weighted tree consisting of n servers numbered from 0 to n - 1.
The tree is represented using three integer arrays:
g_from[i] and g_to[i] represent an undirected edge between two servers.
g_weight[i] represents the weight of that edge.
You are also given an integer k.

You may remove any number of edges from the tree. After removing the edges,
every server must have at most k incident edges.
Return the maximum possible sum of the weights of the remaining edges.

Example 1:
Input:
n = 5
g_from = [0, 0, 0, 2]
g_to = [1, 2, 3, 4]
g_weight = [10, 20, 5, 15]
k = 2
Output: 45

Example 2:
Input:
n = 4
g_from = [0, 1, 2]
g_to = [1, 2, 3]
g_weight = [4, 7, 5]
k = 2
Output: 16

Example 3:
Input:
n = 6
g_from = [0, 0, 0, 1, 2]
g_to = [1, 2, 3, 4, 5]
g_weight = [8, 6, 10, 5, 9]
k = 1
Output: 19

Constraints:
2 <= n <= 2 * 10^5
g_from.length == g_to.length == g_weight.length == n - 1
0 <= g_from[i], g_to[i] < n
1 <= g_weight[i] <= 10^9
1 <= k <= n - 1
The given edges form a valid tree.
*/

#include <bits/stdc++.h>
using namespace std;
#define ll int
vector < vector < pair < ll , ll > > > graph ;
vector < array < ll , 2 > > dp ;
ll k ; 
void dfs(ll n , ll p )
{
    dp[n][0] = 0 ;
    dp[n][1] = 0 ;
    ll cnt = 0 ; 
    for(auto [w,ch] : graph[n])
    {
        if(ch == p) continue ;
        dfs(ch, n) ;
        if(cnt <= k)
        {
            dp[n][0] += max(dp[ch][0] + w , dp[ch][1]) ;
        }
        cnt++ ; 
    }
    cnt = 0 ; 
    for(auto [w,ch] : graph[n])
    {
        if(ch == p) continue ;
        if(cnt < k)
        {
            dp[n][1] += max(dp[ch][0] + w , dp[ch][1]) ;
        }
        cnt++ ; 
    }



}
class Solution {
public:
    long long maximumWeight(
        int n,
        vector<int>& g_from,
        vector<int>& g_to,
        vector<int>& g_weight,
        int ki
    ) {
        graph.assign(n+1, vector < pair < ll , ll > > () ) ;
        dp.assign(n+1, {0, 0}) ;
        for(ll i = 0 ; i < n - 1 ; i++)
        {
            graph[g_from[i]+1].push_back({g_weight[i], g_to[i]+1}) ;
            graph[g_to[i]+1].push_back({g_weight[i], g_from[i]+1}) ;
        }
        for(ll i = 1 ; i <= n ; i++)
        {
            sort(graph[i].begin(), graph[i].end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
                return b.first < a.first; 
            });
        }

        k = ki 
        dfs(1, 0) ;
        return max(dp[1][0], dp[1][1]) ;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Testing logic here

    return 0;
}

