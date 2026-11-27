// orz
// 383. Ransom Note · LeetCode · Easy
//
// Question:
// given two strings ransomNote and magazine, return true if ransomNote can be
// built from the letters of magazine, and false otherwise. each letter of
// magazine can be used only once in ransomNote.
// Example 1: ransomNote = "a", magazine = "b"     -> false
// Example 2: ransomNote = "aa", magazine = "ab"   -> false
// Example 3: ransomNote = "aa", magazine = "aab"  -> true
// Constraints: 1 <= ransomNote.length, magazine.length <= 10^5,
//              both are lowercase English letters only
//
// 1. Mathematical statement
//    for every letter c: (number of c in ransomNote) <= (number of c in magazine).
//
// 2. Brute force
//    for every letter of ransomNote, scan magazine for a copy that is not used yet
//    and mark it used. if some letter finds no copy, false.
//    O(n * m), 10^5 * 10^5 = 10^10. dead.
//
// 3. What the brute force wastes
//    it searches for positions, but the positions never matter. two copies of 'a'
//    in magazine are the same 'a'. only how many of each letter there are matters.
//
// 4. Key breaking point
//    a letter is just a count. 26 counters, one per letter, replace the search:
//    count the magazine, then spend the counts on the note.
//
// 5. Method
//    step 1 : cnt[c] = how many times letter c is in magazine.
//    step 2 : walk the note. for each letter c, spend one: cnt[c]--.
//             if cnt[c] goes below 0, the magazine ran out of c, return false.
//    step 3 : every letter got paid for, return true.
//
// 6. Why it works
//    after step 2, cnt[c] = (c in magazine) - (c in note so far). it goes below 0
//    exactly when the note needs more c than the magazine has, which is the
//    statement in 1 failing.
//    time O(n + m), extra space O(26).
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
    bool canConstruct(string ransomNote, string magazine) {
        ll n = ransomNote.size() ;
        ll m = magazine.size() ;
        // step 1 : cnt[c] stores how many times letter c is in the magazine
        vector < ll > cnt(26 , 0) ;
        for(ll i = 0 ; i < m ; i++)
        {
            cnt[magazine[i] - 'a']++ ;
        }
        // step 2 : spend one copy for every letter of the note
        for(ll i = 0 ; i < n ; i++)
        {
            cnt[ransomNote[i] - 'a']-- ;
            if(cnt[ransomNote[i] - 'a'] < 0)
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
