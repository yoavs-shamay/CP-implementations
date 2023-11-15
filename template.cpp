#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> p;
typedef pair<ll, p> tri;
typedef vector<ll> v;
typedef vector<v> vv;
typedef vector<p> vp;
typedef vector<tri> vtri;
typedef vector<vtri> vvtri;
typedef vector<vvtri> vvvtri;
typedef vector<vv> vvv;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef vector<p> vp;
typedef vector<vp> vvp;
typedef vector<vvp> vvvp;
typedef vector<vvvp> vvvvp;
const ll mod = 1e9 + 7;
const ll INF = 1e15;
#define f first
#define s second
#define pb push_back
#define loop(a) for (ll i = 0; i < a; i++)
#define setmin(a, b) a = min(a, b)
#define setmax(a, b) a = max(a, b)
#define all(v) v.begin(), v.end()
ll maxInArr(v &arr)
{
    ll maxi = -INF;
    for (ll x : arr) setmax(maxi, x);
    return maxi;
}
ll minInArr(v &arr)
{
    ll mini = INF;
    for (ll x : arr) setmin(mini, x);
    return mini;
}
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    
    return 0;
}