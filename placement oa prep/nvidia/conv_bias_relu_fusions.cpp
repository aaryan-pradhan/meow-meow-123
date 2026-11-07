/*
Conv -> Bias -> ReLU fusions (source: NVIDIA OA)

An inference compiler speeds up a neural network by fusing three operators that
run back to back, Conv -> Bias -> ReLU, into a single kernel, so the
intermediate results never travel to memory.

The network is a directed acyclic graph with N operator nodes, numbered 0 to
N - 1, and M directed data-flow edges. Every node has one type: Conv, Bias,
ReLU or Other.

A fusion is formed for every node B of type Bias such that
 - B has exactly one incoming edge and exactly one outgoing edge,
 - the incoming edge comes from a node of type Conv, and
 - the outgoing edge goes to a node of type ReLU.

Only the Bias node has a degree condition; the Conv and ReLU nodes may have any
other edges. The input guarantees that no Conv node and no ReLU node takes part
in more than one such pattern.

Count the fusions.

Function to Complete
countFusions(ops, fromNodes, toNodes). ops[i] is the type of node i, and edge j
goes from fromNodes[j] to toNodes[j]. Return the number of fusions.

Input Format
 - The first line holds N and M.
 - Each of the next N lines holds NodeId OpType. Every id from 0 to N - 1
   appears exactly once, in any order.
 - Each of the next M lines holds u v: a directed edge from node u to node v.

Output Format
Print a single integer: the number of Conv -> Bias -> ReLU fusions.

Constraints
1 <= N <= 5000
1 <= M <= 10^4
OpType is one of Conv, Bias, ReLU, Other
0 <= u, v <= N - 1, u != v, no edge appears twice, and the graph has no
directed cycle
No Conv or ReLU node belongs to two different fusion patterns.

Examples
(not yet captured)
*/
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

void solve()
{

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
