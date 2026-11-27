// orz
// 76. Minimum Window Substring · LeetCode · Hard
//
// Question:
// given strings s (length n) and t (length m), return the shortest substring of s
// that contains every character of t, duplicates included. if there is none, return "".
// the answer is unique when it exists.
// Example 1: s = "ADOBECODEBANC", t = "ABC" -> "BANC"
// Example 2: s = "a", t = "a"               -> "a"
// Example 3: s = "a", t = "aa"              -> ""   (t needs two 'a', s has one)
// Constraints: 1 <= n, m <= 10^5, s and t are uppercase and lowercase English letters
// Follow up: an O(n + m) algorithm. -> done here.
//
// 1. Mathematical statement
//    need[c] = count of c in t, have[c] = count of c in s[l .. r].
//    minimise r - l + 1 over all l <= r with have[c] >= need[c] for every c.
//
// 2. Brute force
//    every l, every r >= l, compare the counts. O(n^2 * 52), n = 10^5. dead.
//
// 3. What the brute force wastes
//    if s[l .. r] covers t, every longer window covers it too, so for a fixed l only the
//    first r that covers matters. and when l moves right the window loses a character,
//    so that first r can only move right. the brute force restarts r from l.
//
// 4. Key breaking point
//    "covers t" is monotone: my sliding window, push the head while the window does not
//    cover t yet. comparing 52 counts every step is too slow, so keep one number:
//    missing = how many characters of t (with duplicates) the window still lacks.
//    adding c helps only if have[c] <= need[c] after adding. removing c hurts only if
//    have[c] <= need[c] before removing. covers t <=> missing == 0.
//    (t is the name of the input string, so here the window ends are called tail and head.)
//
// 5. Method
//    step 1 : need[c] from t, have[c] = 0, missing = m.
//    step 2 : tail = 0, head = -1 (empty window), best = n + 1 (means "none yet"), start = 0.
//    step 3 : while head + 1 < n and missing > 0 : head++, c = s[head], have[c]++,
//             if have[c] <= need[c] then missing--.
//    step 4 : if missing == 0, [tail, head] is the shortest cover starting at tail,
//             if it is shorter than best, best = head - tail + 1, start = tail.
//    step 5 : remove c = s[tail] : if have[c] <= need[c] then missing++. have[c]--, tail++.
//             (empty window: tail++, head = tail - 1.)
//    step 6 : best still n + 1 -> "". else s.substr(start, best).
//
// 6. Why it works
//    missing == number of characters of t not yet matched, kept exact by steps 3 and 5,
//    so missing == 0 is exactly "the window covers t". for every tail, head stops at the
//    first cover (or at n - 1). that first cover never moves left as tail grows (monotone),
//    so no window is skipped, and best is the shortest over every tail.
//    tail and head each move at most n times: time O(n + m), extra space O(128).
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
    string minWindow(string s, string t) {
        ll n = s.size() ;
        ll m = t.size() ;
        // step 1 : counts of t
        vector < ll > need(128 , 0) ; // this stores how many times each character is in t
        vector < ll > have(128 , 0) ; // this stores how many times each character is in the window
        for(ll i = 0 ; i < m ; i++)
        {
            need[t[i]]++ ;
        }
        ll missing = m ; // this stores how many characters of t the window still lacks
        // step 2 : t is taken by the input string, so the window is tail / head
        ll tail = 0 , head = -1 , best = n + 1 , start = 0 ;
        while(tail < n)
        {
            // step 3 : grow while the window does not cover t
            while(head + 1 < n && missing > 0)
            {
                head++ ;
                char c = s[head] ;
                have[c]++ ;
                if(have[c] <= need[c])
                {
                    missing-- ;
                }
            }
            // step 4 : shortest cover starting at tail
            if(missing == 0 && head - tail + 1 < best)
            {
                best = head - tail + 1 ;
                start = tail ;
            }
            // step 5 : drop s[tail]
            if(tail > head)
            {
                tail++ ;
                head = tail - 1 ;
            }
            else
            {
                char c = s[tail] ;
                if(have[c] <= need[c])
                {
                    missing++ ;
                }
                have[c]-- ;
                tail++ ;
            }
        }
        // step 6
        if(best == n + 1)
        {
            return "" ;
        }
        else
        {
            return s.substr(start , best) ;
        }
    }
};
