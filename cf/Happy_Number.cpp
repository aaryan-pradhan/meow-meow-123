// orz
// 202. Happy Number · LeetCode · Easy
//
// Question:
// a happy number: start with n, replace it by the sum of the squares of its
// digits, and repeat. if this reaches 1, n is happy. otherwise it loops forever
// in a cycle that does not contain 1. return true if n is happy.
// Example 1: n = 19 -> true   (1 + 81 = 82, 64 + 4 = 68, 36 + 64 = 100, 1 + 0 + 0 = 1)
// Example 2: n = 2  -> false
// Constraints: 1 <= n <= 2^31 - 1
//
// 1. Mathematical statement
//    f(x) = sum of (digit of x)^2. the sequence x0 = n, x(k + 1) = f(xk).
//    is there a k with xk = 1?
//
// 2. Brute force
//    apply f a fixed big number of times (say 10^6) and see if 1 ever shows up.
//    works, but "big enough" is a guess, not a proof.
//
// 3. What the brute force wastes
//    the moment a value repeats, the sequence is stuck in a cycle forever.
//    every step after the first repeat is wasted, and the guess hides that.
//
// 4. Key breaking point
//    the values are small after one step: n < 10^10 has at most 10 digits, so
//    f(n) <= 10 * 81 = 810. so the sequence lives in 1 .. 810 from x1 on, and must
//    repeat within ~812 steps. keep a set of seen values: a repeat = a cycle.
//
// 5. Method
//    step 1 : nxt(x) returns the sum of the squares of the digits of x.
//    step 2 : walk x = n while x != 1. if x is already in seen, it is a cycle
//             without 1 (1 would have stopped the walk), return false.
//             else put x in seen and move x = nxt(x).
//    step 3 : the walk reached 1, return true.
//
// 6. Why it works
//    f is a function, so once some x repeats, everything after it repeats too.
//    the walk either hits 1 or hits a repeat, and by 4 a repeat comes in at most
//    ~812 steps. a repeat before 1 means 1 is never reached.
//    time O(812 * 10), extra space O(812).
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
ll nxt(ll x)
{
    // step 1 : this returns the sum of the squares of the digits of x
    ll sum = 0 ;
    while(x > 0)
    {
        ll d = x % 10 ;
        sum += d * d ;
        x /= 10 ;
    }
    return sum ;
}
class Solution {
public:
    bool isHappy(int n) {
        // step 2 : walk until 1 or until a value repeats
        set < ll > seen ;
        ll x = n ;
        while(x != 1)
        {
            if(seen.find(x) != seen.end())
            {
                return false ;
            }
            else
            {
                seen.insert(x) ;
                x = nxt(x) ;
            }
        }
        // step 3
        return true ;
    }
};
