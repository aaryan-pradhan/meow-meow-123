// orz
// 134. Gas Station · LeetCode · Medium
//
// Question:
// there are n gas stations on a circular route. station i has gas[i] gas, and
// driving from station i to station i + 1 (station n - 1 goes back to 0) costs
// cost[i] gas. the car has an unlimited tank and starts empty at one station.
// return the index of the station where you can start and drive once around the
// circuit clockwise, or -1 if no start works. if an answer exists it is unique.
// Example 1: gas = [1,2,3,4,5], cost = [3,4,5,1,2] -> 3
//            (start at 3: tank 4, 8, 7, 6, 5, back at 3 with 5 >= 0 all the way)
// Example 2: gas = [2,3,4], cost = [3,4,3]           -> -1
// Constraints: n == gas.length == cost.length, 1 <= n <= 10^5,
//              0 <= gas[i], cost[i] <= 10^4
//
// 1. Mathematical statement
//    let d[k] = gas[k] - cost[k]. find a start s such that for every t = 0 .. n - 1
//    d[s] + d[(s + 1) % n] + .. + d[(s + t) % n] >= 0. if there is none, -1.
//
// 2. Brute force
//    for every start s, drive around and check the tank never goes below 0.
//    n starts, n stations each, O(n^2), n = 10^5 gives 10^10. dead.
//
// 3. What the brute force wastes
//    a start i that dies at step T already walked the stations i + 1 .. i + T,
//    and the brute force then starts from i + 1 and walks the same road again.
//
// 4. Key breaking point
//    say the start i first goes below 0 at step T, at station k = i + T.
//    for every j between i + 1 and k, the car coming from i arrived at j with
//    tank >= 0 (it only died at k). starting fresh at j means arriving with 0,
//    which is no better, so the start j also dies at k or before.
//    so a failed run kills every start inside it: jump straight to k + 1.
//
// 5. Method
//    step 1 : test(i) drives from i. at step t it is at station (i + t) % n and adds
//             gas - cost of that station. it returns the first t where the tank is
//             below 0, or n when the car makes it all the way around.
//    step 2 : i = 0. while i < n : T = test(i).
//             if T == n, i is the answer.
//             else every start i .. i + T dies, so i = i + T + 1.
//    step 3 : i ran past n - 1, so every start died : return -1.
//
// 6. Why it works
//    step 4 shows the skipped starts all die, and the starts before i died earlier,
//    so when test(i) == n, i is the only possible answer (it is unique, given).
//    the failed tests walk disjoint stretches of stations (i jumps past each one),
//    so they cost n in total, and the one successful test costs n more.
//    time O(n), extra space O(1).
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
ll test(ll i , vector<int>& gas , vector<int>& cost)
{
    // this returns the first step t where the tank goes below 0 starting at station i,
    // or n if the car goes all the way around
    ll n = gas.size() ;
    ll tank = 0 ;
    for(ll t = 0 ; t < n ; t++)
    {
        ll k = (i + t) % n ;
        tank += gas[k] - cost[k] ;
        if(tank < 0)
        {
            return t ;
        }
    }
    return n ;
}
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        ll n = gas.size() ;
        // step 2 : test i, jump past the whole stretch it died on
        ll i = 0 ;
        while(i < n)
        {
            // step 1
            ll T = test(i , gas , cost) ;
            if(T == n)
            {
                return i ;
            }
            else
            {
                i = i + T + 1 ;
            }
        }
        // step 3 : every start died
        return -1 ;
    }
};
