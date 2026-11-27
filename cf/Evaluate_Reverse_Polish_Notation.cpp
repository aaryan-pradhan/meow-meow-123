// orz
// 150. Evaluate Reverse Polish Notation · LeetCode · Medium
//
// Question:
// given an array of string tokens that is an arithmetic expression in Reverse
// Polish Notation (operator after its two operands), evaluate it and return the
// integer value. operators are '+', '-', '*', '/'. each operand is an integer or
// another expression. division between two integers truncates toward zero.
// there is no division by zero, the input is always a valid RPN expression,
// and the answer and every intermediate result fit in a 32-bit integer.
// Example 1: tokens = ["2","1","+","3","*"]                  -> 9    ((2 + 1) * 3)
// Example 2: tokens = ["4","13","5","/","+"]                 -> 6    (4 + (13 / 5))
// Example 3: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"] -> 22
// Constraints: 1 <= tokens.length <= 10^4, tokens[i] is an operator or an integer
//              in [-200, 200]
//
// 1. Mathematical statement
//    RPN: a number is an expression, and "E1 E2 op" is the expression E1 op E2.
//    compute its value.
//
// 2. Brute force
//    find the first operator, apply it to the two numbers right before it, replace
//    the three tokens by the result, and repeat until one token is left.
//    each round is O(n) to find and to shift, n / 2 rounds: O(n^2).
//
// 3. What the brute force wastes
//    every round scans again from the start, but the numbers waiting for an
//    operator are always the last ones read, in order.
//
// 4. Key breaking point
//    "the two numbers right before the operator" = the two most recent unused
//    numbers = the top two of a stack.
//
// 5. Method
//    step 1 : number token: push it. ("-11" is a number, "-" alone is an operator.)
//    step 2 : operator token: b = pop (the right operand, pushed last), a = pop.
//             push a op b. C++ '/' truncates toward zero, which is what is asked.
//    step 3 : at the end the stack holds exactly the value, return it.
//
// 6. Why it works
//    after reading a prefix, the stack holds the values of the finished
//    sub-expressions not used yet, left to right. "E1 E2 op" puts E1 then E2 on the
//    stack, so op takes E2 as b and E1 as a, the right order for '-' and '/'.
//    time O(n), extra space O(n).
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
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        ll n = tokens.size() ;
        // this stores the values of the sub-expressions not used yet
        stack < ll > st ;
        for(ll i = 0 ; i < n ; i++)
        {
            string x = tokens[i] ;
            // step 1 : a number
            if(x != "+" && x != "-" && x != "*" && x != "/")
            {
                st.push(stoll(x)) ;
                continue ;
            }
            // step 2 : an operator takes the top two, b is on top
            ll b = st.top() ;
            st.pop() ;
            ll a = st.top() ;
            st.pop() ;
            if(x == "+")
            {
                st.push(a + b) ;
            }
            else if(x == "-")
            {
                st.push(a - b) ;
            }
            else if(x == "*")
            {
                st.push(a * b) ;
            }
            else
            {
                st.push(a / b) ;
            }
        }
        // step 3
        return st.top() ;
    }
};
