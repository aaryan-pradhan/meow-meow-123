// orz
// 133. Clone Graph · LeetCode · Medium
//
// Question:
// given a reference to a node of a connected undirected graph, return a deep
// copy (clone) of the graph. each node has an int val and a list neighbors of
// Node*. node i has val = i, and the given node is the one with val = 1.
// (the judge writes the graph as an adjacency list, 1-indexed.)
// Example 1: adjList = [[2,4],[1,3],[2,4],[1,3]] -> [[2,4],[1,3],[2,4],[1,3]]
// Example 2: adjList = [[]]                      -> [[]]   (one node, no edges)
// Example 3: adjList = []                        -> []     (empty graph, node = NULL)
// Constraints: 0 <= number of nodes <= 100, 1 <= Node.val <= 100, every val is unique,
//              no repeated edges, no self-loops, the graph is connected.
//
// 1. Mathematical statement
//    graph G = (V, E) given by pointers. build new nodes v' for every v in V,
//    with v'.val = v.val and v'.neighbors = (u' for u in v.neighbors, same order).
//    no new node may point to an old node.
//
// 2. Brute force
//    copy(v) = make v', then v'.neighbors[i] = copy(v.neighbors[i]), with no memory.
//    on a cycle (1 - 2 - 1 ..) it never stops, and even without one it makes a new
//    copy of a node for every path that reaches it.
//
// 3. What the brute force wastes
//    it copies the same node again and again, because it can't tell "I already made 2'".
//
// 4. Key breaking point
//    vals are unique and in 1 .. 100, so val is already an id, like the ids in my tree
//    template. ptr[id] = old node, cp[id] = its copy. then it is my bfs on g to find
//    every node once, then one pass that makes the copies, then one pass that wires them.
//
// 5. Method
//    step 1 : node == NULL -> return NULL.
//    step 2 : bfs from node over the neighbors lists. ptr[id] = the old node with val id,
//             ptr[id] != NULL means visited (marked when pushed). ids = every id seen.
//    step 3 : cp[id] = new Node(id) for every id seen.
//    step 4 : for every id and every old neighbour u of ptr[id]:
//             cp[id]->neighbors.push_back(cp[u->val]). same order as the old list.
//    step 5 : return cp[node->val].
//
// 6. Why it works
//    the graph is connected, so the bfs reaches every node, and once each (val is unique).
//    step 3 makes exactly one copy per node. step 4 gives every copy the copies of exactly
//    its old neighbours, so the new graph has the same shape and only new pointers.
//    time O(V + E), space O(V) for ptr, cp and the queue.
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
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Solution {
public:
    Node* cloneGraph(Node* node) {
        // step 1 : empty graph
        if(node == NULL)
        {
            return NULL ;
        }
        // step 2 : bfs over the old graph, val is the id
        vector < Node* > ptr(101 , NULL) ; // ptr[id] = the old node with val id, NULL = not visited
        vector < ll > ids ;                // this stores every id the bfs reached
        queue < ll > q ;
        q.push(node->val) ;
        ptr[node->val] = node ;
        while(!q.empty())
        {
            ll id = q.front() ;
            q.pop() ;
            ids.push_back(id) ;
            for(auto child : ptr[id]->neighbors)
            {
                if(ptr[child->val] == NULL)
                {
                    ptr[child->val] = child ;
                    q.push(child->val) ;
                }
            }
        }
        // step 3 : one copy per node
        vector < Node* > cp(101 , NULL) ; // cp[id] = the copy of ptr[id]
        for(auto id : ids)
        {
            cp[id] = new Node(id) ;
        }
        // step 4 : wire the copies like the old nodes
        for(auto id : ids)
        {
            for(auto child : ptr[id]->neighbors)
            {
                cp[id]->neighbors.push_back(cp[child->val]) ;
            }
        }
        // step 5
        return cp[node->val] ;
    }
};
