// orz
// 139. Word Break · LeetCode · Medium
//
// Question:
// given a string s and a dictionary of strings wordDict, return true if s can be
// segmented into a space-separated sequence of one or more dictionary words.
// the same word may be reused any number of times.
// Example 1: s = "leetcode", wordDict = ["leet","code"]                     -> true
// Example 2: s = "applepenapple", wordDict = ["apple","pen"]                -> true  (apple pen apple)
// Example 3: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]  -> false
// Constraints: 1 <= s.length <= 300, 1 <= wordDict.length <= 1000,
//              1 <= wordDict[i].length <= 20, s and wordDict[i] are lowercase English letters,
//              all the strings of wordDict are unique
//
// 1. Mathematical statement
//    is there a cut 0 = c0 < c1 < .. < ck = n with every piece s[c(j) .. c(j + 1) - 1]
//    in wordDict?
//
// 2. Brute force
//    try every set of cut positions: 2^(n - 1) of them, n = 300. dead.
//
// 3. What the brute force wastes
//    once the pieces cover s[0 .. i - 1], whether the rest can be cut only depends
//    on i. every cut set that reaches i asks the same question about s[i ..] again.
//
// 4. Key breaking point
//    the state is the start index i of what is left. the choice is the next word.
//    a reachability DP: rec(i) = OR over words that fit at i.
//
// 5. Method
//    step 1 : FORM = i -> end. rec(i) = true if s[i .. n - 1] can be cut into dictionary words.
//    step 2 : CHOICE at level i : the next piece is one of the words w.
//    step 3 : CHECK : i == n means nothing is left, true.
//             a word w fits at i if i + |w| <= n and s.substr(i , |w|) == w.
//    step 4 : MOVE : rec(i) = OR of rec(i + |w|) over the words w that fit at i.
//    step 5 : COST : n + 1 states, each tries 1000 words of length <= 20,
//             301 * 1000 * 20 = 6 * 10^6. fine.
//    step 6 : bottom up, i from n down to 0, so every i + |w| is ready before i.
//             no rolling here: i + |w| can be up to 20 ahead.
//
// 6. Why it works
//    a valid cut of s[i ..] starts with some dictionary word w at i, and the rest
//    is a valid cut of s[i + |w| ..]. so rec(i) is true exactly when some fitting w
//    has rec(i + |w|) true. answer rec(0).
//    time O(n * |wordDict| * 20), extra space O(n).
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
// bool rec(ll i)
// {
//     // this returns true if s[i .. n - 1] can be cut into dictionary words
//     if(i == n)
//     {
//         return true ;
//     }
//     if(dp[i] != -1)
//     {
//         return dp[i] ;
//     }
//     bool ans = false ;
//     for(auto w : wordDict)
//     {
//         ll len = w.size() ;
//         if(i + len <= n && s.substr(i , len) == w)
//         {
//             ans = ans || rec(i + len) ;
//         }
//     }
//     return dp[i] = ans ;
// }
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        ll n = s.size() ;
        vector < bool > dp(n + 1 , false) ;
        // step 6 : i from n down to 0
        for(ll i = n ; i >= 0 ; i--)
        {
            // step 3 : nothing left
            if(i == n)
            {
                dp[i] = true ;
                continue ;
            }
            // step 2 : try every word as the next piece
            bool ans = false ;
            for(auto w : wordDict)
            {
                ll len = w.size() ;
                // step 3 : does w fit at i
                if(i + len <= n && s.substr(i , len) == w)
                {
                    // step 4
                    ans = ans || dp[i + len] ;
                }
                else
                {
                    continue ;
                }
            }
            dp[i] = ans ;
        }
        return dp[0] ;
    }
};
