// orz
// 117. Populating Next Right Pointers in Each Node II · LeetCode · Medium
//
// Question:
// given a binary tree whose nodes have val, left, right and next, point every
// next to the node right after it on the same level (left to right). the last
// node of a level gets next = NULL. at the start every next is NULL. return root.
// Example 1: root = [1,2,3,4,5,null,7] -> [1,#,2,3,#,4,5,7,#]   (# ends a level, read along next)
// Example 2: root = []                 -> []
// Constraints: 0 <= number of nodes <= 6000, -100 <= Node.val <= 100
//
// 1. Mathematical statement
//    for every depth d, let v1 .. vk be the nodes at depth d from left to right.
//    set next(vi) = v(i + 1) for i < k, and next(vk) = NULL.
//
// 2. Brute force
//    for every node u, look at every node of the same depth and keep the closest one
//    to the right of u (compare the root to node paths as strings, L < R).
//    O(n^2 * h).
//
// 3. What the brute force wastes
//    the answer for u is just the one after u in the left to right list of its level,
//    and the brute force rebuilds that list for every node.
//
// 4. Key breaking point
//    the ids from encode are preorder: node, then its whole left subtree, then its whole right subtree.
//    two different nodes x, y on the same level are not ancestors of each other. if x is left of y,
//    they split at some node z with x under left(z) and y under right(z), and all of left(z)
//    gets its ids before right(z). so on one level, left to right = increasing id.
//    walk the ids 1 .. n once and keep last[d] = the last id seen at depth d: a new id at
//    depth d is exactly the next of last[d].
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template, Node in place of TreeNode).
//             empty tree -> return root (NULL).
//    step 2 : dfs(node , par , depth) stores d[node], the root has depth 0.
//    step 3 : for id = 1 .. n in increasing order : if last[d[id]] != 0,
//             ptr[last[d[id]]]->next = ptr[id]. then last[d[id]] = id.
//    step 4 : the last node of every level keeps next = NULL (as given). return root.
//
// 6. Why it works
//    on every level, increasing id is left to right (the key breaking point), so
//    step 3 links every pair of neighbours on the level, and nothing else.
//    time O(n), space O(n) for the ids, g, d, last and the recursion.
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
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
// ---- tree template (TEMPLATES.md, Node in place of TreeNode) ----
ll n ;
vector < Node* > ptr ;  // ptr[id] = the tree node with this id
vector < ll > lc , rc ;     // lc[id] / rc[id] = id of the left / right child, 0 means no child
vector < vector < ll > > g ;
ll encode(Node* cur)
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
vector < ll > d ;  // d[id] = depth of node id, the root has depth 0
void dfs(ll node , ll par , ll depth)
{
    // step 2 : this stores the depth of node and of everything below it
    d[node] = depth ;
    for(auto child : g[node])
    {
        if(child != par)
        {
            dfs(child , node , depth + 1) ;
        }
    }
}
class Solution {
public:
    Node* connect(Node* root) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        if(rootid == 0)
        {
            return root ; // empty tree
        }
        buildg() ;
        // step 2 : depth of every node
        d.assign(n + 1 , 0) ;
        dfs(rootid , 0 , 0) ;
        // step 3 : on each level, increasing id = left to right
        vector < ll > last(n + 1 , 0) ; // last[depth] = last id seen at this depth, 0 = none yet
        for(ll id = 1 ; id <= n ; id++)
        {
            ll dep = d[id] ;
            if(last[dep] != 0)
            {
                ptr[last[dep]]->next = ptr[id] ;
            }
            last[dep] = id ;
        }
        // step 4
        return root ;
    }
};
