// orz
// 108. Convert Sorted Array to Binary Search Tree · LeetCode · Easy
//
// Question:
// given an integer array nums sorted in ascending order, convert it to a height-balanced
// binary search tree (for every node, the heights of its two subtrees differ by at most 1).
// any valid answer is accepted.
// Example 1: nums = [-10,-3,0,5,9] -> [0,-3,9,-10,null,5]   ([0,-10,5,null,-3,null,9] is also accepted)
// Example 2: nums = [1,3]          -> [3,1]                 ([1,null,3] is also accepted)
// Constraints: 1 <= nums.length <= 10^4, -10^4 <= nums[i] <= 10^4, nums is strictly increasing.
//
// 1. Mathematical statement
//    build a binary tree on the values nums[0 .. n - 1] with inorder = nums (that is the BST rule
//    for sorted distinct values) and |height(left) - height(right)| <= 1 at every node.
//
// 2. Brute force
//    insert the values into a BST one by one in the given order: a chain of height n,
//    not balanced. trying every insertion order is n!.
//
// 3. What the brute force wastes
//    the array is already sorted, so the inorder is known. the only real choice is which value
//    sits at the root of each piece, and the brute force never chooses it on purpose.
//
// 4. Key breaking point
//    inorder = nums means: the root of nums[l .. r] is some nums[mid], its left subtree is built
//    from nums[l .. mid - 1] and its right subtree from nums[mid + 1 .. r].
//    take mid = the middle, then the two halves differ in size by at most 1.
//    it is my segment tree build(id , l , r): split at the middle, build both halves, join.
//
// 5. Method
//    step 1 : build(l , r) returns the root of a balanced BST of nums[l .. r], NULL if l > r.
//    step 2 : mid = (l + r) / 2, make the node nums[mid].
//    step 3 : node->left = build(l , mid - 1), node->right = build(mid + 1 , r). return node.
//    step 4 : the answer is build(0 , n - 1).
//
// 6. Why it works
//    every node has the smaller values on its left and the bigger ones on its right, so it is a BST.
//    the halves have sizes that differ by at most 1, and build gives a piece of k nodes the
//    height floor(log2 k) + 1, which grows with k and differs by at most 1 for sizes k and k + 1,
//    so every node is balanced. time O(n), space O(log n) recursion besides the tree.
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
TreeNode* build(ll l , ll r , vector < int >& nums)
{
    // step 1 : this builds a balanced BST of nums[l .. r] and returns its root, NULL if the range is empty
    if(l > r)
    {
        return NULL ;
    }
    // step 2 : the middle value is the root
    ll mid = (l + r) / 2 ;
    TreeNode* node = new TreeNode(nums[mid]) ;
    // step 3 : the smaller half on the left, the bigger half on the right
    node->left = build(l , mid - 1 , nums) ;
    node->right = build(mid + 1 , r , nums) ;
    return node ;
}
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // step 4
        ll n = nums.size() ;
        return build(0 , n - 1 , nums) ;
    }
};
