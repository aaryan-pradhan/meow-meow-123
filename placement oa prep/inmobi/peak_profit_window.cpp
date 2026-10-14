/*
1. Peak Profit Window (InMobi)

Description:
A proprietary trading desk logs its net profit or loss for each trading day over N days. 
Day i's result is A[i] — a positive number means the desk made money that day, a negative number means it lost money. 
Each day's P&L is bounded by |A[i]| <= 15007, and the log covers up to N <= 50000 trading days.

The head of risk keeps asking the same kind of question: "Looking only at the days between x and y, what's the best consecutive run of days we had?" — i.e., the maximum total profit achievable by picking some unbroken stretch of days i to j, where x <= i <= j <= y.

You are asked to build a tool that answers these questions instantly, no matter how the range shifts. 
You will be given M such queries, and for each you must report the best consecutive-day streak's total P&L within that window [x, y].

Input Format:
- Line 1: an integer N — the number of trading days logged.
- Line 2: N space-separated integers — the daily P&L values A[1..N].
- Line 3: an integer M — the number of audit queries.
- Next M lines: each contains two integers x and y — the inclusive day range to analyze.

Output Format:
- For each query, output one line: the maximum total P&L achievable over any consecutive run of days within [x, y].

Constraints:
- 1 <= N <= 50000
- |A[i]| <= 15007
- 1 <= x <= y <= N
- 1 <= M <= 50000
Time Limit: 0.60 seconds
*/

#include <bits/stdc++.h>
using namespace std;
#define INF 1e18 
#define ll long long 
ll arr[50050] ; 

struct stnode{
    ll sum ; 
    ll p ; 
    ll s ; 
    ll ans ; 
    stnode()
    {
        sum = 0 ; 
        p = s = ans = -INF ; 
    }

}; 
vector < stnode > st ; 
stnode merge( stnode a , stnode b)
{
    stnode res ; 
    res.sum = a.sum + b.sum; 
    res.p = max(a.p , a.sum + b.p) ; 
    res.s = max(b.s , b.sum + a.s ) ; 
    res.ans = max({a.ans , b.ans , a.s + b.p}) ; 
    return res ; 

}
void build(ll id , ll l , ll r)
{
    if(l == r)
    {
        st[id].sum = arr[l] ; 
        st[id].p = arr[l] ; 
        st[id].s = arr[l] ; 
        st[id].ans = arr[l] ; 
    }
    else 
    {
        ll mid = l + ( r - l ) / 2 ; 
        build(2 * id , l , mid) ; 
        build(2*id + 1 , mid + 1 , r) ; 
        st[id] = merge(st[2 * id ] , st[ 2 * id + 1]) ; 
    }
}
stnode query(ll id , ll l , ll r , ll lq , ll rq)
{
    if(lq > r )
    {
        return stnode() ; 
    }
    if (rq < l)
    {
        return stnode() ; 
    }
    if ( lq <= l && r <= rq)
    {
        return st[id] ; 
    }
    ll mid = l + ( r - l ) / 2 ;
    stnode left = query(2 * id , l , mid , lq , rq) ; 
    stnode right = query(2 * id + 1 , mid + 1 , r , lq , rq ) ; 
    return merge(left , right) ; 
}
void solve() {
    ll n ; 
    cin >> n ;

    st.resize(4 * n + 10 ); 
    for(ll i = 1 ; i <= n ; i++) cin >> arr[i]; 
    build(1 , 1 , n ) ;
    ll m ; 
    cin >> m ; 
    for(ll i = 0 ; i < m ; i++)
    {
        ll x , y ;  
        cin >> x >> y ; 
        stnode res = query(1 , 1 , n , x , y ) ; 
        cout << res.ans << endl ; 
        

    }
}
    

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}

