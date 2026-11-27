// orz
// 637. Average of Levels in Binary Tree · LeetCode · Easy
//
// Question:
// given the root of a binary tree, return the average value of the nodes on
// each level, as an array, from the top level down. answers within 10^-5 of
// the actual answer are accepted.
// Example 1: root = [3,9,20,null,null,15,7] -> [3.00000,14.50000,11.00000]
// Example 2: root = [3,9,20,15,7]           -> [3.00000,14.50000,11.00000]
// Constraints: 1 <= number of nodes <= 10^4, -2^31 <= Node.val <= 2^31 - 1
//
// 1. Mathematical statement
//    depth(v) = number of edges from the root to v.
//    for every depth d = 0, 1, .. that has a node:
//    ans[d] = (sum of val(v) over v with depth d) / (number of v with depth d).
//
// 2. Brute force
//    for every depth d, walk the whole tree and add up the nodes of depth d.
//    up to n depths, O(n) per walk = O(n^2) = 10^8 for a chain. slow, and silly.
//
// 3. What the brute force wastes
//    every walk visits every node and then throws away all the nodes that are
//    not at its one depth.
//
// 4. Key breaking point
//    one BFS from the root gives every node its level lvl[node]. then a level is
//    just a bucket: sum[lvl] += val, cnt[lvl] += 1, and the average is sum / cnt.
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template).
//    step 2 : bfs from the root with my queue. lvl[child] = lvl[node] + 1,
//             lvl = -1 means not visited yet (marked when pushed).
//    step 3 : when node is popped, add its value to sum[lvl[node]] and 1 to cnt[lvl[node]].
//             sum is ll: up to 10^4 values of size 2^31 is about 2 * 10^13, too big for int.
//    step 4 : ans[d] = sum[d] / cnt[d] as a double, for every level d.
//
// 6. Why it works
//    BFS reaches every node exactly once, and the tree path is the only path, so
//    lvl[node] is exactly its depth. so bucket d holds exactly the nodes of depth d.
//    BFS pops level d before level d + 1, so the buckets are opened in top-down order.
//    time O(n), space O(n) for the ids, g, lvl and the queue.
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// ---- tree template (TEMPLATES.md) ----
ll n ;
vector < TreeNode* > ptr ;  // ptr[id] = the tree node with this id
vector < ll > lc , rc ;     // lc[id] / rc[id] = id of the left / right child, 0 means no child
vector < vector < ll > > g ;
ll encode(TreeNode* cur)
{
    // this gives cur and everything below it an id, and returns the id of cur (0 if cur is NULL)
    if(cur == NULL)
    {
        return 0 ;
    }
    n++ ;
    ll id = n ;
    ptr.push_back(cur) ;
    lc.push_back(0) ;
    rc.push_back(0) ;
    ll l = encode(cur->left) ;
    ll r = encode(cur->right) ;
    lc[id] = l ;
    rc[id] = r ;
    return id ;
}
void buildg()
{
    // this turns lc / rc into my adjacency list g
    g.assign(n + 1 , vector < ll > ()) ;
    for(ll id = 1 ; id <= n ; id++)
    {
        if(lc[id] != 0)
        {
            g[id].push_back(lc[id]) ;
            g[lc[id]].push_back(id) ;
        }
        if(rc[id] != 0)
        {
            g[id].push_back(rc[id]) ;
            g[rc[id]].push_back(id) ;
        }
    }
}
// ---- end of tree template ----
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        buildg() ;
        // step 2 : bfs from the root, lvl = -1 means not visited
        vector < ll > lvl(n + 1 , -1) ;
        vector < ll > sum ; // sum[d] = sum of the values on level d
        vector < ll > cnt ; // cnt[d] = number of nodes on level d
        queue < ll > q ;
        q.push(rootid) ;
        lvl[rootid] = 0 ;
        while(!q.empty())
        {
            ll node = q.front() ;
            q.pop() ;
            // step 3 : drop node into the bucket of its level
            if(lvl[node] == (ll)sum.size())
            {
                sum.push_back(0) ;
                cnt.push_back(0) ;
            }
            sum[lvl[node]] += ptr[node]->val ;
            cnt[lvl[node]]++ ;
            for(auto child : g[node])
            {
                if(lvl[child] == -1)
                {
                    lvl[child] = lvl[node] + 1 ;
                    q.push(child) ;
                }
            }
        }
        // step 4 : average of every level
        vector < double > ans ;
        for(ll d = 0 ; d < (ll)sum.size() ; d++)
        {
            ans.push_back((double)sum[d] / cnt[d]) ;
        }
        return ans ;
    }
};
