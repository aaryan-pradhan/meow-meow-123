// orz
// 222. Count Complete Tree Nodes · LeetCode · Medium
//
// Question:
// given the root of a complete binary tree, return the number of nodes.
// complete : every level except possibly the last is completely filled, and the
// nodes of the last level are as far left as possible.
// Example 1: root = [1,2,3,4,5,6] -> 6
// Example 2: root = []            -> 0
// Example 3: root = [1]           -> 1
// Constraints: 0 <= number of nodes <= 5 * 10^4, 0 <= Node.val <= 5 * 10^4, the tree is complete.
// Follow up: design an algorithm that runs in less than O(n) time. -> done here, O(log^2 n).
//
// 1. Mathematical statement
//    return n = the number of nodes, using that the tree is complete.
//
// 2. Brute force
//    any dfs that visits every node and counts it : O(n). (my ids template is O(n)
//    just to encode, so no ids here.)
//
// 3. What the brute force wastes
//    a perfect tree with h levels (every level full) has exactly 2^h - 1 nodes, and a
//    complete tree is mostly made of perfect pieces. counting those node by node wastes the formula.
//
// 4. Key breaking point
//    hl = number of nodes on the walk from cur going left only, hr = going right only.
//    in a complete tree the left walk always reaches the last level.
//    the right walk reaches it only when the last level is full.
//    so hl == hr <=> perfect <=> 2^hl - 1 nodes, found in O(h).
//    when hl != hr : both children are complete trees again, and at least one is perfect:
//      the last level reaches into the right child -> the left child is full, perfect.
//      the last level stops inside the left child  -> the right child has no last level nodes, perfect.
//    the perfect child answers right after its two walks, so only ONE child goes deeper.
//
// 5. Method
//    step 1 : leftheight(cur) = number of nodes on cur, cur->left, cur->left->left, .. until NULL.
//             rightheight(cur) = the same going right.
//    step 2 : countnodes(cur) : cur == NULL -> 0.
//    step 3 : hl = leftheight(cur), hr = rightheight(cur). hl == hr -> return 2^hl - 1 = (1LL << hl) - 1.
//    step 4 : else return 1 + countnodes(cur->left) + countnodes(cur->right).
//    step 5 : return countnodes(root).
//
// 6. Why it works
//    step 3 is exact for a perfect subtree, step 4 is just "cur plus both children", and
//    a subtree of a complete tree is complete again, so the reasoning repeats.
//    cost : every call does two walks of O(h). per level only one child goes deeper, the other
//    is perfect and stops after its walks, so there are about 2 calls per level, O(h) calls.
//    time O(h^2) = O(log^2 n) (h <= 16 for 5 * 10^4 nodes), space O(h) for the recursion.
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
ll leftheight(TreeNode* cur)
{
    // step 1 : this returns the number of nodes on the walk from cur going left only
    ll h = 0 ;
    while(cur != NULL)
    {
        h++ ;
        cur = cur->left ;
    }
    return h ;
}
ll rightheight(TreeNode* cur)
{
    // step 1 : this returns the number of nodes on the walk from cur going right only
    ll h = 0 ;
    while(cur != NULL)
    {
        h++ ;
        cur = cur->right ;
    }
    return h ;
}
ll countnodes(TreeNode* cur)
{
    // this returns the number of nodes in the complete subtree of cur
    // step 2 : empty
    if(cur == NULL)
    {
        return 0 ;
    }
    // step 3 : both walks equally long means the subtree is perfect
    ll hl = leftheight(cur) ;
    ll hr = rightheight(cur) ;
    if(hl == hr)
    {
        return (1LL << hl) - 1 ;
    }
    // step 4 : one child is perfect and stops at once, only the other one goes deeper
    else
    {
        return 1 + countnodes(cur->left) + countnodes(cur->right) ;
    }
}
class Solution {
public:
    int countNodes(TreeNode* root) {
        // step 5
        return countnodes(root) ;
    }
};
