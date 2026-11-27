// orz
// 138. Copy List with Random Pointer · LeetCode · Medium
//
// Question:
// a linked list of length n is given where each node has an extra pointer random,
// which points to any node in the list or to null. make a deep copy: n brand new
// nodes, each with the value of its original, where the next and random pointers of
// the new nodes point to new nodes, so that the copy shows the same list. no pointer
// of the copy may point into the original list. return the head of the copy.
// (the judge shows each node as [val, random_index], random_index = null for no random.)
// Example 1: head = [[7,null],[13,0],[11,4],[10,2],[1,0]] -> [[7,null],[13,0],[11,4],[10,2],[1,0]]
// Example 2: head = [[1,1],[2,1]]                         -> [[1,1],[2,1]]
// Example 3: head = [[3,null],[3,0],[3,null]]             -> [[3,null],[3,0],[3,null]]
// Constraints: 0 <= n <= 1000, -10^4 <= Node.val <= 10^4,
//              Node.random is null or points to some node in the linked list
//
// 1. Mathematical statement
//    original nodes x1 .. xn with next(xi) = x(i + 1) and random(xi) = xj or NULL.
//    build new nodes y1 .. yn with val(yi) = val(xi), next(yi) = y(i + 1),
//    random(yi) = yj exactly when random(xi) = xj (NULL when it is NULL).
//    so the whole job is the map copy(xj) = yj.
//
// 2. Brute force
//    copy the next chain first. then for each xi with random(xi) = xj: walk from head to
//    find j, then walk j steps in the copy to find yj. O(n) per random, O(n^2) total.
//    (a hash map from xj to yj makes it O(n) time but costs O(n) extra memory.)
//
// 3. What the brute force wastes
//    every random pointer asks the same question, "where is the copy of xj?",
//    and answers it by walking from head again (or by keeping a whole map).
//
// 4. Key breaking point
//    store the answer in the list itself: put the copy of every node right after it,
//    x1 -> y1 -> x2 -> y2 -> .. -> xn -> yn. now copy(x) = x->next, an O(1) lookup with no map.
//    afterwards pull the two lists apart again.
//
// 5. Method
//    step 1 : weave. for every original x: make y with the same val,
//             y->next = x->next, x->next = y. then jump to y->next (the next original).
//    step 2 : randoms. for every original x (every other node), with y = x->next:
//             if x->random is NULL, y->random = NULL,
//             else y->random = x->random->next (the copy sits right after its original).
//    step 3 : unweave. dummy node for the copy, tail = dummy. for every original x with
//             y = x->next: x->next = y->next (x gets its old next back),
//             tail->next = y, tail = y.
//             step 3 must be a separate pass after step 2: a later random can point back
//             to an earlier node, and step 2 needs that node still followed by its copy.
//    step 4 : return dummy->next.
//
// 6. Why it works
//    after step 1 every original x is followed by its own copy, so x->next = copy(x).
//    step 2 reads only that, so every random of the copy points to the right copy node.
//    step 3 gives every x back the next it had (y->next was the old x->next), so the
//    original list is exactly as before, and chains y1 -> y2 -> .. -> yn in order; the
//    last yn->next is the old xn->next = NULL.
//    time O(n), extra space O(1) besides the n copied nodes themselves.
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
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // step 1 : weave, every copy sits right after its original
        Node* cur = head ;
        while(cur != NULL)
        {
            Node* copy = new Node(cur->val) ;
            copy->next = cur->next ;
            cur->next = copy ;
            cur = copy->next ;
        }
        // step 2 : random of the copy = the node right after the original's random
        cur = head ;
        while(cur != NULL)
        {
            Node* copy = cur->next ;
            if(cur->random == NULL)
            {
                copy->random = NULL ;
            }
            else
            {
                copy->random = cur->random->next ;
            }
            cur = copy->next ;
        }
        // step 3 : unweave, give the originals their next back, chain the copies
        Node* dummy = new Node(0) ;
        Node* tail = dummy ;
        cur = head ;
        while(cur != NULL)
        {
            Node* copy = cur->next ;
            cur->next = copy->next ;
            tail->next = copy ;
            tail = copy ;
            cur = cur->next ;
        }
        // step 4
        return dummy->next ;
    }
};
