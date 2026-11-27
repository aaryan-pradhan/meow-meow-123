// orz
// 173. Binary Search Tree Iterator · LeetCode · Medium
//
// Question:
// implement the class BSTIterator, which walks the inorder (sorted) order of a BST:
// BSTIterator(root) : starts the iterator just before the smallest value.
// hasNext()         : true if there is a next value in the inorder order.
// next()            : moves to the next value and returns it.
// next() is only called when there is a next value.
// Example 1: ["BSTIterator","next","next","hasNext","next","hasNext","next","hasNext","next","hasNext"]
//            [[[7,3,15,null,null,9,20]],[],[],[],[],[],[],[],[],[]]
//            -> [null,3,7,true,9,true,15,true,20,false]
// Constraints: 1 <= number of nodes <= 10^5, 0 <= Node.val <= 10^6,
//              at most 10^5 calls in total to hasNext and next.
// Follow up: next() and hasNext() in O(1) average time with O(h) memory (h = height of the tree). -> done here.
//
// 1. Mathematical statement
//    x1 < x2 < .. < xn is the inorder order. after k calls to next, the next call returns
//    x(k + 1), and hasNext = (k < n). memory must stay O(h).
//
// 2. Brute force
//    in the constructor, run the whole inorder dfs into an array a, keep an index i.
//    next = a[i], i++. hasNext = i < n. O(1) per call, but O(n) memory, and the follow-up wants O(h).
//    (my ids template is O(n) memory too, so no ids here.)
//
// 3. What the brute force wastes
//    it keeps all n values at once, while a call only needs the one next value.
//
// 4. Key breaking point
//    don't finish the inorder dfs, PAUSE it. the recursion stack of an inorder dfs is one
//    path of nodes that are still waiting for their turn: their left side is being done,
//    they and their right side are not. keep that stack by hand. the smallest value not
//    returned yet is always on top.
//
// 5. Method
//    step 1 : pushleft(cur) : while cur != NULL, push cur and go to cur->left.
//             it pushes cur and its left spine, so the smallest value under cur ends on top.
//    step 2 : constructor : pushleft(root).
//    step 3 : next() : top = the top of the stack, pop it. everything left of top is returned
//             already, so what comes right after top is its right subtree: pushleft(top->right).
//             return top->val.
//    step 4 : hasNext() : the stack is not empty.
//
// 6. Why it works
//    every node in the stack waits for its own left subtree, and that subtree is either returned
//    already or sits above it in the stack. so the top waits for nothing: it is the smallest
//    value not returned yet. after top is returned, the values right after it are its right
//    subtree, smallest first, and pushleft puts exactly that smallest one on top. once the
//    right subtree is empty, the next waiting ancestor is on top.
//    memory : the stack is always part of one root to node path, so O(h).
//    time : every node is pushed once and popped once over all the calls, so n calls to next
//    cost O(n) in total = O(1) average. hasNext is O(1).
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
class BSTIterator {
public:
    stack < TreeNode* > s ; // this stores the nodes still waiting for their turn, the smallest on top
    void pushleft(TreeNode* cur)
    {
        // step 1 : this pushes cur and its left spine
        while(cur != NULL)
        {
            s.push(cur) ;
            cur = cur->left ;
        }
    }
    BSTIterator(TreeNode* root) {
        // step 2 : the smallest value of the tree ends on top
        pushleft(root) ;
    }

    int next() {
        // step 3 : the top is the smallest value not returned yet
        TreeNode* top = s.top() ;
        s.pop() ;
        // its right subtree comes right after it
        pushleft(top->right) ;
        return top->val ;
    }

    bool hasNext() {
        // step 4
        return !s.empty() ;
    }
};
