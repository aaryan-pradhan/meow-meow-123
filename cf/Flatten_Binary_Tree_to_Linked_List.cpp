// orz
// 114. Flatten Binary Tree to Linked List · LeetCode · Medium
//
// Question:
// given the root of a binary tree, flatten it into a "linked list" in place:
// the same nodes, right is the next pointer, left is always NULL, and the
// order of the list is the preorder of the tree.
// Example 1: root = [1,2,5,3,4,null,6] -> [1,null,2,null,3,null,4,null,5,null,6]
// Example 2: root = []                 -> []
// Example 3: root = [0]                -> [0]
// Constraints: 0 <= number of nodes <= 2000, -100 <= Node.val <= 100
//
// 1. Mathematical statement
//    let v1 .. vn be the nodes in preorder. set right(vi) = v(i + 1), right(vn) = NULL
//    and left(vi) = NULL for every i, without making new nodes.
//
// 2. Brute force
//    repeat : find the first node in preorder that still has a left child, walk to the last
//    node of that left subtree, hang the right subtree there, move the left subtree to the right.
//    every round starts again from the root : O(n^2).
//
// 3. What the brute force wastes
//    every round walks the tree again to find a preorder that never changes.
//
// 4. Key breaking point
//    the preorder is fixed before I change anything, and encode already numbers the nodes
//    in preorder (node, then its left subtree, then its right subtree). so ptr[1] .. ptr[n]
//    IS the list, and the whole job is rewiring ptr[id]->right = ptr[id + 1].
//
// 5. Method
//    step 1 : give every node an id (tree template, no g here). ptr[id] = the id-th node in preorder.
//    step 2 : ptr[n + 1] = NULL, so the last node gets right = NULL like every other.
//    step 3 : for id = 1 .. n : ptr[id]->left = NULL, ptr[id]->right = ptr[id + 1].
//             (empty tree : n = 0, nothing to do)
//
// 6. Why it works
//    encode visits node, left subtree, right subtree, which is preorder, so ptr is the list order.
//    every id was given before the first pointer changed, so the rewiring can't spoil the walk.
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
    void flatten(TreeNode* root) {
        // step 1 : ids in preorder. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        encode(root) ;
        // step 2 : ptr[n + 1] = NULL ends the list
        ptr.push_back(NULL) ;
        // step 3 : chain ptr[1] .. ptr[n] through right
        for(ll id = 1 ; id <= n ; id++)
        {
            ptr[id]->left = NULL ;
            ptr[id]->right = ptr[id + 1] ;
        }
    }
};
