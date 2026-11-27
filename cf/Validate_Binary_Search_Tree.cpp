// orz
// 98. Validate Binary Search Tree · LeetCode · Medium
//
// Question:
// given the root of a binary tree, decide if it is a valid binary search tree.
// a valid BST: the left subtree of a node holds only values strictly less than
// the node's value, the right subtree holds only values strictly greater, and
// both subtrees are valid BSTs too.
// Example 1: root = [2,1,3]                  -> true
// Example 2: root = [5,1,4,null,null,3,6]    -> false  (3 is in the right subtree of 5)
// Constraints: 1 <= number of nodes <= 10^4, -2^31 <= Node.val <= 2^31 - 1
//
// 1. Mathematical statement
//    for every node v: val(u) < val(v) for every u in the left subtree of v,
//    and val(u) > val(v) for every u in the right subtree of v.
//
// 2. Brute force
//    for every node v, walk both of its subtrees and compare each node with v.
//    O(n) per node, O(n^2) = 10^8 for a chain of 10^4 nodes. slow.
//
// 3. What the brute force wastes
//    for v, only the biggest value on its left and the smallest value on its right
//    can break the rule, and the walk compares every other node too.
//
// 4. Key breaking point
//    a tree is a BST  <=>  its inorder walk (left subtree, node, right subtree) is
//    strictly increasing. so: write the inorder list, check every neighbour pair.
//
// 5. Method
//    step 1 : give every node an id 1 .. n with lc / rc (tree template).
//             left vs right matters here, so I walk lc / rc. g is not needed.
//    step 2 : inorder(id): inorder(lc[id]), push val, inorder(rc[id]). id 0 = no node, return.
//    step 3 : if some inord[i] <= inord[i - 1], it is not a BST: return false.
//             <= and not <, because equal values are not allowed either.
//    step 4 : else return true.
//
// 6. Why it works
//    =>  if it is a BST, by induction on the subtree size: the inorder of the left
//        subtree is increasing and all < v, then v, then the right part, increasing and all > v.
//    <=  if the inorder is strictly increasing: the left subtree of v is written just
//        before v and the right subtree just after, so left values < v < right values.
//        and the inorder of each subtree is a piece of the list, so it is increasing
//        too, and the same argument works inside it.
//    values reach 2^31 - 1, so I keep them in ll (no INT tricks with sentinels needed).
//    time O(n), space O(n) for the ids, inord and the recursion.
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
vector < ll > inord ; // this stores the values in inorder
void inorder(ll id)
{
    // this pushes the values of the subtree of id into inord, in left - node - right order
    if(id == 0)
    {
        return ;
    }
    inorder(lc[id]) ;
    inord.push_back(ptr[id]->val) ;
    inorder(rc[id]) ;
}
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // step 1 : ids + lc / rc. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        // step 2 : inorder list
        inord.clear() ;
        inorder(rootid) ;
        // step 3 : every neighbour pair must go strictly up
        for(ll i = 1 ; i < (ll)inord.size() ; i++)
        {
            if(inord[i] <= inord[i - 1])
            {
                return false ;
            }
            else
            {
                continue ;
            }
        }
        // step 4
        return true ;
    }
};
