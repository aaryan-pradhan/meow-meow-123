// Problem: C. XOR Problem (DeepInfra Round 1 / Codeforces Round 1126, Div. 1 + Div. 2)
// Link: https://codeforces.com/contest/2271/problem/C
// Pattern: (tags: bitmasks, constructive algorithms, graphs, greedy, math)
// Time:
// Space:
// Limits: 2 s, 256 MB

/*
You are given an integer n.

Define the beauty of an array a as |a| - f(a), where |a| is the length of a and
f(a) is the number of non-empty subarrays of a with bitwise XOR equal to 0.
Formally, f(a) is the number of pairs (l, r) such that 1 <= l <= r <= |a| and
a_l ^ a_{l+1} ^ ... ^ a_r = 0.

Among all arrays a consisting of integers from 0 to n that have the maximum
possible beauty, find one with maximum length.

Input
  t (1 <= t <= 1e4) test cases. Each: a single integer n (1 <= n <= 2e5).
  Sum of n over all test cases <= 2e5.

Output
  For each test case, output k, the length of the array. On the next line,
  output a_1 ... a_k (0 <= a_i <= n). Sum of k over all tests <= 1e6.
  Any valid answer is accepted.

Example
  input
  2
  1
  2
  output
  3
  1 1 1
  7
  2 2 1 0 2 0 1

Note
  n = 1: [1, 1, 1] has two zero-XOR subarrays, (1,2) and (2,3), so its beauty
  is 3 - 2 = 1. Every length-4 array over {0,1} has at least four, so its
  beauty is at most 0.
  n = 2: [2, 2, 1, 0, 2, 0, 1] has zero-XOR subarrays (1,2), (2,7), (4,4),
  (6,6), so its beauty is 7 - 4 = 3. [1, 2, 2, 1, 2] also has beauty 3 but is
  shorter. 3 is the maximum for n = 2, and no array longer than 7 achieves it.
*/