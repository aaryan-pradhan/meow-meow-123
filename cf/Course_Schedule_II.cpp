// orz
// 210. Course Schedule II · LeetCode · Medium
//
// Question:
// there are numCourses courses, labelled 0 .. numCourses - 1. prerequisites[i] = [a, b]
// means you must take course b before course a. return an order in which you can take
// all courses. any valid order is accepted. if it is impossible, return an empty array.
// Example 1: numCourses = 2, prerequisites = [[1,0]]                   -> [0,1]
// Example 2: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]] -> [0,1,2,3] (or [0,2,1,3])
// Example 3: numCourses = 1, prerequisites = []                        -> [0]
// Constraints: 1 <= numCourses <= 2000, 0 <= prerequisites.length <= numCourses * (numCourses - 1),
//              0 <= a , b < numCourses, a != b, all pairs are distinct.
//
// 1. Mathematical statement
//    directed graph: edge b -> a for every [a, b]. return a topological order
//    (every edge goes forward) of all nodes, or [] if the graph has a directed cycle.
//
// 2. Brute force
//    try every order of the n courses and check every edge. n! orders. dead.
//
// 3. What the brute force wastes
//    almost every order breaks an edge early, and it keeps building orders past that.
//    and after a course is taken, only its own out-edges change who is ready.
//
// 4. Key breaking point
//    this is my Course Schedule (CSES), word for word: Kahn's topo order.
//    indeg[node] = prerequisites not taken yet. take any course with indeg 0,
//    only its children lose 1. topo.size() != n means a cycle -> [].
//
// 5. Method
//    step 1 : g[b].push_back(a) and indeg[a]++ for every [a, b].
//    step 2 : push every course with indeg 0 into the queue.
//    step 3 : pop node, put it in topo, every child loses 1 indeg, push it when it hits 0.
//    step 4 : topo.size() != n -> return [], else return topo.
//
// 6. Why it works
//    a course enters topo only after all its prerequisites, so topo is a valid order.
//    if there is a cycle, no course on it can ever reach indeg 0 (each waits for the one
//    before it), so topo.size() < n. if there is no cycle, while some courses are left,
//    one of them has indeg 0 (else walking back along edges among them would close a cycle),
//    so Kahn takes everything. time O(n + m), space O(n + m).
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
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        ll n = numCourses ;
        // step 1 : edge b -> a, indeg[a] = prerequisites of a not taken yet
        vector < vector < ll > > g(n) ;
        vector < ll > indeg(n , 0) ;
        for(auto pr : prerequisites)
        {
            ll a = pr[0] ;
            ll b = pr[1] ;
            g[b].push_back(a) ;
            indeg[a]++ ;
        }
        // step 2 : courses with nothing to wait for
        queue < ll > q ;
        for(ll i = 0 ; i < n ; i++)
        {
            if(indeg[i] == 0)
            {
                q.push(i) ;
            }
        }
        // step 3 : kahn
        vector < int > topo ;
        while(!q.empty())
        {
            ll node = q.front() ;
            q.pop() ;
            topo.push_back(node) ;
            for(auto child : g[node])
            {
                indeg[child]-- ;
                if(indeg[child] == 0)
                {
                    q.push(child) ;
                }
            }
        }
        // step 4 : a cycle leaves some course out
        if((ll)topo.size() != n)
        {
            return vector < int > () ;
        }
        else
        {
            return topo ;
        }
    }
};
