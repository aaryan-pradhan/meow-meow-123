// orz
// 236. Lowest Common Ancestor of a Binary Tree · LeetCode · Medium
//
// Question:
// given a binary tree and two of its nodes p and q, return their lowest common ancestor:
// the lowest node that has both p and q as descendants (a node is a descendant of itself).
// Example 1: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1 -> 3
// Example 2: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4 -> 5   (5 is its own descendant)
// Example 3: root = [1,2], p = 1, q = 2                         -> 1
// Constraints: 2 <= number of nodes <= 10^5, -10^9 <= Node.val <= 10^9, all values distinct,
//              p != q, p and q are both in the tree.
//
// 1. Mathematical statement
//    anc(v) = { v, parent(v), parent(parent(v)), .. , root }.
//    lca(a , b) = the deepest node in anc(a) and anc(b).
//
// 2. Brute force
//    for every node v, run a dfs over its subtree and check whether both p and q are in it.
//    keep the deepest such v. O(n^2) = 10^10. dead.
//
// 3. What the brute force wastes
//    the common ancestors of p and q are only the nodes on the two paths p -> root and
//    q -> root, and the brute force searches whole subtrees to find them.
//
// 4. Key breaking point
//    the two paths a -> root and b -> root join at the lca and stay joined up to the root.
//    lift the deeper one to the same depth first. then both are on the same level, and
//    moving both up one step at a time, they meet for the first time exactly at the lca.
//    this is my binary lifting LCA (Company Queries II) with jumps of 1 : one query only,
//    so no up[][] table is needed, the parent array is enough.
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template).
//             node_a = id of p, node_b = id of q (scan ptr).
//    step 2 : dfs(node , par , depth) stores d[node] and parent[node]. root : depth 0, parent 0.
//    step 3 : if d[node_a] < d[node_b], swap them, so node_a is the deeper one.
//             lift node_a to parent[node_a] until d[node_a] == d[node_b].
//    step 4 : while node_a != node_b : node_a = parent[node_a], node_b = parent[node_b].
//    step 5 : return ptr[node_a].
//
// 6. Why it works
//    every common ancestor is an ancestor of b, so its depth is <= d[b] = k. after step 3 node_a is
//    the ancestor of a at depth k, so anc(node_a) still holds every common ancestor.
//    two nodes at the same depth have the same ancestor at depth j exactly when j <= depth(lca),
//    so step 4 stops exactly at the lca.
//    if b is an ancestor of a, step 3 already lands on b and step 4 does nothing.
//    time O(n), space O(n) for the ids, g, d, parent and the recursion.
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
vector < ll > d ;       // d[id] = depth of node id, the root has depth 0
vector < ll > parent ;  // parent[id] = id of the parent of id, 0 above the root
void dfs(ll node , ll par , ll depth)
{
    // step 2 : this stores depth and parent of node and of everything below it
    d[node] = depth ;
    parent[node] = par ;
    for(auto child : g[node])
    {
        if(child != par)
        {
            dfs(child , node , depth + 1) ;
        }
    }
}
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        buildg() ;
        ll node_a = 0 ;
        ll node_b = 0 ;
        for(ll id = 1 ; id <= n ; id++)
        {
            if(ptr[id] == p)
            {
                node_a = id ;
            }
            else if(ptr[id] == q)
            {
                node_b = id ;
            }
        }
        // step 2 : depth and parent of every node
        d.assign(n + 1 , 0) ;
        parent.assign(n + 1 , 0) ;
        dfs(rootid , 0 , 0) ;
        // step 3 : node_a is the deeper one, lift it to the depth of node_b
        if(d[node_a] < d[node_b])
        {
            swap(node_a , node_b) ;
        }
        while(d[node_a] > d[node_b])
        {
            node_a = parent[node_a] ;
        }
        // step 4 : same depth now, climb together until they meet
        while(node_a != node_b)
        {
            node_a = parent[node_a] ;
            node_b = parent[node_b] ;
        }
        // step 5
        return ptr[node_a] ;
    }
};
