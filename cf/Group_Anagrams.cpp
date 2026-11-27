// orz
// 49. Group Anagrams · LeetCode · Medium
//
// Question:
// given an array of strings strs, group the anagrams together (strings with the
// same letters, each used the same number of times). return the groups in any order.
// Example 1: strs = ["eat","tea","tan","ate","nat","bat"]
//            -> [["bat"],["nat","tan"],["ate","eat","tea"]]
// Example 2: strs = [""]    -> [[""]]
// Example 3: strs = ["a"]   -> [["a"]]
// Constraints: 1 <= strs.length <= 10^4, 0 <= strs[i].length <= 100,
//              strs[i] is lowercase English letters
//
// 1. Mathematical statement
//    a ~ b iff a is an anagram of b. this is an equivalence relation.
//    output its classes.
//
// 2. Brute force
//    for every string, compare it with the first string of every group so far
//    (242 Valid Anagram, O(L)). join the first group that matches, else open a new one.
//    O(n^2 * L) = 10^8 * 100. dead.
//
// 3. What the brute force wastes
//    it compares a string against every group to find its class, when the class
//    could be read off the string alone.
//
// 4. Key breaking point
//    give every class a name that each member can compute alone: the sorted string.
//    "eat", "tea", "ate" all sort to "aet". a ~ b iff sorted(a) == sorted(b).
//    then a map from name to group index finds the group in one lookup.
//
// 5. Method
//    step 1 : for every string w, key = w sorted.
//    step 2 : if key is new, id[key] = groups.size(), open an empty group.
//    step 3 : push w into groups[id[key]].
//    step 4 : return groups.
//
// 6. Why it works
//    two strings are anagrams exactly when they have the same letter counts,
//    and the sorted string is those counts written out in order. so equal keys
//    = same class, and every class gets exactly one group.
//    time O(n * L log L + n * L log n) for the sorts and the map, extra space O(n * L).
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
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        ll n = strs.size() ;
        vector < vector < string > > groups ;
        // this stores, for every key, the index of its group in groups
        map < string , ll > id ;
        for(ll i = 0 ; i < n ; i++)
        {
            // step 1 : the name of the class
            string key = strs[i] ;
            sort(key.begin() , key.end()) ;
            // step 2 : open a new group for a new key
            if(id.find(key) == id.end())
            {
                id[key] = groups.size() ;
                groups.push_back(vector < string > ()) ;
            }
            // step 3
            groups[id[key]].push_back(strs[i]) ;
        }
        // step 4
        return groups ;
    }
};
