// orz
// 105. Construct Binary Tree from Preorder and Inorder Traversal · LeetCode · Medium
//
// Question:
// given two integer arrays preorder and inorder, the preorder and the inorder
// traversal of the same binary tree, build that tree and return its root.
// Example 1: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7] -> [3,9,20,null,null,15,7]
// Example 2: preorder = [-1], inorder = [-1]                   -> [-1]
// Constraints: 1 <= n = preorder.length <= 3000, inorder.length == n,
//              -3000 <= values <= 3000, all values are distinct,
//              both arrays are guaranteed to be traversals of the same tree.
//
// 1. Mathematical statement
//    preorder(T) = root, preorder(left), preorder(right).
//    inorder(T)  = inorder(left), root, inorder(right).
//    find the tree T with these two sequences (values distinct, so T is unique).
//
// 2. Brute force
//    root = preorder[0]. scan inorder for it: everything before it is the left subtree,
//    everything after it the right subtree. cut preorder by those sizes, copy the four
//    pieces into new arrays and recurse on each side. O(n^2) on a chain, from the scans and the copies.
//
// 3. What the brute force wastes
//    the scan for a value in inorder gives the same answer every time (values are distinct),
//    and the copies only pass on pieces that are already contiguous.
//
// 4. Key breaking point
//    every subtree is a contiguous range of inorder. and its nodes come in preorder in
//    exactly the order the recursion asks for them: root, then the whole left subtree,
//    then the whole right subtree. so pass only the inorder range [l , r], keep one global
//    index pi into preorder that moves forward by 1 for every new node, and precompute
//    pos[value] = index of value in inorder.
//    that is a plain build(l , r), like my segment tree build(id , l , r).
//
// 5. Method
//    step 1 : pos[inorder[i]] = i for every i, pi = 0 (reset every global).
//    step 2 : build(l , r) returns the root of the subtree whose inorder is inorder[l .. r].
//             l > r -> empty, NULL.
//    step 3 : the root is preorder[pi], the next unused preorder value. pi++.
//    step 4 : m = pos[root value]. left = build(l , m - 1), THEN right = build(m + 1 , r).
//             left first, because preorder lists the whole left subtree before the right one.
//    step 5 : return build(0 , n - 1).
//
// 6. Why it works
//    inorder puts the root between its left and its right subtree, so m splits [l , r] exactly.
//    build makes nodes in the order root, left, right, the same order as preorder,
//    so preorder[pi] is always the root of the range being built.
//    time O(n log n) with the map, space O(n) for pos and the recursion.
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
vector < ll > pre ;    // this stores preorder
map < ll , ll > pos ;  // pos[value] = index of value in inorder
ll pi ;                // index of the next unused value in pre
TreeNode* build(ll l , ll r)
{
    // this returns the root of the subtree whose inorder is inorder[l .. r]
    // step 2 : empty range
    if(l > r)
    {
        return NULL ;
    }
    // step 3 : the next preorder value is the root
    TreeNode* cur = new TreeNode(pre[pi]) ;
    pi++ ;
    // step 4 : split inorder at the root, left subtree first
    ll m = pos[cur->val] ;
    cur->left = build(l , m - 1) ;
    cur->right = build(m + 1 , r) ;
    return cur ;
}
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // step 1 : reset every global, LeetCode keeps them between test cases
        ll n = preorder.size() ;
        pre.assign(n , 0) ;
        pos.clear() ;
        for(ll i = 0 ; i < n ; i++)
        {
            pre[i] = preorder[i] ;
            pos[inorder[i]] = i ;
        }
        pi = 0 ;
        // step 5
        return build(0 , n - 1) ;
    }
};
