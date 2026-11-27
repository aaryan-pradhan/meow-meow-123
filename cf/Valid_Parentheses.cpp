// orz
// 20. Valid Parentheses · LeetCode · Easy
//
// Question:
// given a string s of just the characters '(', ')', '{', '}', '[' and ']',
// return true if it is valid: every open bracket is closed by the same type of
// bracket, open brackets are closed in the correct order, and every close
// bracket has a matching open bracket.
// Example 1: s = "()"       -> true
// Example 2: s = "()[]{}"   -> true
// Example 3: s = "(]"       -> false
// Example 4: s = "([])"     -> true
// Example 5: s = "([)]"     -> false
// Constraints: 1 <= s.length <= 10^4, s is only '()[]{}'
//
// 1. Mathematical statement
//    s is valid iff it reduces to "" by repeatedly deleting an adjacent pair
//    "()", "[]" or "{}".
//
// 2. Brute force
//    do exactly that: scan for an adjacent matching pair, delete it, repeat.
//    up to n / 2 rounds of O(n) each, O(n^2) = 10^8 / 2. slow and clumsy.
//
// 3. What the brute force wastes
//    each round rescans the whole string from the start, but the only pair that
//    can appear new after a deletion is right where the deletion happened.
//
// 4. Key breaking point
//    a close bracket must match the LAST open bracket that is still open.
//    "last open, first closed" is a stack.
//
// 5. Method
//    step 1 : open bracket: push it.
//    step 2 : close bracket: want = its matching open bracket.
//             if the stack is empty (nothing to close) or the top is not want, return false.
//             else pop: this pair is done.
//    step 3 : at the end, valid iff nothing is left open (stack empty).
//
// 6. Why it works
//    the stack holds exactly the brackets that are open and not closed yet, in order.
//    deleting the pair (top, current close) is one deletion of the brute force, done
//    at the only place a new pair can appear. so the scan succeeds iff the
//    deletions reduce s to "".
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
    bool isValid(string s) {
        ll n = s.size() ;
        // this stores the open brackets that are not closed yet
        stack < char > st ;
        for(ll i = 0 ; i < n ; i++)
        {
            char c = s[i] ;
            // step 1 : open bracket
            if(c == '(' || c == '[' || c == '{')
            {
                st.push(c) ;
                continue ;
            }
            // step 2 : close bracket, it must match the last open one
            char want ;
            if(c == ')')
            {
                want = '(' ;
            }
            else if(c == ']')
            {
                want = '[' ;
            }
            else
            {
                want = '{' ;
            }
            if(st.empty() || st.top() != want)
            {
                return false ;
            }
            else
            {
                st.pop() ;
            }
        }
        // step 3 : nothing may stay open
        return st.empty() ;
    }
};
