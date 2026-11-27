// orz
// 380. Insert Delete GetRandom O(1) · LeetCode · Medium
//
// Question:
// implement the class RandomizedSet:
//   RandomizedSet()      initialises an empty set.
//   bool insert(int val) inserts val if it is not present. returns true if it was not present.
//   bool remove(int val) removes val if it is present. returns true if it was present.
//   int getRandom()      returns a random element of the set, each element with the same probability.
// every function must work in average O(1) time.
// Example 1: ["RandomizedSet","insert","remove","insert","getRandom","remove","insert","getRandom"]
//            [[],[1],[2],[2],[],[1],[2],[]]
//            -> [null,true,false,true,1 or 2,true,false,2]
// Constraints: -2^31 <= val <= 2^31 - 1, at most 2 * 10^5 calls in total,
//              getRandom is only called when the set has at least one element.
//
// 1. Mathematical statement
//    keep a set S under insert / remove, and sample a uniform element of S, each in O(1).
//
// 2. Brute force
//    a vector alone: insert and remove need a search for val, O(n) each.
//    a hash set alone: insert / remove are O(1), but it has no index, so a uniform
//    random element needs a walk of O(n) steps.
//
// 3. What the brute force wastes
//    the vector has O(1) random access but slow search, the hash set has O(1) search
//    but no random access. each one has exactly what the other one lacks.
//
// 4. Key breaking point
//    keep both: v = the values in any order (random access), pos[x] = index of x in v
//    (O(1) search). the order inside v doesn't matter, so removing from the middle is
//    "move the last element into the hole, then pop_back", O(1) instead of a shift.
//    (unordered_map, not map: map is O(log n) and the problem asks for O(1).)
//
// 5. Method
//    step 1 : insert(val) : if val is in pos, return false.
//             else pos[val] = v.size(), push val to the back of v, return true.
//    step 2 : remove(val) : if val is not in pos, return false.
//             else idx = pos[val], last = v.back().
//             move last into the hole: v[idx] = last, pos[last] = idx.
//             then v.pop_back(), erase val from pos, return true.
//             (val == last also works: pos[last] = idx is written, then erased.)
//    step 3 : getRandom() : return v[rand() % v.size()].
//
// 6. Why it works
//    invariant: v holds every element of S exactly once and pos[x] is the index of x in v.
//    insert and remove both keep it, so step 3 picks each element of S with
//    probability 1 / |S|.
//    time average O(1) per call (hash map), space O(n).
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
class RandomizedSet {
    vector < int > v ;               // this stores the elements, in any order
    unordered_map < int , ll > pos ; // pos[x] = index of x in v
public:
    RandomizedSet() {
    }

    bool insert(int val) {
        // step 1 : already there
        if(pos.find(val) != pos.end())
        {
            return false ;
        }
        else
        {
            pos[val] = v.size() ;
            v.push_back(val) ;
            return true ;
        }
    }

    bool remove(int val) {
        // step 2 : not there
        if(pos.find(val) == pos.end())
        {
            return false ;
        }
        else
        {
            ll idx = pos[val] ;
            int last = v.back() ;
            // move the last element into the hole
            v[idx] = last ;
            pos[last] = idx ;
            v.pop_back() ;
            pos.erase(val) ;
            return true ;
        }
    }

    int getRandom() {
        // step 3 : uniform index into v
        ll idx = rand() % v.size() ;
        return v[idx] ;
    }
};
