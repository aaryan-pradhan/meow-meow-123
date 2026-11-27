// orz
// 207. Course Schedule · LeetCode · Medium
//
// Question:
// there are numCourses courses, labelled 0 .. numCourses - 1. prerequisites[i] = [a, b]
// means you must take course b before course a. return true if you can finish
// all courses, else false.
// Example 1: numCourses = 2, prerequisites = [[1,0]]       -> true
// Example 2: numCourses = 2, prerequisites = [[1,0],[0,1]] -> false  (0 needs 1, 1 needs 0)
// Constraints: 1 <= numCourses <= 2000, 0 <= prerequisites.length <= 5000,
//              0 <= a , b < numCourses, all pairs are distinct.
//
// 1. Mathematical statement
//    directed graph: edge b -> a for every [a, b]. return true iff there is an order of
//    all nodes where every edge goes forward, i.e. iff the graph has no directed cycle.
//
// 2. Brute force
//    try every order of the n courses and check every edge. n! orders. dead.
//    (or: rescan all courses again and again for one whose prerequisites are done:
//    O(n * (n + m)) = 2000 * 7000, slow and silly.)
//
// 3. What the brute force wastes
//    after a course is taken, only its own out-edges change who is ready.
//    rescanning everything finds the same not-ready courses again.
//
// 4. Key breaking point
//    this is my Course Schedule (CSES): Kahn. keep indeg[node] = prerequisites not taken yet.
//    take any course with indeg 0, then only its children lose 1. all taken <=> no cycle.
//
// 5. Method
//    step 1 : g[b].push_back(a) and indeg[a]++ for every [a, b].
//    step 2 : push every course with indeg 0 into the queue.
//    step 3 : pop node, put it in topo, every child loses 1 indeg, push it when it hits 0.
//    step 4 : return topo.size() == n.
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
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
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
        vector < ll > topo ;
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
        // step 4 : every course taken <=> no cycle
        if((ll)topo.size() != n)
        {
            return false ;
        }
        else
        {
            return true ;
        }
    }
};
