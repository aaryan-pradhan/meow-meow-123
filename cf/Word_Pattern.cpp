// orz
// 290. Word Pattern · LeetCode · Easy
//
// Question:
// given a pattern and a string s, return true if s follows the same pattern.
// follow means a bijection between the letters of pattern and the non-empty
// words of s: each letter maps to exactly one word, each word maps to exactly
// one letter, no two letters map to the same word and no two words to the same letter.
// Example 1: pattern = "abba", s = "dog cat cat dog"    -> true
// Example 2: pattern = "abba", s = "dog cat cat fish"   -> false
// Example 3: pattern = "aaaa", s = "dog cat cat dog"    -> false
// Constraints: 1 <= pattern.length <= 300, pattern is lowercase English letters,
//              1 <= s.length <= 3000, s is lowercase English letters and ' ',
//              s has no leading or trailing spaces, words are split by a single space
//
// 1. Mathematical statement
//    split s into words w0 .. w(k - 1). need k == pattern.length and a one to one
//    map f from letters to words with f(pattern[i]) = wi for every i.
//
// 2. Brute force
//    split s, then for every pair i < j check: pattern[i] == pattern[j] exactly
//    when wi == wj. O(k^2) word compares. fine at k = 300, but it is the same
//    waste as 205.
//
// 3. What the brute force wastes
//    once letter c is tied to a word, every later c only has to match that one word.
//    comparing all pairs re-proves the same tie again and again.
//
// 4. Key breaking point
//    this is 205 Isomorphic Strings with words in place of t's characters.
//    lw[c] = the word letter c goes to, wl[word] = the letter that goes to the word.
//    both directions, because both must be one to one.
//
// 5. Method
//    step 1 : split s on ' ' into words.
//    step 2 : different counts of letters and words can never match, return false.
//    step 3 : walk i. c = pattern[i], w = words[i].
//             if both are new, tie them: lw[c] = w, wl[w] = c.
//             else if lw[c] != w or wl[w] != c, the map breaks, return false.
//             else they agree, move on.
//    step 4 : nothing broke, return true.
//
// 6. Why it works
//    same as 205: lw and wl stay inverse maps of each other, and a pair fails
//    exactly when a letter would need two words or a word two letters.
//    time O(|s| log k) (string compares in the map), extra space O(|s|).
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
    bool wordPattern(string pattern, string s) {
        ll n = s.size() ;
        // step 1 : split s into words
        vector < string > words ;
        string cur = "" ;
        for(ll i = 0 ; i < n ; i++)
        {
            if(s[i] == ' ')
            {
                words.push_back(cur) ;
                cur = "" ;
            }
            else
            {
                cur += s[i] ;
            }
        }
        words.push_back(cur) ;
        // step 2 : the counts must match
        ll k = pattern.size() ;
        if((ll)words.size() != k)
        {
            return false ;
        }
        // step 3 : lw[c] stores the word letter c goes to ("" = not tied yet)
        //          wl stores, for every tied word, the letter that goes to it
        vector < string > lw(26 , "") ;
        map < string , char > wl ;
        for(ll i = 0 ; i < k ; i++)
        {
            ll c = pattern[i] - 'a' ;
            string w = words[i] ;
            if(lw[c] == "" && wl.find(w) == wl.end())
            {
                lw[c] = w ;
                wl[w] = pattern[i] ;
            }
            else if(lw[c] != w || wl[w] != pattern[i])
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
