template<class T>
struct SegmentTree
{
    vector<T> st;
    vector<T> lazy;
    ll N;
    T stInitial;
    T lazyInitial;
    operation<T> stOperation;
    operation<T> lazyOperation;
    SegmentTree(T stInitial, operation<T> stOperation, T lazyInitial, operation<T> lazyOperation, ll n) 
    {
        this->stInitial = stInitial;
        this->lazyInitial = lazyInitial;
        this->stOperation = stOperation;
        this->lazyOperation = lazyOperation;
        N = pow(2, ceil(log2(n)));
        st = vector<T>(2 * N, stInitial);
        lazy = vector<T>(2 * N, lazyInitial);
    }
    SegmentTree(T stInitial, operation<T> stOperation, T lazyInitial, operation<T> lazyOperation, vector<T> &arr)
    {
        ll n = arr.size();
        this->stInitial = stInitial;
        this->lazyInitial = lazyInitial;
        this->stOperation = stOperation;
        this->lazyOperation = lazyOperation;
        N = pow(2, ceil(log2(n)));
        st = vector<T>(2 * N, stInitial);
        lazy = vector<T>(2 * N, lazyInitial);
        for (ll i = N; i < N + n; i++)
        {
            st[i] = arr[i - N];
        }
        for (ll i=  N - 1; i > 0; i--) st[i] = stOperation(st[2 * i], st[2 * i + 1]);
    }
    void _push(ll index)
    {
        if (index >= 2 * N) return;
        if (index >= N)
        {
            lazy[index] = lazyInitial;
            return;
        }
        st[2 * index] = lazyOperation(st[2 * index], lazy[index]);
        lazy[2 * index] = lazyOperation(lazy[2 * index], lazy[index]);
        st[2 * index + 1] = lazyOperation(st[2 * index + 1], lazy[index]);
        lazy[2 * index + 1] = lazyOperation(lazy[2 * index + 1], lazy[index]);
        lazy[index] = lazyInitial;
    }
    void _updateRange(T add, ll index, ll from, ll to, ll l, ll r)
    {
        if (from > to) return;
        _push(index);
        if (from == l && to == r)
        {
            st[index] = lazyOperation(st[index], add);
            lazy[index] = lazyOperation(lazy[index], add);
            return;
        }
        ll mid = (l + r) / 2;
        _updateRange(add, 2 * index, from, min(to, mid), l, mid);
        _updateRange(add, 2 * index + 1, max(from, mid + 1), to, mid + 1, r);
        st[index] = stOperation(st[2 * index], st[2 * index + 1]);
    }
    void update(ll from, ll to, T add)
    {
        _updateRange(add, 1, from, to, 0, N - 1);
    }
    T _queryRange(ll index, ll tl, ll tr, ll from, ll to)
    {
        _push(index);
        if (from > to)
            return stInitial;
        if (from == tl && to == tr)
            return st[index];
        ll tmid = (tl + tr) / 2;
        return stOperation(_queryRange(2 * index,  tl, tmid, from, min(to, tmid)),_queryRange(2 * index + 1, tmid + 1, tr, max(from, tmid + 1), to));
    }
    T query(ll from, ll to)
    {
        return _queryRange(1, 0, N - 1, from, to);
    }
};