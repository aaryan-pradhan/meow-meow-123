// orz
// 205. Isomorphic Strings · LeetCode · Easy
//
// Question:
// given two strings s and t, return true if they are isomorphic.
// s and t are isomorphic if the characters of s can be replaced to get t:
// every occurrence of a character is replaced by the same character, the order
// stays, no two different characters may map to the same character, and a
// character may map to itself.
// Example 1: s = "egg", t = "add"       -> true
// Example 2: s = "foo", t = "bar"       -> false
// Example 3: s = "paper", t = "title"   -> true
// Constraints: 1 <= s.length <= 5 * 10^4, t.length == s.length,
//              s and t consist of any valid ascii character
//
// 1. Mathematical statement
//    there is a one to one map f on characters with f(s[i]) = t[i] for every i.
//    f must be a function (same s char -> same t char) and one to one
//    (different s chars -> different t chars).
//
// 2. Brute force
//    for every pair i < j check: s[i] == s[j] exactly when t[i] == t[j].
//    O(n^2), n = 5 * 10^4 gives about 1.25 * 10^9 pairs. too slow.
//
// 3. What the brute force wastes
//    position i only needs to agree with ONE earlier position that has the same
//    character. once s[i] -> t[i] is decided, every later copy of s[i] just has
//    to match it. checking all pairs re-proves the same thing again and again.
//
// 4. Key breaking point
//    store the map itself. st[a] = the t char that s char a goes to,
//    ts[b] = the s char that goes to t char b. two tables because both
//    directions must be one to one ("foo" -> "bar" breaks st, "ab" -> "aa" breaks ts).
//
// 5. Method
//    step 1 : st(256 , -1), ts(256 , -1). -1 means not decided yet.
//    step 2 : walk i. a = s[i], b = t[i].
//             if both are new, decide st[a] = b and ts[b] = a.
//             else if st[a] != b or ts[b] != a, the map breaks, return false.
//             else the pair agrees with what was decided, move on.
//    step 3 : no pair broke the map, return true.
//
// 6. Why it works
//    step 2 keeps st and ts as inverse maps of each other on the chars seen so far.
//    a pair (a , b) fits iff a and b are both new, or a already goes to b
//    (then b already comes from a). anything else means a needs two images or
//    b needs two sources, which is exactly the statement in 1 failing.
//    time O(n), extra space O(256).
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
    bool isIsomorphic(string s, string t) {
        ll n = s.size() ;
        // step 1 : st[a] stores where s char a goes, ts[b] stores which s char comes to b
        vector < ll > st(256 , -1) ;
        vector < ll > ts(256 , -1) ;
        // step 2 : check every pair (s[i] , t[i])
        for(ll i = 0 ; i < n ; i++)
        {
            ll a = (unsigned char)s[i] ;
            ll b = (unsigned char)t[i] ;
            if(st[a] == -1 && ts[b] == -1)
            {
                st[a] = b ;
                ts[b] = a ;
            }
            else if(st[a] != b || ts[b] != a)
            {
                return false ;
            }
            else
            {
                continue ;
            }
        }
        // step 3
        return true ;
    }
};
