#include "bits/stdc++.h"
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
/*ou are given a 0-indexed array of strings words. Each string consists of lowercase English letters only. No letter occurs more than once in any string of words.

Two strings s1 and s2 are said to be connected if the set of letters of s2 can be obtained from the set of letters of s1 by any one of the following operations:

Adding exactly one letter to the set of the letters of s1.
Deleting exactly one letter from the set of the letters of s1.
Replacing exactly one letter from the set of the letters of s1 with any letter, including itself.*/
ll convert(string s)
{
    ll num = 0 ; 
    for(auto c : s)
    {
        num = num | (1 << (c - 'a')) ;
        
    }
    return num ;


}
vector < ll > can_b(ll state)
{
    vector < ll > res ; 
    res.push_back(state) ;
    for( ll i = 0 ; i < 26 ; i++)
    {
        ll ati = (1 << i) ;
        ll add = state | ati ;
        ll del = state & (~ati) ;
        res.push_back(add) ;
        res.push_back(del) ;
        for( ll j = 0 ; j < 26 ; j++)
        {
            ll atj = (1 << j) ;
            ll rep = (state & (~atj)) | ati ;
            res.push_back(rep) ;
        }
    }
    return res ; 


}
struct UnionFind
{
    ll n , setsz , *par , *rank , maxsz ; 
    UnionFind()
    {
        n = setsz = 0 ; 
        par = nullptr ;
        rank = nullptr ;
        maxsz = 0 ; 
    }
    UnionFind( ll a)
    {
        n = setsz = a ; 
        par = new ll[n+1] ; 
        rank = new ll[n+1] ; 
        maxsz = 1 ; 
        for( ll i = 1 ; i <= n ; i++)
        {
            par[i] = i ; 
            rank[i] = 1 ; 
        }
    }
    ll find( ll x )
    {
        if( x != par[x])
        {
            return par[x] = find(par[x]) ;
        }
        else 
        {
            return x ; 
        }
    }
    void merge( ll a , ll b)
    {
        ll x = find(a) ; 
        ll y = find(b) ; 
        if (x == y) return ; 
        if( x != y )
        {
            if(rank[x] >= rank[y])
            {
                par[y] = x ; 
                rank[x] += rank[y] ;
                maxsz = max(maxsz , rank[x]) ; 
            }
            else 
            {
                par[x] = y ; 
                rank[y] += rank[x] ; 
                maxsz = max(maxsz , rank[y]) ; 

            }
            setsz-- ; 
        }


    }
    ll maxu()
    {
        return maxsz ; 
    }


}; 

void solve() 
{
    ll n ; 
    cin >> n ; 
    vector < string > words ;
    for( ll i = 0 ; i < n ; i++)
    {
        string s ; 
        cin >> s ; 
        words.push_back(s) ;
    }

    UnionFind uf(n) ;
    // Map each unique bitmask to its word index
    unordered_map<ll, ll> mask_to_index;
    for (ll i = 0; i < n; i++) {
        ll state = convert(words[i]);
        mask_to_index[state] = i;
    }

    for (ll i = 0; i < n; i++) {
        ll state = convert(words[i]);
        vector<ll> possible = can_b(state);
        for (ll mask : possible) {
            auto it = mask_to_index.find(mask);
            if (it != mask_to_index.end()) {
                uf.merge(i + 1, it->second + 1);
            }
        }
    }
    
    

    




}
signed main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve() ; 
} 
