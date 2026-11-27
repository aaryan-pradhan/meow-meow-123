// orz
// 427. Construct Quad Tree · LeetCode · Medium
//
// Question:
// given an n x n matrix grid of 0s and 1s only, represent it with a quad tree and return its root.
// every node of a quad tree has two fields and four children:
//   val    : true if the node stands for a square of 1s, false for a square of 0s
//            (any value is accepted when isLeaf is false).
//   isLeaf : true if the node is a leaf (no children), false if it has exactly four children.
// to build it for a square: if every cell of the square has the same value, make a leaf with that
// value. else make an inner node, split the square into 4 equal squares (topLeft, topRight,
// bottomLeft, bottomRight) and build each of them the same way.
// Example 1: grid = [[0,1],[1,0]] -> [[0,1],[1,0],[1,1],[1,1],[1,0]]  (as [isLeaf,val] in level order)
// Example 2: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],
//                    [1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
//            -> [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
// Constraints: n == grid.length == grid[i].length, n == 2^x with 0 <= x <= 6.
//
// 1. Mathematical statement
//    for a square Q (top-left (r , c), side len): if all cells of Q are 0 or all are 1, Q is a leaf
//    with that value. else Q has the 4 children built from its 4 quarters. build the tree of the whole grid.
//
// 2. Brute force
//    follow the definition and scan every cell of the square to see if it is all one value.
//    a cell gets scanned once on every level that contains it, so O(n^2 log n). fine for n = 64,
//    but every level scans again what the level above already looked at.
//
// 3. What the brute force wastes
//    the only question asked of a square is "how many 1s are in it". that is a 2D range sum,
//    and the brute force answers it by scanning every time.
//
// 4. Key breaking point
//    my 2D prefix sums: ps[i][j] = number of 1s in grid[0 .. i - 1][0 .. j - 1] (zero row and column).
//    ones in a square = ps[r + len][c + len] - ps[r][c + len] - ps[r + len][c] + ps[r][c], O(1).
//    ones = 0 : all 0s, leaf false. ones = len * len : all 1s, leaf true. anything else : split.
//
// 5. Method
//    step 1 : ps[i][j] = grid[i - 1][j - 1] + ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1].
//    step 2 : boxsum(r , c , len) = the number of 1s in the square with top-left (r , c) and side len.
//    step 3 : build(r , c , len) : ones = boxsum. 0 -> new Node(false , true). len * len -> new Node(true , true).
//    step 4 : else h = len / 2, build the 4 quarters (r , c), (r , c + h), (r + h , c), (r + h , c + h)
//             in the order topLeft, topRight, bottomLeft, bottomRight, and join them in an inner node.
//    step 5 : reset ps, the answer is build(0 , 0 , n).
//
// 6. Why it works
//    build follows the definition word for word, and boxsum gives the exact count of 1s, so
//    "all the same" is decided exactly. len is a power of 2, so the halves are always whole squares
//    and len = 1 is always a leaf. time O(n^2) for ps plus O(1) per tree node (<= 4 n^2 / 3 nodes),
//    space O(n^2).
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
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
vector < vector < ll > > ps ; // ps[i][j] = number of 1s in grid[0 .. i - 1][0 .. j - 1]
ll boxsum(ll r , ll c , ll len)
{
    // step 2 : this returns the number of 1s in the square with top-left (r , c) and side len
    return ps[r + len][c + len] - ps[r][c + len] - ps[r + len][c] + ps[r][c] ;
}
Node* build(ll r , ll c , ll len)
{
    // step 3 : this builds the quad tree of the square with top-left (r , c) and side len
    ll ones = boxsum(r , c , len) ;
    if(ones == 0)
    {
        return new Node(false , true) ;
    }
    if(ones == len * len)
    {
        return new Node(true , true) ;
    }
    // step 4 : mixed square, split it into 4 quarters
    ll h = len / 2 ;
    Node* topleft = build(r , c , h) ;
    Node* topright = build(r , c + h , h) ;
    Node* bottomleft = build(r + h , c , h) ;
    Node* bottomright = build(r + h , c + h , h) ;
    return new Node(true , false , topleft , topright , bottomleft , bottomright) ;
}
class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        // step 5 : reset every global, LeetCode keeps them between test cases
        ll n = grid.size() ;
        ps.assign(n + 1 , vector < ll > (n + 1 , 0)) ;
        // step 1 : 2D prefix sums, 1-indexed with a zero row and column
        for(ll i = 1 ; i <= n ; i++)
        {
            for(ll j = 1 ; j <= n ; j++)
            {
                ps[i][j] = grid[i - 1][j - 1] + ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] ;
            }
        }
        return build(0 , 0 , n) ;
    }
};
