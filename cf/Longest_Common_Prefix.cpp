// orz
// 14. Longest Common Prefix · LeetCode · Easy
//
// Question:
// given an array of strings strs, return the longest string that is a prefix of
// all of them. if there is none, return "".
// Example 1: strs = ["flower","flow","flight"]  -> "fl"
// Example 2: strs = ["dog","racecar","car"]     -> ""
// Constraints: 1 <= strs.length <= 200, 0 <= strs[i].length <= 200,
//              strs[i] has only lowercase English letters
//
// 1. Mathematical statement
//    find the largest L such that for every string w in strs, |w| >= L and
//    w[j] == strs[0][j] for all j < L. return strs[0][0 .. L - 1].
//
// 2. Brute force
//    for L = |strs[0]| down to 0, check whether every string starts with strs[0][0 .. L - 1],
//    return the first L that works. each check costs n * L : O(n * m^2) with m = 200.
//
// 3. What the brute force wastes
//    the check for L and for L - 1 compare the same first L - 1 columns again.
//
// 4. Key breaking point
//    the condition is column by column : column j is good if every string has a
//    j-th char equal to strs[0][j]. the answer is the first bad column.
//    so scan columns j = 0, 1, 2 .. and stop at the first bad one.
//
// 5. Method
//    step 1 : for j = 0, 1, .. up to |strs[0]| - 1, ch = strs[0][j].
//    step 2 : for every string w, if |w| <= j or w[j] != ch, column j is bad : return the
//             prefix strs[0][0 .. j - 1].
//    step 3 : the column is good, append ch to the answer and go to j + 1.
//    step 4 : strs[0] ran out with every column good : the answer is all of strs[0].
//
// 6. Why it works
//    the prefix of length L is common iff columns 0 .. L - 1 are all good, so the first
//    bad column is exactly the answer length. each char is compared at most once.
//    time O(total chars), extra space O(1) besides the answer.
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
    string longestCommonPrefix(vector<string>& strs) {
        ll n = strs.size() ;
        ll m = strs[0].size() ;
        string ans = "" ;
        // step 1 : column j
        for(ll j = 0 ; j < m ; j++)
        {
            char ch = strs[0][j] ;
            // step 2 : every string must have ch at column j
            for(ll k = 0 ; k < n ; k++)
            {
                ll len = strs[k].size() ;
                if(len <= j || strs[k][j] != ch)
                {
                    return ans ;
                }
                else
                {
                    continue ;
                }
            }
            // step 3 : column j is good
            ans += ch ;
        }
        // step 4
        return ans ;
    }
};
