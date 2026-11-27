// orz
// 242. Valid Anagram · LeetCode · Easy
//
// Question:
// given two strings s and t, return true if t is an anagram of s (the same
// letters, each used the same number of times, in any order), and false otherwise.
// Example 1: s = "anagram", t = "nagaram"   -> true
// Example 2: s = "rat", t = "car"           -> false
// Constraints: 1 <= s.length, t.length <= 5 * 10^4, s and t are lowercase English letters
//
// 1. Mathematical statement
//    for every letter c: (number of c in s) == (number of c in t).
//
// 2. Brute force
//    for every letter of s, scan t for an unused equal letter and mark it used.
//    at the end, t must have nothing left over.
//    O(n^2), n = 5 * 10^4 gives 2.5 * 10^9. too slow.
//
// 3. What the brute force wastes
//    it looks for positions, but positions don't matter in an anagram.
//    only the count of each letter matters.
//
// 4. Key breaking point
//    same as 383 Ransom Note: a letter is just a count. one counter per letter,
//    +1 for s, -1 for t. anagram iff every counter ends at 0.
//
// 5. Method
//    step 1 : different lengths can never be anagrams, return false.
//    step 2 : cnt[c]++ for every letter of s, cnt[c]-- for every letter of t.
//    step 3 : if some cnt[c] != 0, one string has more c, return false.
//    step 4 : return true.
//
// 6. Why it works
//    after step 2, cnt[c] = (c in s) - (c in t). all 26 are 0 exactly when
//    the statement in 1 holds.
//    time O(n), extra space O(26).
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
    bool isAnagram(string s, string t) {
        ll n = s.size() ;
        ll m = t.size() ;
        // step 1 : lengths must match
        if(n != m)
        {
            return false ;
        }
        // step 2 : cnt[c] stores (c in s) - (c in t)
        vector < ll > cnt(26 , 0) ;
        for(ll i = 0 ; i < n ; i++)
        {
            cnt[s[i] - 'a']++ ;
            cnt[t[i] - 'a']-- ;
        }
        // step 3 : every letter must balance
        for(ll c = 0 ; c < 26 ; c++)
        {
            if(cnt[c] != 0)
            {
                return false ;
            }
            else
            {
                continue ;
            }
        }
        // step 4
        return true ;
    }
};
