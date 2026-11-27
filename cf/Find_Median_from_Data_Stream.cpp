// orz
// 295. Find Median from Data Stream · LeetCode · Hard
//
// Question:
// the median is the middle value in an ordered integer list. if the size of the list
// is even, there is no single middle value, and the median is the mean of the two
// middle values. (for [2,3,4] the median is 3, for [2,3] it is (2 + 3) / 2 = 2.5.)
// implement the MedianFinder class:
//   MedianFinder() initialises the object.
//   void addNum(int num) adds the integer num from the data stream.
//   double findMedian() returns the median of all elements so far.
//   answers within 10^-5 of the actual answer are accepted.
// Example 1: ["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
//            [[],[1],[2],[],[3],[]]  -> [null,null,null,1.5,null,2.0]
// Constraints: -10^5 <= num <= 10^5, findMedian is called only when there is at least
//              one element, at most 5 * 10^4 calls to addNum and findMedian in total.
//
// 1. Mathematical statement
//    keep a multiset S under insertions. with c = S sorted and t = |S|, answer
//    c[(t - 1) / 2] when t is odd, (c[t / 2 - 1] + c[t / 2]) / 2 when t is even.
//
// 2. Brute force
//    keep a sorted vector, insert each number at its place (shift everything after it).
//    O(t) per add, 5 * 10^4 adds -> about 1.25 * 10^9 shifts. too slow.
//
// 3. What the brute force wastes
//    it keeps the whole list in order, but the median only needs the two values at the cut
//    in the middle: the biggest of the smaller half and the smallest of the bigger half.
//
// 4. Key breaking point
//    split the numbers into two halves:
//    lo = the smaller half in a max-heap (its top = the biggest small value),
//    hi = the bigger half in a min-heap  (its top = the smallest big value).
//    keep two rules: every value in lo <= every value in hi, and
//    lo.size() = hi.size() or lo.size() = hi.size() + 1.
//    then the median is read from the two tops.
//
// 5. Method
//    step 1 : members lo (max-heap) and hi (min-heap), both empty.
//    step 2 : addNum: push num into lo.
//    step 3 :         move lo's top into hi. lo's top is lo's biggest value, so after the move
//                     every value in lo is still <= every value in hi.
//    step 4 :         if hi now has more values than lo, move hi's top (its smallest) back into lo.
//                     this fixes the sizes and keeps the order rule.
//    step 5 : findMedian: lo bigger -> t is odd and the middle value is lo.top().
//             same size -> (lo.top() + hi.top()) / 2.0.
//
// 6. Why it works
//    after step 3: num went into the halves, and the order rule holds because only lo's biggest moved up.
//    sizes before addNum: (s , s) or (s + 1 , s). after step 2 and 3 they are (s , s + 1) or (s + 1 , s + 1),
//    step 4 turns (s , s + 1) into (s + 1 , s). so both rules hold after every addNum.
//    with the rules, lo is exactly the first ceil(t / 2) values of the sorted list, so its top and
//    hi's top are the middle values. time O(log t) per addNum, O(1) per findMedian, space O(t).
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
class MedianFinder {
public:
    // step 1
    priority_queue < ll > lo ;                                  // this stores the smaller half, biggest on top
    priority_queue < ll , vector < ll > , greater < ll > > hi ; // this stores the bigger half, smallest on top
    MedianFinder() {
    }

    void addNum(int num) {
        // step 2
        lo.push(num) ;
        // step 3
        hi.push(lo.top()) ;
        lo.pop() ;
        // step 4
        if(hi.size() > lo.size())
        {
            lo.push(hi.top()) ;
            hi.pop() ;
        }
    }

    double findMedian() {
        // step 5
        if(lo.size() > hi.size())
        {
            return lo.top() ;
        }
        else
        {
            return (lo.top() + hi.top()) / 2.0 ;
        }
    }
};
