#define stinitial INF
#define stoperation(A, B) min(A,B)
#define lazyinitial 0
#define lazyoperation(A, B) ((A)+(B))
typedef struct SegmentTree
{
    v st;
    v lazy;
    ll N;
    SegmentTree(ll n) 
    {
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, stinitial);
        lazy = v(2 * N, lazyinitial);
    }
    SegmentTree(ll n, v &arr)
    {
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, stinitial);
        lazy = v(2 * N, lazyinitial);
        for (ll i = N; i < N + n; i++)
        {
            st[i] = arr[i - N];
        }
        for (ll i=  N - 1; i > 0; i--) st[i] = stoperation(st[2 * i], st[2 * i + 1]);
    }
    void _push(ll index)
    {
        if (index >= N)
        {
            lazy[index] = lazyinitial;
            return;
        }
        st[2 * index] = lazyoperation(st[2 * index], lazy[index]);
        lazy[2 * index] = lazyoperation(lazy[2 * index], lazy[index]);
        st[2 * index + 1] = lazyoperation(st[2 * index + 1], lazy[index]);
        lazy[2 * index + 1] = lazyoperation(lazy[2 * index + 1], lazy[index]);
        lazy[index] = lazyinitial;
    }
    void _updateRange(ll add, ll index, ll from, ll to, ll l, ll r)
    {
        if (from > to) return;
        if (from == l && to == r)
        {
            st[index] = lazyoperation(st[index], add);
            lazy[index] = lazyoperation(lazy[index], add);
        }
        else
        {
            _push(index);
            ll mid = (l + r) / 2;
            _updateRange(add, 2 * index, from, min(to, mid), l, mid);
            _updateRange(add, 2 * index + 1, max(from, mid + 1), to, mid + 1, r);
            st[index] = stoperation(st[2 * index], st[2 * index + 1]);
        }
    }
    void update(ll add, ll from, ll to)
    {
        _updateRange(add, 1, from, to, 0, N - 1);
    }
    ll _queryRange(ll index, ll tl, ll tr, ll from, ll to)
    {
        if (from > to)
            return stinitial;
        if (from == tl && to == tr)
            return st[index];
        _push(index);
        ll tmid = (tl + tr) / 2;
        return stoperation(_queryRange(2 * index,  tl, tmid, from, min(to, tmid)),_queryRange(2 * index + 1, tmid + 1, tr, max(from, tmid + 1), to));
    }
    ll query(ll from, ll to)
    {
        return _queryRange(1, 0, N - 1, from, to);
    }
} SegmentTree;