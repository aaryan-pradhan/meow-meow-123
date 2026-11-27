// orz
// 45. Jump Game II · LeetCode · Medium
//
// Question:
// you start at index 0 of an integer array nums. nums[i] is the maximum jump length
// from index i: from i you can jump to any of i + 1 .. i + nums[i] (staying inside the array).
// return the minimum number of jumps to reach index n - 1. it is always reachable.
// Example 1: nums = [2,3,1,1,4]   -> 2   (0 -> 1 -> 4)
// Example 2: nums = [2,3,0,1,4]   -> 2
// Constraints: 1 <= n <= 10^4, 0 <= nums[i] <= 1000, n - 1 is reachable from 0
//
// 1. Mathematical statement
//    graph on 0 .. n - 1 with an edge i -> j of cost 1 for every i < j <= i + nums[i].
//    find the shortest distance from 0 to n - 1.
//
// 2. Brute force
//    plain bfs on that graph. node i has nums[i] edges, so O(sum of nums[i]) = 10^4 * 1000 = 10^7 edges,
//    built and stored. (trying every jump sequence by recursion is exponential.)
//
// 3. What the brute force wastes
//    the nums[i] edges out of i all cost 1 and land on a whole block i + 1 .. i + nums[i].
//    landing short of the far end is the same as landing on the far end and walking back.
//
// 4. Key breaking point
//    replace the nums[i] edges of i with just two:
//      i -> min(n - 1 , i + nums[i])   cost 1   (the longest jump)
//      i -> i - 1                      cost 0   (walk back for free)
//    "jump to i + d" = "jump to the far end, then d' free steps back", so every old path
//    still exists with the same cost. and the free steps never make anything cheaper:
//    the set reached with <= c jumps is always a prefix 0 .. R (Jump Game), so walking back
//    only visits indices that already cost <= c.
//    now it is a shortest path with weights 0 and 1: 0-1 bfs with a deque.
//
// 5. Method
//    step 1 : build g with 2 edges per node, {weight , node} (daam phir naam).
//    step 2 : dist[i] = INF for every i, dist[0] = 0, deque dq = { 0 }.
//    step 3 : pop node from the front. for every edge {w , child}:
//             if dist[node] + w < dist[child], set dist[child] = dist[node] + w and
//             push child to the FRONT if w = 0, to the BACK if w = 1.
//    step 4 : return dist[n - 1].
//
// 6. Why it works
//    0-1 bfs = dijkstra where the deque is the priority queue: a 0 edge keeps the same
//    distance (front), a 1 edge is one more (back), so the deque always holds at most two
//    distances d and d + 1 in sorted order, and nodes leave it in order of distance.
//    by 4 the new graph has the same distance to n - 1 as the old one.
//    time O(n): 0-1 bfs is O(nodes + edges) like bfs, and there are only 2n edges. space O(n).
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
    int jump(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1 : two edges per node, weight first, node second
        vector < vector < pll > > g(n) ;
        for(ll node = 0 ; node < n ; node++)
        {
            g[node].push_back({1 , min(n - 1 , node + nums[node])}) ; // the longest jump
            if(node > 0)
            {
                g[node].push_back({0 , node - 1}) ; // walk back for free
            }
        }
        // step 2
        vector < ll > dist(n , INF) ;
        deque < ll > dq ;
        dist[0] = 0 ;
        dq.push_back(0) ;
        // step 3 : 0-1 bfs
        while(!dq.empty())
        {
            ll node = dq.front() ;
            dq.pop_front() ;
            for(auto [w , child] : g[node])
            {
                if(dist[node] + w < dist[child])
                {
                    dist[child] = dist[node] + w ;
                    if(w == 0)
                    {
                        dq.push_front(child) ;
                    }
                    else
                    {
                        dq.push_back(child) ;
                    }
                }
                else
                {
                    continue ;
                }
            }
        }
        // step 4
        return dist[n - 1] ;
    }
};
