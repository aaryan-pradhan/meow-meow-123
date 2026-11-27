// orz
// 106. Construct Binary Tree from Inorder and Postorder Traversal · LeetCode · Medium
//
// Question:
// given two integer arrays inorder and postorder, the inorder and the postorder
// traversal of the same binary tree, build that tree and return its root.
// Example 1: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3] -> [3,9,20,null,null,15,7]
// Example 2: inorder = [-1], postorder = [-1]                   -> [-1]
// Constraints: 1 <= n = inorder.length <= 3000, postorder.length == n,
//              -3000 <= values <= 3000, all values are distinct,
//              both arrays are guaranteed to be traversals of the same tree.
//
// 1. Mathematical statement
//    inorder(T)   = inorder(left), root, inorder(right).
//    postorder(T) = postorder(left), postorder(right), root.
//    find the tree T with these two sequences (values distinct, so T is unique).
//
// 2. Brute force
//    root = the last value of postorder. scan inorder for it: everything before it is the
//    left subtree, everything after it the right subtree. cut postorder by those sizes,
//    copy the four pieces into new arrays and recurse. O(n^2) on a chain.
//
// 3. What the brute force wastes
//    the scan for a value in inorder gives the same answer every time (values are distinct),
//    and the copies only pass on pieces that are already contiguous.
//
// 4. Key breaking point
//    read postorder BACKWARDS: root, then the whole right subtree, then the whole left subtree.
//    that is a preorder with right before left. so it is Construct from Preorder and Inorder
//    mirrored: pass only the inorder range [l , r], keep one global index pi that walks
//    postorder from the back, pos[value] = index of value in inorder, and build the RIGHT
//    subtree first. a plain build(l , r), like my segment tree build(id , l , r).
//
// 5. Method
//    step 1 : pos[inorder[i]] = i for every i, pi = n - 1 (reset every global).
//    step 2 : build(l , r) returns the root of the subtree whose inorder is inorder[l .. r].
//             l > r -> empty, NULL.
//    step 3 : the root is post[pi], the last unused postorder value. pi--.
//    step 4 : m = pos[root value]. right = build(m + 1 , r), THEN left = build(l , m - 1).
//             right first, because backwards postorder lists the whole right subtree before the left one.
//    step 5 : return build(0 , n - 1).
//
// 6. Why it works
//    inorder puts the root between its left and its right subtree, so m splits [l , r] exactly.
//    build makes nodes in the order root, right, left, the same order as postorder read
//    backwards, so post[pi] is always the root of the range being built.
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
vector < ll > post ;   // this stores postorder
map < ll , ll > pos ;  // pos[value] = index of value in inorder
ll pi ;                // index of the last unused value in post, it walks backwards
TreeNode* build(ll l , ll r)
{
    // this returns the root of the subtree whose inorder is inorder[l .. r]
    // step 2 : empty range
    if(l > r)
    {
        return NULL ;
    }
    // step 3 : the last unused postorder value is the root
    TreeNode* cur = new TreeNode(post[pi]) ;
    pi-- ;
    // step 4 : split inorder at the root, right subtree first
    ll m = pos[cur->val] ;
    cur->right = build(m + 1 , r) ;
    cur->left = build(l , m - 1) ;
    return cur ;
}
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // step 1 : reset every global, LeetCode keeps them between test cases
        ll n = inorder.size() ;
        post.assign(n , 0) ;
        pos.clear() ;
        for(ll i = 0 ; i < n ; i++)
        {
            post[i] = postorder[i] ;
            pos[inorder[i]] = i ;
        }
        pi = n - 1 ;
        // step 5
        return build(0 , n - 1) ;
    }
};
