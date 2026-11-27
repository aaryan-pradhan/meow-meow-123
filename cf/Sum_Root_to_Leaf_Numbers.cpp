// orz
// 129. Sum Root to Leaf Numbers · LeetCode · Medium
//
// Question:
// every node holds one digit 0 .. 9. every root-to-leaf path is read as a number,
// e.g. the path 1 -> 2 -> 3 is the number 123. return the sum of all these numbers.
// a leaf is a node with no children. the answer fits in a 32-bit integer.
// Example 1: root = [1,2,3]       -> 25    (12 + 13)
// Example 2: root = [4,9,0,5,1]   -> 1026  (495 + 491 + 40)
// Constraints: 1 <= number of nodes <= 1000, 0 <= Node.val <= 9, depth of the tree <= 10
//
// 1. Mathematical statement
//    for a leaf v with path root = u1, u2, .. , uk = v, num(v) = digits w(u1) w(u2) .. w(uk)
//    = sum of w(ui) * 10^(k - i). return the sum of num(v) over all leaves v.
//
// 2. Brute force
//    for every leaf, walk up to the root, collect the digits, reverse them, build the number.
//    O(n * h).
//
// 3. What the brute force wastes
//    leaves under the same node read the same top digits again.
//
// 4. Key breaking point
//    num(root -> child) = num(root -> node) * 10 + w(child): appending a digit is * 10 + digit.
//    carry the number down as a dfs parameter, exactly like depth in my dfs(node , par , depth).
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template).
//    step 2 : dfs(node , par , num) with num = number above node. num = num * 10 + w(node).
//    step 3 : count the children while going down. children == 0 means node is a leaf: ans += num.
//    step 4 : return ans.
//
// 6. Why it works
//    every root to leaf path is one branch of the dfs and arrives at its leaf with its exact
//    number. depth <= 10, so a number is < 10^10, kept in ll, and the total fits in int (given).
//    time O(n), space O(n) for the ids, g and the recursion.
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
ll ans ;
void dfs(ll node , ll par , ll num)
{
    // step 2 : now num = the digits from the root down to node
    num = num * 10 + ptr[node]->val ;
    ll children = 0 ;
    for(auto child : g[node])
    {
        if(child != par)
        {
            children++ ;
            dfs(child , node , num) ;
        }
    }
    // step 3 : no children means node is a leaf, num is a whole root-to-leaf number
    if(children == 0)
    {
        ans += num ;
    }
}
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        buildg() ;
        // step 2 : nothing above the root, num starts at 0
        ans = 0 ;
        dfs(rootid , 0 , 0) ;
        // step 4
        return ans ;
    }
};
