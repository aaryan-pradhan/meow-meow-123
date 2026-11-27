// orz
// 104. Maximum Depth of Binary Tree · LeetCode · Easy
//
// Question:
// given the root of a binary tree, return its maximum depth. the maximum depth
// is the number of nodes on the longest path from the root down to the farthest leaf.
// Example 1: root = [3,9,20,null,null,15,7] -> 3
// Example 2: root = [1,null,2]              -> 2
// Constraints: 0 <= number of nodes <= 10^4, -100 <= Node.val <= 100
//
// 1. Mathematical statement
//    rooted tree, depth(root) = 1, depth(child) = depth(parent) + 1.
//    return the max of depth(v) over all nodes v, and 0 for the empty tree.
//
// 2. Brute force
//    for every node, walk up to the root and count the nodes on the way.
//    O(n * h), a chain of 10^4 nodes gives about 5 * 10^7 steps.
//
// 3. What the brute force wastes
//    the walk up from a child repeats the whole walk up from its parent.
//
// 4. Key breaking point
//    depth(child) = depth(parent) + 1, so one dfs from the root that carries depth
//    as a parameter knows every depth on arrival. that is my dfs(node , par , depth).
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template). empty tree -> 0.
//    step 2 : dfs(node , par , depth) from the root with depth 1, every child gets depth + 1.
//    step 3 : ans = the max depth seen at any node.
//
// 6. Why it works
//    every node is reached exactly once and carries its true depth, so the max over
//    the dfs is the max depth. the deepest node is always a leaf, so this is the
//    longest root to leaf path.
//    time O(n), space O(n) for the ids, g and the recursion.
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
ll ans ;
void dfs(ll node , ll par , ll depth)
{
    // step 3 : this stores the deepest depth seen so far in ans
    ans = max(ans , depth) ;
    // step 2 : every child is one level deeper
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
    int maxDepth(TreeNode* root) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        if(rootid == 0)
        {
            return 0 ; // empty tree
        }
        buildg() ;
        // step 2 : the root has depth 1
        ans = 0 ;
        dfs(rootid , 0 , 1) ;
        // step 3
        return ans ;
    }
};
