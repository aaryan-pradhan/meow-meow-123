// orz
// 392. Is Subsequence · LeetCode · Easy
//
// Question:
// given two strings s and t, return true if s is a subsequence of t.
// a subsequence is made by deleting some (maybe none) characters of t
// without changing the order of the ones that are left.
// Example 1: s = "abc", t = "ahbgdc" -> true
// Example 2: s = "axc", t = "ahbgdc" -> false
// Constraints: 0 <= s.length <= 100, 0 <= t.length <= 10^4, lowercase English letters only
//
// 1. Mathematical statement
//    m = s.length, n = t.length. true iff there are indices
//    0 <= j0 < j1 < .. < j(m - 1) < n with t[jk] == s[k] for every k.
//
// 2. Brute force
//    try every way to pick m positions of t, check if they spell s.
//    C(n, m) choices, n = 10^4 and m = 100 is astronomic. dead.
//
// 3. What the brute force wastes
//    it tries late positions for s[0] when an earlier one was available.
//    an earlier match never hurts: it leaves more of t for the rest of s.
//
// 4. Key breaking point
//    greedy: match every s[i] at the FIRST free position of t that equals it.
//    that is two pointers walking in parallel, i on s and j on t (like Apartments).
//
// 5. Method
//    step 1 : i = 0 on s, j = 0 on t.
//    step 2 : while i < m and j < n : if s[i] == t[j], s[i] is matched, i++.
//             either way t[j] is used up, j++.
//    step 3 : return true iff i == m (every character of s got matched).
//
// 6. Why it works
//    exchange: take any valid matching j0 < j1 < .. . the greedy g0 is the first
//    position with t[g0] == s[0], so g0 <= j0. replace j0 by g0, still increasing.
//    repeat for s[1] after g0, and so on: if any matching exists the greedy finds one.
//    and if the greedy finds one, it is a matching. so they agree.
//    time O(n + m), extra space O(1).
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
    bool isSubsequence(string s, string t) {
        ll m = s.size() ;
        ll n = t.size() ;
        // step 1
        ll i = 0 , j = 0 ;
        // step 2 : match s[i] at the first equal t[j]
        while(i < m && j < n)
        {
            if(s[i] == t[j])
            {
                i++ ;
            }
            j++ ;
        }
        // step 3
        if(i == m)
        {
            return true ;
        }
        else
        {
            return false ;
        }
    }
};
