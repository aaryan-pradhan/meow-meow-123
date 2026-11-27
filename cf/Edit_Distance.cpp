// orz
// 72. Edit Distance · LeetCode · Medium
//
// Question:
// given two strings word1 and word2, return the minimum number of operations needed
// to convert word1 into word2. one operation is: insert a character, delete a
// character, or replace a character.
// Example 1: word1 = "horse", word2 = "ros"           -> 3  (horse -> rorse -> rose -> ros)
// Example 2: word1 = "intention", word2 = "execution" -> 5
// Constraints: 0 <= word1.length, word2.length <= 500,
//              word1 and word2 consist of lowercase English letters
//
// 1. Mathematical statement
//    the smallest k such that k single-character inserts / deletes / replaces turn
//    word1 into word2.
//
// 2. Brute force
//    try all three operations at every position without remembering.
//    about 3^(n + m) branches, n = m = 500. dead.
//
// 3. What the brute force wastes
//    only the last characters decide the last operation, and after it what is left is
//    a pair of prefixes. the same pair of prefixes comes up again and again.
//
// 4. Key breaking point
//    state = (i , j) : the first i characters of word1 against the first j of word2.
//    look at the last characters: equal -> free, else add / remove / replace.
//    row i reads only rows i and i - 1, so two rows.
//
// 5. Method
//    step 1 : FORM = multi-sequence on prefixes. rec(i , j) = the edit distance between
//             word1[0 .. i - 1] and word2[0 .. j - 1].
//    step 2 : CHECK : i == 0 -> j (add all j letters). j == 0 -> i (remove all i letters).
//    step 3 : the last letters are equal (word1[i - 1] == word2[j - 1]) -> they cost
//             nothing, rec(i , j) = rec(i - 1 , j - 1).
//    step 4 : else CHOICE + MOVE, each costs 1 :
//             add     word2[j - 1] at the end : rec(i , j - 1) + 1
//             remove  word1[i - 1]            : rec(i - 1 , j) + 1
//             replace word1[i - 1] by word2[j - 1] : rec(i - 1 , j - 1) + 1
//             rec(i , j) = min(add , remove , replace).
//    step 5 : COST : 501 * 501 states, 3 moves. fine.
//    step 6 : bottom up, i from 0 to n, j from 0 to m.
//    step 7 : rolling rows. dp[i & 1] is row i, dp[(i + 1) & 1] is row i - 1
//             (i + 1 and i - 1 have the same parity). add reads dp[i & 1][j - 1],
//             already written this pass. answer dp[n & 1][m], not dp[0][m].
//
// 6. Why it works
//    in an optimal edit the last letter of word2 is either the untouched last letter
//    of word1 (equal case), or was added, or came from replacing word1's last letter,
//    or word1's last letter was removed. those cases cover every edit, and when the
//    last letters are equal keeping them is never worse. so the min is exact.
//    time O(n * m), extra space O(m).
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
// ll rec(ll i , ll j)
// {
//     // this returns the edit distance to make the first i characters of word1 equal to the first j characters of word2
//     if(i == 0)
//     {
//         return j ;
//     }
//     if(j == 0)
//     {
//         return i ;
//     }
//     if(dp[i][j] != -1)
//     {
//         return dp[i][j] ;
//     }
//     ll ans = 0 ;
//     if(word1[i - 1] == word2[j - 1])
//     {
//         ans = rec(i - 1 , j - 1) ;
//     }
//     else
//     {
//         ll add = rec(i , j - 1) + 1 ;
//         ll remove = rec(i - 1 , j) + 1 ;
//         ll replace = rec(i - 1 , j - 1) + 1 ;
//         ans = min({add , remove , replace}) ;
//     }
//     return dp[i][j] = ans ;
// }
class Solution {
public:
    int minDistance(string word1, string word2) {
        ll n = word1.size() ;
        ll m = word2.size() ;
        // step 7 : two rows of m + 1, dp[i & 1]
        vector < vector < ll > > dp(2 , vector < ll > (m + 1 , 0)) ;
        // step 6 : i from 0 to n, j from 0 to m
        for(ll i = 0 ; i <= n ; i++)
        {
            for(ll j = 0 ; j <= m ; j++)
            {
                // step 2 : one side empty
                if(i == 0)
                {
                    dp[i & 1][j] = j ;
                    continue ;
                }
                if(j == 0)
                {
                    dp[i & 1][j] = i ;
                    continue ;
                }
                // step 3 : equal last letters are free
                if(word1[i - 1] == word2[j - 1])
                {
                    dp[i & 1][j] = dp[(i + 1) & 1][j - 1] ;
                }
                // step 4 : add / remove / replace
                else
                {
                    ll add = dp[i & 1][j - 1] + 1 ;
                    ll remove = dp[(i + 1) & 1][j] + 1 ;
                    ll replace = dp[(i + 1) & 1][j - 1] + 1 ;
                    dp[i & 1][j] = min({add , remove , replace}) ;
                }
            }
        }
        return dp[n & 1][m] ;
    }
};
