// orz
// 112. Path Sum · LeetCode · Easy
//
// Question:
// given the root of a binary tree and an integer targetSum, return true if the tree
// has a root-to-leaf path whose values add up to targetSum. a leaf is a node with no children.
// Example 1: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22 -> true   (5 -> 4 -> 11 -> 2)
// Example 2: root = [1,2,3], targetSum = 5                                    -> false
// Example 3: root = [], targetSum = 0                                         -> false  (no path at all)
// Constraints: 0 <= number of nodes <= 5000, -1000 <= Node.val <= 1000, -1000 <= targetSum <= 1000
//
// 1. Mathematical statement
//    is there a leaf v with (sum of w(u) over u on the path root -> v) = targetSum ?
//
// 2. Brute force
//    for every leaf, walk up to the root adding the values. O(n * h).
//
// 3. What the brute force wastes
//    leaves under the same node add up the same top part of the path again.
//
// 4. Key breaking point
//    sum(root -> child) = sum(root -> node) + w(child). carry the sum down as a dfs
//    parameter, exactly like depth in my dfs(node , par , depth).
//    a leaf in g = a node whose only neighbour is par, so no child call happens.
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template). empty tree -> false.
//    step 2 : dfs(node , par , sum) with sum = sum above node. sum += w(node) is root .. node.
//    step 3 : count the children while going down. children == 0 means node is a leaf:
//             if sum == targetSum, found = true.
//    step 4 : return found.
//
// 6. Why it works
//    every root to leaf path is one branch of the dfs and arrives at its leaf with its
//    exact sum. |sum| <= 5000 * 1000, no overflow.
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
ll target ;
bool found ;
void dfs(ll node , ll par , ll sum)
{
    // step 2 : now sum = sum of the values from the root down to node
    sum += ptr[node]->val ;
    ll children = 0 ;
    for(auto child : g[node])
    {
        if(child != par)
        {
            children++ ;
            dfs(child , node , sum) ;
        }
    }
    // step 3 : no children means node is a leaf, the path root -> node is complete
    if(children == 0 && sum == target)
    {
        found = true ;
    }
}
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        if(rootid == 0)
        {
            return false ; // empty tree has no root-to-leaf path
        }
        buildg() ;
        // step 2 : nothing above the root, sum starts at 0
        target = targetSum ;
        found = false ;
        dfs(rootid , 0 , 0) ;
        // step 4
        return found ;
    }
};
