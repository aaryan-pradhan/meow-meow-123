// orz
// 502. IPO · LeetCode · Hard
//
// Question:
// a company wants to finish at most k distinct projects before its IPO. there are n
// projects; project i has a pure profit profits[i] and needs at least capital[i]
// capital to start. you start with w capital. finishing a project adds its pure
// profit to your capital. pick at most k distinct projects to maximise your final
// capital, and return that final maximised capital. the answer fits in a 32-bit
// signed integer.
// Example 1: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1] -> 4
//            (start project 0 with w = 0, now w = 1, then project 2, w = 1 + 3 = 4)
// Example 2: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2] -> 6
// Constraints: 1 <= k <= 10^5, 0 <= w <= 10^9, 1 <= n <= 10^5,
//              0 <= profits[i] <= 10^4, 0 <= capital[i] <= 10^9
//
// 1. Mathematical statement
//    choose an order p1, p2, .., pr of distinct projects, r <= k, such that
//    capital[p(s)] <= w + profits[p1] + .. + profits[p(s - 1)] for every s.
//    maximise w + profits[p1] + .. + profits[pr].
//
// 2. Brute force
//    every round, scan all projects, take the most profitable one I can afford and haven't done.
//    O(n * k) = 10^10. dead. (trying all orders is even worse.)
//
// 3. What the brute force wastes
//    profits are >= 0, so w never goes down. a project I can afford now stays affordable
//    forever, yet every round re-checks all of them from scratch.
//
// 4. Key breaking point
//    greedy: each round take the most profitable affordable project (exchange argument in 6.).
//    sort projects by capital. as w grows, walk a pointer p and push every newly affordable
//    project's profit into a max-heap, each project exactly once. the top of the heap is the
//    best affordable project. sorted list + pointer + heap.
//
// 5. Method
//    step 1 : v = pairs (capital[i] , profits[i]), sorted by capital.
//    step 2 : pq = max-heap of profits of projects that are affordable and not done. p = 0.
//    step 3 : repeat k times:
//             while p < n and v[p].capital <= w : push v[p].profit, p++.
//    step 4 :     if pq is empty, nothing is affordable and w can't grow any more: stop.
//                 else w += pq.top(), pop it.
//    step 5 : return w.
//
// 6. Why it works
//    exchange argument: say an optimal plan does some project x first, and g is the most
//    profitable affordable one. if the plan uses g later, swap x and g: g first is affordable,
//    and after it w is at least as big as after x, so everything later stays affordable.
//    if the plan never uses g, do g instead of x: same reason, and the final w is not smaller.
//    so taking g first is never worse; repeat the argument for the rest of the rounds.
//    time O(n log n + k log n), extra space O(n).
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
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        ll n = profits.size() ;
        ll cur = w ;
        // step 1 : (capital , profit), sorted by capital
        vector < pll > v(n) ;
        for(ll i = 0 ; i < n ; i++)
        {
            v[i].fr = capital[i] ;
            v[i].sc = profits[i] ;
        }
        sort(v.begin() , v.end() , [](pll a , pll b)
        {
            return a.fr < b.fr ;
        }) ;
        // step 2 : this stores the profits of the affordable projects not done yet, biggest on top
        priority_queue < ll > pq ;
        ll p = 0 ;
        for(ll round = 0 ; round < k ; round++)
        {
            // step 3 : push every project that just became affordable
            while(p < n && v[p].fr <= cur)
            {
                pq.push(v[p].sc) ;
                p++ ;
            }
            // step 4
            if(pq.empty())
            {
                break ;
            }
            else
            {
                cur += pq.top() ;
                pq.pop() ;
            }
        }
        // step 5
        return cur ;
    }
};
