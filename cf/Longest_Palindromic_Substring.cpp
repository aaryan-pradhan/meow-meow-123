// orz
// 5. Longest Palindromic Substring · LeetCode · Medium
//
// Question:
// given a string s, return the longest palindromic substring in s.
// (a palindrome reads the same forward and backward. any longest one is accepted.)
// Example 1: s = "babad" -> "bab"  ("aba" is also accepted)
// Example 2: s = "cbbd"  -> "bb"
// Constraints: 1 <= s.length <= 1000, s consists of only digits and English letters
//
// 1. Mathematical statement
//    find l <= r maximising r - l + 1 such that s[l + k] == s[r - k] for every k
//    with l + k <= r - k. return s[l .. r].
//
// 2. Brute force
//    every pair (l , r), check it with two pointers walking inwards.
//    n^2 / 2 pairs * n per check = O(n^3), about 1.7 * 10^8 at n = 1000. too slow / borderline.
//
// 3. What the brute force wastes
//    checking s[l .. r] walks s[l + 1 .. r - 1] again, which the pair (l + 1 , r - 1)
//    already checked. the same inner segments are re-walked for every outer pair.
//
// 4. Key breaking point
//    s[l .. r] is a palindrome iff s[l] == s[r] and s[l + 1 .. r - 1] is one.
//    the state is the segment: LR form rec(l , r). row l reads only row l + 1,
//    so two rows are enough.
//
// 5. Method
//    step 1 : FORM = LR. rec(l , r) = true if s[l .. r] is a palindrome.
//    step 2 : CHECK : l >= r -> true (one letter, or the empty middle of an even length
//             like "bb" asking about (l + 1 , l)).
//    step 3 : MOVE : rec(l , r) = (s[l] == s[r]) and rec(l + 1 , r - 1).
//    step 4 : COST : n^2 = 10^6 states, O(1) each. fine.
//    step 5 : bottom up, l from n - 1 down to 0 (rec(l , ..) needs row l + 1),
//             r from 0 to n - 1.
//    step 6 : rolling rows. dp[l & 1] is row l, dp[(l + 1) & 1] is row l + 1.
//    step 7 : every true (l , r) is a candidate: keep the longest, start = l, len = r - l + 1.
//    step 8 : return s.substr(start , len).
//
// 6. Why it works
//    step 3 is the definition of a palindrome peeled from the outside: first letter
//    equals last letter, and the middle reads the same both ways. every segment is
//    checked exactly once, so the longest true one is found. n >= 1 so len >= 1.
//    time O(n^2), extra space O(n).
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
// bool rec(ll l , ll r)
// {
//     // this returns true if s[l .. r] is a palindrome
//     if(l >= r)
//     {
//         return true ;
//     }
//     if(dp[l][r] != -1)
//     {
//         return dp[l][r] ;
//     }
//     bool same = (s[l] == s[r]) ;
//     bool inside = rec(l + 1 , r - 1) ;
//     return dp[l][r] = (same && inside) ;
// }
class Solution {
public:
    string longestPalindrome(string s) {
        ll n = s.size() ;
        // step 6 : two rows, dp[l & 1]
        vector < vector < ll > > dp(2 , vector < ll > (n , 0)) ;
        ll start = 0 , len = 1 ;
        // step 5 : l from n - 1 down to 0
        for(ll l = n - 1 ; l >= 0 ; l--)
        {
            for(ll r = 0 ; r < n ; r++)
            {
                // step 2 : one letter or empty
                if(l >= r)
                {
                    dp[l & 1][r] = 1 ;
                    continue ;
                }
                // step 3 : ends equal and the middle is a palindrome
                bool same = (s[l] == s[r]) ;
                bool inside = dp[(l + 1) & 1][r - 1] ;
                if(same && inside)
                {
                    dp[l & 1][r] = 1 ;
                }
                else
                {
                    dp[l & 1][r] = 0 ;
                    continue ;
                }
                // step 7 : longest so far
                if(r - l + 1 > len)
                {
                    start = l ;
                    len = r - l + 1 ;
                }
            }
        }
        // step 8
        return s.substr(start , len) ;
    }
};
