// orz
// 530. Minimum Absolute Difference in BST · LeetCode · Easy
//
// Question:
// given the root of a binary search tree, return the minimum absolute
// difference between the values of any two different nodes in the tree.
// Example 1: root = [4,2,6,1,3]              -> 1
// Example 2: root = [1,0,48,null,null,12,49] -> 1
// Constraints: 2 <= number of nodes <= 10^4, 0 <= Node.val <= 10^5
//
// 1. Mathematical statement
//    minimise |val(u) - val(v)| over every pair of different nodes u != v.
//
// 2. Brute force
//    try every pair of nodes. n * (n - 1) / 2 pairs, n = 10^4 gives 5 * 10^7.
//    passes, but it never uses that the tree is a BST.
//
// 3. What the brute force wastes
//    once the values are sorted, a pair far apart in the sorted order can never
//    beat a pair of neighbours between them. almost every pair is hopeless.
//
// 4. Key breaking point
//    the inorder walk of a BST (left subtree, node, right subtree) lists the values
//    in sorted order. and in a sorted list the closest pair is always two neighbours.
//    so the answer is min(inord[i] - inord[i - 1]) over neighbours: a linear scan.
//
// 5. Method
//    step 1 : give every node an id 1 .. n with lc / rc (tree template).
//             left vs right matters here, so I walk lc / rc. g is not needed.
//    step 2 : inorder(id): inorder(lc[id]), push val, inorder(rc[id]). id 0 = no node, return.
//    step 3 : ans = min over i of inord[i] - inord[i - 1]. ans starts at INF.
//    step 4 : return ans.
//
// 6. Why it works
//    BST: everything in the left subtree < node < everything in the right subtree, so by
//    induction on the subtree size, the inorder list of every subtree is sorted.
//    for sorted a and i < j: a[j] - a[i] >= a[i + 1] - a[i], so some neighbour pair
//    is at least as close as any pair. the scan sees every neighbour pair.
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
    int getMinimumDifference(TreeNode* root) {
        // step 1 : ids + lc / rc. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        // step 2 : sorted values
        inord.clear() ;
        inorder(rootid) ;
        // step 3 : closest pair is two neighbours
        ll ans = INF ;
        for(ll i = 1 ; i < (ll)inord.size() ; i++)
        {
            ans = min(ans , inord[i] - inord[i - 1]) ;
        }
        // step 4
        return ans ;
    }
};
