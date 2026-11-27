// orz
// 226. Invert Binary Tree · LeetCode · Easy
//
// Question:
// given the root of a binary tree, invert it (mirror it left to right), and return its root.
// Example 1: root = [4,2,7,1,3,6,9] -> [4,7,2,9,6,3,1]
// Example 2: root = [2,1,3]         -> [2,3,1]
// Example 3: root = []              -> []
// Constraints: 0 <= number of nodes <= 100, -100 <= Node.val <= 100
//
// 1. Mathematical statement
//    for every node v : new left(v) = old right(v), new right(v) = old left(v).
//    same nodes, only the child pointers change.
//
// 2. Brute force
//    for every node, find it again by walking its L / R path from the root
//    (paths written down before anything changes), and swap its two children there.
//    O(n * h).
//
// 3. What the brute force wastes
//    the swap at a node needs nothing but the node and its two old children,
//    so every walk from the root is wasted.
//
// 4. Key breaking point
//    the mirror is a local rule: every node swaps its own two children, and no node
//    cares what the others do. so I only need the list of all nodes with their OLD
//    children, and that is exactly ptr / lc / rc from the ids. lc / rc are read before
//    any pointer changes, so the order of the rewiring does not matter.
//
// 5. Method
//    step 1 : give every node an id (tree template, no g here). lc / rc keep the OLD children.
//    step 2 : for every id : ptr[id]->left = ptr[rc[id]], ptr[id]->right = ptr[lc[id]].
//             ptr[0] = NULL, so a missing child stays missing.
//    step 3 : return root, the root node itself does not move. (empty tree: n = 0,
//             step 2 does nothing, NULL comes back)
//
// 6. Why it works
//    mirror(v) = v with mirror(old right) on the left and mirror(old left) on the right.
//    from the leaves up, swapping at every node builds exactly that. lc / rc were saved
//    before the first change, so every swap uses the true old children.
//    time O(n), space O(n) for the ids.
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
    TreeNode* invertTree(TreeNode* root) {
        // step 1 : ids. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        encode(root) ;
        // step 2 : swap the children of every node through ptr
        for(ll id = 1 ; id <= n ; id++)
        {
            ptr[id]->left = ptr[rc[id]] ;
            ptr[id]->right = ptr[lc[id]] ;
        }
        // step 3
        return root ;
    }
};
