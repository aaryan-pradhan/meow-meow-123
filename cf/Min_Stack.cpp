// orz
// 155. Min Stack · LeetCode · Medium
//
// Question:
// design a stack that supports push, pop, top and getting the minimum element,
// each in O(1) time. implement class MinStack:
//   MinStack()          initializes the stack.
//   void push(int val)  pushes val onto the stack.
//   void pop()          removes the top element.
//   int top()           returns the top element.
//   int getMin()        returns the minimum element in the stack.
// Example 1: ["MinStack","push","push","push","getMin","pop","top","getMin"]
//            [[],[-2],[0],[-3],[],[],[],[]]
//            -> [null,null,null,null,-3,null,0,-2]
// Constraints: -2^31 <= val <= 2^31 - 1, pop, top and getMin are always called
//              on a non-empty stack, at most 3 * 10^4 calls in total
//
// 1. Mathematical statement
//    keep a sequence v1 .. vk with push / pop at the end, and answer
//    min(v1 .. vk) in O(1).
//
// 2. Brute force
//    a plain stack, and getMin scans every element. O(k) per getMin,
//    up to 3 * 10^4 * 3 * 10^4 = 9 * 10^8, and the judge asks for O(1).
//
// 3. What the brute force wastes
//    a stack only changes at the top, so the elements below the top never change.
//    their min is the same every time getMin scans them.
//
// 4. Key breaking point
//    a prefix min: next to every element store the min of everything from the
//    bottom up to it. pop removes an element and its prefix min together, so the
//    new top's stored min is still right. getMin = the top's stored min.
//
// 5. Method
//    step 1 : st holds pairs (value , min of the stack up to this value).
//    step 2 : push(val): mn = val if the stack is empty, else min(val , st.back().sc).
//             push (val , mn).
//    step 3 : pop(): pop_back.
//    step 4 : top(): st.back().fr.
//    step 5 : getMin(): st.back().sc.
//
// 6. Why it works
//    by induction st[i].sc = min(st[0].fr .. st[i].fr): true for the bottom, and
//    step 2 extends it by one. pop never changes the pairs below. so the top pair
//    always holds the min of the whole stack.
//    time O(1) per call, extra space O(k).
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
class MinStack {
public:
    // step 1 : st[i] = (value , min of st[0 .. i])
    vector < pll > st ;
    MinStack() {
        st.clear() ;
    }

    void push(int val) {
        // step 2 : the new prefix min
        ll mn = val ;
        if(!st.empty())
        {
            mn = min(mn , st.back().sc) ;
        }
        st.push_back({val , mn}) ;
    }

    void pop() {
        // step 3
        st.pop_back() ;
    }

    int top() {
        // step 4
        return st.back().fr ;
    }

    int getMin() {
        // step 5
        return st.back().sc ;
    }
};
