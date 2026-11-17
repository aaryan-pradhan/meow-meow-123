/*
Array First Greater Index

Given two arrays a and b.
For each element in a (a[i]), you have to find the index (1-based) of an element in array b (b[j]) such that b[j] > a[i] and if there are multiple as such then return the minimum index one.
You have to return the vector of indices.
*/

#include <bits/stdc++.h>
using namespace std;
#define ll int 
vector<int> solveFirstGreaterIndex(vector<int>& a, vector<int>& b) {
    ll n = b.size() ; 
    if (n == 0) return vector<int>(a.size(), -1);
    vector < ll > pre(n,0) ; 
    pre[0] = b[0] ; 
    for( ll i = 1 ; i < n ; i++)
    {
        pre[i] = max( pre[i-1]  , b[i] ) ; 

    }
    // pre stores the max from 0 to i 
    vector < ll > ans ; 
    for (auto& x : a)
    {
        auto it = upper_bound(pre.begin(), pre.end(), x);
        // this returns the iterator to the first first element in pre that is bigger than a
        if(it == pre.end())
        {
            ans.push_back(-1) ; 
        }
        else 
        {
            ans.push_back((it - pre.begin()) + 1 ) ; 
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Testing logic here
    
    return 0;
}

