// orz
// 124. Binary Tree Maximum Path Sum · LeetCode · Hard
//
// Question:
// a path in a binary tree is a sequence of nodes where each pair of adjacent
// nodes has an edge between them, and a node appears at most once. the path
// does not need to pass through the root. the path sum is the sum of the node
// values on the path. given the root, return the maximum path sum of any
// non-empty path.
// Example 1: root = [1,2,3]                  -> 6   (2 -> 1 -> 3)
// Example 2: root = [-10,9,20,null,null,15,7] -> 42  (15 -> 20 -> 7)
// Constraints: 1 <= number of nodes <= 3 * 10^4, -1000 <= Node.val <= 1000
//
// 1. Mathematical statement
//    tree with values w(v). maximise the sum of w(v) over v on P,
//    over every simple path P with at least one node.
//
// 2. Brute force
//    run a dfs from every node u, and every node v it reaches closes a path u -> v.
//    n dfs runs of O(n) each = O(n^2) = 9 * 10^8. too slow.
//
// 3. What the brute force wastes
//    paths with different ends share the same downward pieces, and every dfs
//    sums those pieces again.
//
// 4. Key breaking point
//    root the tree. every path has exactly one highest node top (the one closest to the root).
//    from top, the path goes down into at most two different children, and each side
//    is a downward path (an "arm"). so
//    best path with highest node top = w(top) + max(0 , best left arm) + max(0 , best right arm),
//    because a negative arm is just dropped.
//    now I only need indp[v] = best downward path starting at v, for every v:
//    the same in-dp as Maximum White Subtree (max(0LL , indp[child])).
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template), so my dfs(node , par) works.
//    step 2 : indp[node] = w(node) + max(0 , best indp[child]).
//             best downward path that starts at node: node alone, or node plus its best arm.
//    step 3 : at the same node, the best path whose highest node is node =
//             w(node) + sum over children of max(0 , indp[child]). (at most 2 children)
//    step 4 : ans = max of step 3 over all nodes. ans starts at -INF, because all values can be negative.
//
// 6. Why it works
//    every path has exactly one highest node, so it is counted at that node in step 3.
//    the two arms lie in different subtrees, so they can't share a node, and each can be
//    chosen on its own. a negative arm can be dropped because the path may be the node alone.
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
vector < ll > indp ;
ll ans ;
void dfsin(ll node , ll par)
{
    // indp[node] = best sum of a downward path that starts at node
    ll w = ptr[node]->val ;
    ll bestarm = 0 ;  // best child arm, 0 means take no arm
    ll botharms = 0 ; // sum of every child arm that helps
    for(auto child : g[node])
    {
        if(child != par)
        {
            dfsin(child , node) ;
            bestarm = max(bestarm , indp[child]) ;
            botharms += max(0LL , indp[child]) ;
        }
    }
    // step 2 : node plus its best arm
    indp[node] = w + bestarm ;
    // step 3 : best path whose highest node is node
    ans = max(ans , w + botharms) ;
}
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        buildg() ;
        // step 4 : all values can be negative, so start at -INF
        ans = -INF ;
        indp.assign(n + 1 , 0) ;
        dfsin(rootid , 0) ;
        return ans ;
    }
};
