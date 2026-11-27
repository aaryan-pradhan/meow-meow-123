// orz
// 101. Symmetric Tree · LeetCode · Easy
//
// Question:
// given the root of a binary tree, check whether it is a mirror of itself
// (symmetric around its center).
// Example 1: root = [1,2,2,3,4,4,3]       -> true
// Example 2: root = [1,2,2,null,3,null,3] -> false
// Constraints: 1 <= number of nodes <= 1000, -100 <= Node.val <= 100
//
// 1. Mathematical statement
//    mirror(a , b) is true when both are empty, or both are non-empty with val(a) = val(b),
//    mirror(left(a) , right(b)) and mirror(right(a) , left(b)).
//    answer = mirror(left(root) , right(root)).
//
// 2. Brute force
//    make an inverted copy of the tree (Invert Binary Tree), then run Same Tree on
//    the tree and its copy. O(n), but n new nodes and two extra passes.
//
// 3. What the brute force wastes
//    the copy. the mirror image of the left half is only needed to be compared with
//    the right half, and that comparison can look at the two halves directly.
//
// 4. Key breaking point
//    symmetric <=> the left subtree is the mirror of the right subtree.
//    walk a PAIR (a , b) down together: the outside pair (left of a , right of b) and the
//    inside pair (right of a , left of b) must be mirrors again. left vs right matters,
//    so this walks lc / rc of the ids, not g.
//
// 5. Method
//    step 1 : give every node an id (tree template, no g here).
//    step 2 : mirror(a , b) : both 0 (empty) -> true.
//    step 3 : only one of them 0, or ptr[a]->val != ptr[b]->val -> false.
//    step 4 : else mirror(lc[a] , rc[b]) and mirror(rc[a] , lc[b]).
//    step 5 : answer = mirror(lc[root] , rc[root]).
//
// 6. Why it works
//    step 2 - 4 are the mathematical statement word for word, and every call moves both
//    a and b one level down, so it ends. every node is in at most one call.
//    time O(n), space O(n) for the ids and the recursion.
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
bool mirror(ll a , ll b)
{
    // this returns true if the subtree of id a is the mirror image of the subtree of id b
    // step 2 : both empty
    if(a == 0 && b == 0)
    {
        return true ;
    }
    // step 3 : only one empty, or different values
    if(a == 0 || b == 0)
    {
        return false ;
    }
    if(ptr[a]->val != ptr[b]->val)
    {
        return false ;
    }
    // step 4 : outside pair and inside pair
    bool outside = mirror(lc[a] , rc[b]) ;
    bool inside = mirror(rc[a] , lc[b]) ;
    return outside && inside ;
}
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // step 1 : ids. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        // step 5 : the two halves must mirror each other
        return mirror(lc[rootid] , rc[rootid]) ;
    }
};
