// orz
// 97. Interleaving String · LeetCode · Medium
//
// Question:
// given strings s1, s2 and s3, find whether s3 is formed by an interleaving of s1 and s2:
// s1 and s2 are cut into pieces and the pieces are put one after the other, taking
// turns between s1 and s2, keeping the order inside each string.
// (in short: every letter of s3 comes from s1 or from s2, each of s1 and s2 is used
// fully and in order.)
// Example 1: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac" -> true
// Example 2: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc" -> false
// Example 3: s1 = "", s2 = "", s3 = ""                     -> true
// Constraints: 0 <= s1.length, s2.length <= 100, 0 <= s3.length <= 200,
//              s1, s2 and s3 consist of lowercase English letters
// Follow up: only O(s2.length) additional memory space. -> done here.
//
// 1. Mathematical statement
//    n = |s1|, m = |s2|. is there a split of the positions 0 .. n + m - 1 of s3 into a
//    set A of size n and the rest B of size m, such that s3 read on A (in order) is s1
//    and s3 read on B (in order) is s2? (|s3| != n + m -> false.)
//
// 2. Brute force
//    letter by letter, try "this letter of s3 comes from s1" and "from s2".
//    up to C(200 , 100) splits. dead.
//
// 3. What the brute force wastes
//    after i letters of s1 and j letters of s2 are used, s3 is used up to i + j and the
//    rest only depends on (i , j). many different splits reach the same (i , j).
//
// 4. Key breaking point
//    multi-sequence form: state (i , j), the position in s3 is i + j, not a third index.
//    row i reads only row i + 1 and itself, so two rows of m + 1 (the follow up).
//
// 5. Method
//    step 1 : |s3| != n + m -> false.
//    step 2 : FORM = multi-sequence. rec(i , j) = true if s1[i ..] and s2[j ..] can be
//             interleaved into s3[i + j ..].
//    step 3 : CHECK : i == n and j == m -> true, everything is used.
//    step 4 : CHOICE + MOVE : the next letter s3[i + j] comes from
//             s1 : allowed if i < n and s1[i] == s3[i + j], then rec(i + 1 , j).
//             s2 : allowed if j < m and s2[j] == s3[i + j], then rec(i , j + 1).
//             rec(i , j) = fromone or fromtwo.
//    step 5 : COST : 101 * 101 states, 2 moves. tiny.
//    step 6 : bottom up, i from n down to 0, j from m down to 0.
//    step 7 : rolling rows. dp[i & 1] is row i, dp[(i + 1) & 1] is row i + 1.
//             fromtwo reads dp[i & 1][j + 1], already written this pass. answer dp[0][0].
//
// 6. Why it works
//    in any valid interleaving the letter s3[i + j] is the next unused letter of s1 or
//    of s2, and the rest is a valid interleaving of what is left. trying both covers
//    every interleaving, so rec(0 , 0) is exact.
//    time O(n * m), extra space O(m) = O(s2.length).
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
// bool rec(ll i , ll j)
// {
//     // this returns true if s1[i ..] and s2[j ..] can be interleaved into s3[i + j ..]
//     if(i == n && j == m)
//     {
//         return true ;
//     }
//     if(dp[i][j] != -1)
//     {
//         return dp[i][j] ;
//     }
//     bool fromone = false , fromtwo = false ;
//     if(i < n && s1[i] == s3[i + j])
//     {
//         fromone = rec(i + 1 , j) ;
//     }
//     if(j < m && s2[j] == s3[i + j])
//     {
//         fromtwo = rec(i , j + 1) ;
//     }
//     return dp[i][j] = (fromone || fromtwo) ;
// }
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        ll n = s1.size() ;
        ll m = s2.size() ;
        // step 1 : the lengths must add up
        if((ll)s3.size() != n + m)
        {
            return false ;
        }
        // step 7 : two rows of m + 1, dp[i & 1]
        vector < vector < ll > > dp(2 , vector < ll > (m + 1 , 0)) ;
        // step 6 : i from n down to 0, j from m down to 0
        for(ll i = n ; i >= 0 ; i--)
        {
            for(ll j = m ; j >= 0 ; j--)
            {
                // step 3 : everything used
                if(i == n && j == m)
                {
                    dp[i & 1][j] = 1 ;
                    continue ;
                }
                // step 4 : the next letter of s3 comes from s1 or from s2
                bool fromone = false , fromtwo = false ;
                if(i < n && s1[i] == s3[i + j])
                {
                    fromone = dp[(i + 1) & 1][j] ;
                }
                if(j < m && s2[j] == s3[i + j])
                {
                    fromtwo = dp[i & 1][j + 1] ;
                }
                if(fromone || fromtwo)
                {
                    dp[i & 1][j] = 1 ;
                }
                else
                {
                    dp[i & 1][j] = 0 ;
                }
            }
        }
        if(dp[0][0] == 1)
        {
            return true ;
        }
        else
        {
            return false ;
        }
    }
};
