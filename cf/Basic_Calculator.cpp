// orz
// 224. Basic Calculator · LeetCode · Hard
//
// Question:
// given a string s that is a valid expression, evaluate it and return the result.
// s has digits, '+', '-', '(', ')' and ' '. you may not use eval().
// '+' is never unary ("+1" and "+(2 + 3)" are invalid). '-' can be unary
// ("-1" and "-(2 + 3)" are valid). there are no two operators in a row.
// every number and every running result fits in a signed 32-bit integer.
// Example 1: s = "1 + 1"                 -> 2
// Example 2: s = " 2-1 + 2 "             -> 3
// Example 3: s = "(1+(4+5+2)-3)+(6+8)"   -> 23
// Constraints: 1 <= s.length <= 3 * 10^5
//
// 1. Mathematical statement
//    there is no * or /, so the value is a signed sum: every number x in s adds
//    sign(x) * x, where sign(x) = its own sign times the signs in front of every
//    '(' that encloses it.
//    e.g. 1 - (2 - (3 + 4)): 1 -> +1, 2 -> -1, 3 -> (-)(-) = +1, 4 -> +1. value 1 - 2 + 3 + 4 = 6.
//
// 2. Brute force
//    find an innermost "( .. )", evaluate the flat part inside, write the result
//    back into the string, repeat. each round is O(n), up to n / 2 rounds:
//    O(n^2) = (3 * 10^5)^2 = 9 * 10^10. dead.
//
// 3. What the brute force wastes
//    it rewrites the string over and over. but by 1 each number only needs its
//    final sign, and that sign is known the moment the number is read, from the
//    '(' that are open around it.
//
// 4. Key breaking point
//    a stack of signs, one per open '(': the top = the product of the signs in
//    front of all the open '('. then one left to right pass adds every number with
//    top * (its own sign).
//
// 5. Method
//    step 1 : ans = 0, sign = +1 (the sign right before the next number or '('),
//             st = [+1] (outside every bracket the multiplier is +1).
//    step 2 : digit: read the whole number num. ans += st.top() * sign * num.
//    step 3 : '+': sign = +1. '-': sign = -1.
//    step 4 : '(': this group's multiplier = st.top() * sign, push it. sign = +1
//             (a fresh start inside the group).
//    step 5 : ')': the group is over, pop its multiplier.
//    step 6 : ' ': skip. return ans after the pass.
//
// 6. Why it works
//    st.top() is always the product of the signs in front of the open '(', so
//    st.top() * sign is exactly sign(x) from 1. a unary '-' at the start or after
//    '(' just sets sign = -1, the same as a binary '-'. so ans is the signed sum in 1.
//    time O(n), extra space O(depth of brackets).
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
    int calculate(string s) {
        ll n = s.size() ;
        // step 1 : st stores the sign multiplier of every open bracket
        ll ans = 0 ;
        ll sign = 1 ;
        stack < ll > st ;
        st.push(1) ;
        for(ll i = 0 ; i < n ; i++)
        {
            char c = s[i] ;
            if(c >= '0' && c <= '9')
            {
                // step 2 : read the whole number, add it with its final sign
                ll num = 0 ;
                while(i < n && s[i] >= '0' && s[i] <= '9')
                {
                    num = num * 10 + (s[i] - '0') ;
                    i++ ;
                }
                i-- ; // i is on the last digit, the for loop moves past it
                ans += st.top() * sign * num ;
            }
            // step 3 : the sign of the next term
            else if(c == '+')
            {
                sign = 1 ;
            }
            else if(c == '-')
            {
                sign = -1 ;
            }
            // step 4 : open a group
            else if(c == '(')
            {
                st.push(st.top() * sign) ;
                sign = 1 ;
            }
            // step 5 : close the group
            else if(c == ')')
            {
                st.pop() ;
            }
            // step 6 : a space
            else
            {
                continue ;
            }
        }
        return ans ;
    }
};
