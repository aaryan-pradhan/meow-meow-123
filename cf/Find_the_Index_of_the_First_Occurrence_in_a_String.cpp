// orz
// 28. Find the Index of the First Occurrence in a String · LeetCode · Easy
//
// Question:
// given two strings haystack and needle, return the index of the first occurrence
// of needle in haystack, or -1 if needle is not part of haystack.
// Example 1: haystack = "sadbutsad", needle = "sad"  -> 0  (at 0 and 6, the first is 0)
// Example 2: haystack = "leetcode", needle = "leeto" -> -1
// Constraints: 1 <= haystack.length, needle.length <= 10^4,
//              both have only lowercase English letters
//
// 1. Mathematical statement
//    n = |haystack|, m = |needle|. find the smallest i, 0 <= i <= n - m, with
//    haystack[i + j] == needle[j] for all j < m. if there is none, -1.
//
// 2. Brute force
//    try every start i and compare up to m chars.
//    O(n * m), 10^4 * 10^4 = 10^8 char compares in the worst case (haystack = "aaa..a",
//    needle = "aa..ab").
//
// 3. What the brute force wastes
//    after matching j chars and failing, it moves the start by one and compares
//    chars it has already seen. those j chars were needle[0 .. j - 1], so we already
//    know what they are.
//
// 4. Key breaking point
//    prefix function (KMP). glue t = needle + '#' + haystack ('#' is in neither string).
//    pi[i] = the length of the longest proper prefix of t[0 .. i] that is also a suffix of it.
//    the prefix of t is (part of) needle, and '#' stops it from ever going past m.
//    so pi[i] == m means : needle ends at position i of t.
//
// 5. Method
//    step 1 : t = needle + '#' + haystack, len = m + 1 + n, pi[0] = 0.
//    step 2 : for i = 1 .. len - 1 : k = pi[i - 1] (the border I am extending).
//             while k > 0 and t[i] != t[k], fall back k = pi[k - 1] (the next shorter border).
//             if t[i] == t[k], k++. pi[i] = k.
//    step 3 : the first i with pi[i] == m : needle ends at i of t, so it starts at
//             i - m + 1 in t, which is i - m + 1 - (m + 1) = i - 2 * m in haystack. return it.
//    step 4 : no such i : return -1.
//
// 6. Why it works
//    a border of t[0 .. i] that can be extended by t[i] is a border of t[0 .. i - 1]
//    followed by t[i], and the borders of t[0 .. i - 1] are exactly pi[i - 1],
//    pi[pi[i - 1] - 1], .. (each one is the longest border of the one before).
//    so step 2 tries every candidate, longest first. k grows by at most 1 per i and every
//    fall back makes it smaller, so the falls back cost at most len in total.
//    time O(n + m), extra space O(n + m).
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
    int strStr(string haystack, string needle) {
        ll m = needle.size() ;
        // step 1 : needle, a separator, then haystack
        string t = needle + '#' + haystack ;
        ll len = t.size() ;
        // pi[i] stores the longest proper prefix of t[0 .. i] that is also its suffix
        vector < ll > pi(len , 0) ;
        for(ll i = 1 ; i < len ; i++)
        {
            // step 2 : extend the border of t[0 .. i - 1]
            ll k = pi[i - 1] ;
            while(k > 0 && t[i] != t[k])
            {
                k = pi[k - 1] ;
            }
            if(t[i] == t[k])
            {
                k++ ;
            }
            pi[i] = k ;
            // step 3 : needle ends at i
            if(pi[i] == m)
            {
                return i - 2 * m ;
            }
        }
        // step 4
        return -1 ;
    }
};
