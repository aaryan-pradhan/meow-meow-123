// orz
// 100. Same Tree · LeetCode · Easy
//
// Question:
// given the roots of two binary trees p and q, return true if they are the same.
// two trees are the same when they have the same shape and the nodes in the
// same places have the same values.
// Example 1: p = [1,2,3], q = [1,2,3]  -> true
// Example 2: p = [1,2], q = [1,null,2] -> false
// Example 3: p = [1,2,1], q = [1,1,2]  -> false
// Constraints: 0 <= number of nodes in each tree <= 100, -10^4 <= Node.val <= 10^4
//
// 1. Mathematical statement
//    p = q when both are empty, or both are non-empty with val(p) = val(q),
//    left(p) = left(q) and right(p) = right(q).
//
// 2. Brute force
//    for every node of p, write its path from the root as moves L / R, walk the same
//    moves from the root of q, and check that a node is there with the same value.
//    then the same from q into p, because q may have extra nodes. O(n * h).
//
// 3. What the brute force wastes
//    the walk to a node repeats the whole walk to its parent.
//
// 4. Key breaking point
//    encode numbers the nodes in preorder (node, then its left subtree, then its right subtree),
//    and that numbering depends only on the shape. two trees with the same shape get the
//    same ids at the same places, so "the node at the same place" is the node with the same id.
//    so same tree <=> same n, and for every id : same lc, same rc, same value.
//
// 5. Method
//    step 1 : encode p (tree template, no g here: only left vs right matters).
//             keep a copy of its n, ptr, lc, rc.
//    step 2 : reset the globals and encode q.
//    step 3 : different n -> false.
//    step 4 : for every id 1 .. n : lc, rc and val must match, else false.
//    step 5 : everything matched -> true. (both empty: n = 0 on both sides -> true)
//
// 6. Why it works
//    preorder ids depend only on the shape, so same shape -> same ids, same lc / rc.
//    the other way, lc / rc read from id 1 rebuild the whole shape, so same lc / rc -> same shape.
//    with equal values at every id, the two trees are equal.
//    time O(n), space O(n) for the ids and the copy.
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // step 1 : ids for p. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        encode(p) ;
        ll np = n ;
        vector < TreeNode* > ptrp = ptr ;
        vector < ll > lcp = lc ;
        vector < ll > rcp = rc ;
        // step 2 : ids for q
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        encode(q) ;
        // step 3 : different number of nodes
        if(np != n)
        {
            return false ;
        }
        // step 4 : the same id is the same place in both trees
        for(ll id = 1 ; id <= n ; id++)
        {
            if(lcp[id] != lc[id] || rcp[id] != rc[id])
            {
                return false ; // different shape
            }
            else if(ptrp[id]->val != ptr[id]->val)
            {
                return false ; // same place, different value
            }
            else
            {
                continue ;
            }
        }
        // step 5
        return true ;
    }
};
