// orz
// 22. Generate Parentheses · LeetCode · Medium
//
// Question:
// given n pairs of parentheses, generate all combinations of well-formed parentheses.
// the answer can be in any order.
// Example 1: n = 3 -> ["((()))","(()())","(())()","()(())","()()()"]
// Example 2: n = 1 -> ["()"]
// Constraints: 1 <= n <= 8.
//
// 1. Mathematical statement
//    return every string s of length 2n over '(' and ')' such that
//    in every prefix #'(' >= #')', and in the whole string #'(' = #')' = n.
//
// 2. Brute force
//    build all 2^(2n) strings, keep the balanced ones.
//    2^16 = 65536 strings * 16. it passes, but only 1430 of them are balanced (n = 8).
//
// 3. What the brute force wastes
//    a string that starts with ")" or has 4 "(" out of n = 3 is dead from that moment,
//    yet the brute force finishes it and checks it at the end.
//
// 4. Key breaking point
//    check the rule while building, one character at a time. keep open = #'(' and close = #')'
//    used so far. a '(' is allowed iff open < n. a ')' is allowed iff close < open
//    (the prefix stays balanced). then every string the rec finishes is valid.
//
// 5. Method
//    step 1 : rec(open , close) : cur = the string so far, with open '(' and close ')'.
//    step 2 : |cur| = 2n : cur is a full valid string, push it to ans, return.
//    step 3 : if open < n : add '(' , rec(open + 1 , close), remove it.
//    step 4 : if close < open : add ')' , rec(open , close + 1), remove it.
//    step 5 : reset the globals, rec(0 , 0).
//
// 6. Why it works
//    step 3 keeps open <= n, step 4 keeps close <= open in every prefix, and length 2n with
//    open <= n and close <= open forces open = close = n. so every leaf is valid. and every valid
//    string only ever adds allowed characters, so it is one path of the rec.
//    time O(Catalan(n) * n), space O(n) besides the answer.
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
ll pairs ; // n
string cur ;
vector < string > ans ;
void rec(ll open , ll close)
{
    // step 1 : this finishes cur in every valid way, cur already has open '(' and close ')'
    // step 2 : full length
    if((ll)cur.size() == 2 * pairs)
    {
        ans.push_back(cur) ;
        return ;
    }
    // step 3 : one more '(' still fits
    if(open < pairs)
    {
        cur.push_back('(') ;
        rec(open + 1 , close) ;
        cur.pop_back() ;
    }
    // step 4 : a ')' keeps the prefix balanced
    if(close < open)
    {
        cur.push_back(')') ;
        rec(open , close + 1) ;
        cur.pop_back() ;
    }
}
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        // step 5 : reset every global, LeetCode keeps them between test cases
        pairs = n ;
        cur = "" ;
        ans.clear() ;
        rec(0 , 0) ;
        return ans ;
    }
};
