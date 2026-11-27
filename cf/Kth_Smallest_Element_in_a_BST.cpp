// orz
// 230. Kth Smallest Element in a BST · LeetCode · Medium
//
// Question:
// given the root of a binary search tree and an integer k, return the k-th
// smallest value (1-indexed) of all the values of the nodes in the tree.
// Example 1: root = [3,1,4,null,2], k = 1           -> 1
// Example 2: root = [5,3,6,2,4,null,null,1], k = 3  -> 3
// Constraints: 1 <= k <= n <= 10^4 (n = number of nodes), 0 <= Node.val <= 10^4
//
// 1. Mathematical statement
//    sort the n values a1 <= a2 <= .. <= an. return ak.
//
// 2. Brute force
//    walk the tree in any order, copy all values, sort them, return the k-th.
//    O(n log n). it passes, but it sorts values the tree already keeps in order.
//
// 3. What the brute force wastes
//    the BST already knows the order (left subtree < node < right subtree),
//    and the sort throws that away and finds it again.
//
// 4. Key breaking point
//    the inorder walk of a BST (left subtree, node, right subtree) lists the values
//    already sorted. so the k-th value of the inorder list is the answer. no sort.
//
// 5. Method
//    step 1 : give every node an id 1 .. n with lc / rc (tree template).
//             left vs right matters here, so I walk lc / rc. g is not needed.
//    step 2 : inorder(id): inorder(lc[id]), push val, inorder(rc[id]). id 0 = no node, return.
//    step 3 : return inord[k - 1] (k is 1-indexed, inord is 0-indexed).
//
// 6. Why it works
//    BST: everything in the left subtree < node < everything in the right subtree, so by
//    induction on the subtree size, the inorder list of every subtree is sorted.
//    so inord is a1 .. an and inord[k - 1] = ak.
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
vector < ll > inord ; // this stores the values in inorder, which is sorted for a BST
void inorder(ll id)
{
    // this pushes the values of the subtree of id into inord, from smallest to largest
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
    int kthSmallest(TreeNode* root, int k) {
        // step 1 : ids + lc / rc. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        // step 2 : sorted values
        inord.clear() ;
        inorder(rootid) ;
        // step 3 : k is 1-indexed
        return inord[k - 1] ;
    }
};
