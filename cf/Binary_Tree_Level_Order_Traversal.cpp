// orz
// 102. Binary Tree Level Order Traversal · LeetCode · Medium
//
// Question:
// given the root of a binary tree, return the level order traversal of its
// nodes' values: level by level from the top, and from left to right inside
// each level.
// Example 1: root = [3,9,20,null,null,15,7] -> [[3],[9,20],[15,7]]
// Example 2: root = [1]                     -> [[1]]
// Example 3: root = []                      -> []
// Constraints: 0 <= number of nodes <= 2000, -1000 <= Node.val <= 1000
//
// 1. Mathematical statement
//    depth(v) = number of edges from the root to v.
//    ans[d] = the values of all v with depth d, in left to right order, for d = 0, 1, ..
//
// 2. Brute force
//    for every depth d, walk the whole tree left before right and collect the
//    nodes of depth d. up to n depths, O(n) per walk = O(n^2).
//
// 3. What the brute force wastes
//    every walk visits every node and then throws away all the nodes that are
//    not at its one depth.
//
// 4. Key breaking point
//    this is exactly the order my BFS pops the nodes in: level by level, and
//    left to right inside a level. so one BFS with lvl[node] fills every row:
//    ans[lvl[node]].push_back(val) in pop order.
//
// 5. Method
//    step 1 : give every node an id 1 .. n and build g (tree template). empty tree -> [].
//    step 2 : bfs from the root with my queue. lvl[child] = lvl[node] + 1,
//             lvl = -1 means not visited yet (marked when pushed).
//    step 3 : when node is popped: if lvl[node] == ans.size() open a new row,
//             then push its value into ans[lvl[node]].
//    step 4 : return ans.
//
// 6. Why it works
//    encode gives a parent a smaller id than its children, so buildg fills
//    g[node] as (parent, left child, right child): left is pushed before right.
//    BFS pops level d before level d + 1. and if level d is popped left to right,
//    the children of a left node are pushed before the children of a node to its
//    right, so level d + 1 is also popped left to right. so every row is filled
//    in left to right order, and the rows open top-down.
//    time O(n), space O(n) for the ids, g, lvl and the queue.
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        // step 1 : ids + g. reset every global, LeetCode keeps them between test cases
        n = 0 ;
        ptr.assign(1 , NULL) ;
        lc.assign(1 , 0) ;
        rc.assign(1 , 0) ;
        ll rootid = encode(root) ;
        buildg() ;
        vector < vector < int > > ans ;
        if(rootid == 0)
        {
            return ans ;
        }
        // step 2 : bfs from the root, lvl = -1 means not visited
        vector < ll > lvl(n + 1 , -1) ;
        queue < ll > q ;
        q.push(rootid) ;
        lvl[rootid] = 0 ;
        while(!q.empty())
        {
            ll node = q.front() ;
            q.pop() ;
            // step 3 : node goes at the end of the row of its level
            if(lvl[node] == (ll)ans.size())
            {
                ans.push_back(vector < int > ()) ;
            }
            ans[lvl[node]].push_back(ptr[node]->val) ;
            for(auto child : g[node])
            {
                if(lvl[child] == -1)
                {
                    lvl[child] = lvl[node] + 1 ;
                    q.push(child) ;
                }
            }
        }
        // step 4
        return ans ;
    }
};
