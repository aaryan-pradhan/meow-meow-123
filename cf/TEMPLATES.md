# Templates for the Top 150 solutions

Every solution file starts with the question and the 6-step header, then the orz
macro block, then `class Solution` with the exact LeetCode signature. No `main`.
The code is tagged `// step k`, the same k as in step 5 of the header.

The 4 samples are the model: `House_Robber.cpp` (DP), `Product_of_Array_Except_Self.cpp`
(array), `Reverse_Linked_List_II.cpp` (linked list), `Binary_Tree_Maximum_Path_Sum.cpp` (tree).

## Header

```
// orz
// <number>. <Title> · LeetCode · <Easy|Medium|Hard>
//
// Question:
// <statement in plain words>
// Example 1: ...
// Constraints: ...
// Follow up: ... -> done here.          (only when the follow-up is the intended answer)
//
// 1. Mathematical statement
// 2. Brute force                        (and its complexity)
// 3. What the brute force wastes
// 4. Key breaking point                 (the trick that turns it into a standard problem)
// 5. Method                             (step 1 : .. step 2 : .. small steps)
// 6. Why it works                       (plus time and space)
```

## Linked list: dummy node

LeetCode lists are solved on the list itself, never copied into a vector.
O(1) extra space when the judge asks for it.

```cpp
ListNode* dummy = new ListNode(0) ;
dummy->next = head ;
ListNode* tail = dummy ;   // last node of the answer built so far
// ... walk with raw pointers, tail->next = node ; tail = node ;
return dummy->next ;       // the head may have changed, dummy never does
```

Three-pointer reverse:

```cpp
ListNode* prev = NULL ;
ListNode* cur = first ;
while(cur != NULL)
{
    ListNode* nxt = cur->next ;
    cur->next = prev ;
    prev = cur ;
    cur = nxt ;
}
```

## Binary tree: ids + g, then my dfs(node , par)

Give every TreeNode an id 1 .. n, keep `ptr[id]`, `lc[id]`, `rc[id]` (0 = no child,
like my 0 sink) and an undirected `g`. Then every tree problem is my usual
`dfs(node , par)`. Use `lc` / `rc` when left vs right matters (BST order,
symmetric, inorder). To change the tree (invert, flatten, connect), rewire
through `ptr[id]->left = ptr[...]`.

```cpp
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
```

In the method, reset every global first (LeetCode keeps globals between tests):

```cpp
n = 0 ;
ptr.assign(1 , NULL) ;
lc.assign(1 , 0) ;
rc.assign(1 , 0) ;
ll rootid = encode(root) ;   // 0 when root is NULL, handle that first
buildg() ;
```

When the problem builds a new tree (from an array or from traversals), there is
nothing to encode: write a plain `build(l , r)` that returns `TreeNode*`, like my
segment tree `build(id , l , r)`.

## Simulate the statement literally

When the statement already is the algorithm (Roman numerals, spiral, zigzag,
text justification, add binary), the method is the statement turned into steps,
one `// step k` per rule, with no tricks.

## Design problems (LRU Cache, Min Stack, Trie, ...)

The class LeetCode gives replaces `class Solution`. Same header, same orz block,
state as members, each method tagged with its step.

## DP

Form → Level → Choice → Check → Move → Cost (prob/prob.html). Write the
top-down `rec` commented out with a `// this returns` line, then the bottom-up
loop with `continue` base cases. Rolling rows always `dp[i & 1]` and
`dp[(i + 1) & 1]`.
