template<class T>
struct SegmentTree
{
    struct Node
    {
        T value;
        T lazy;
        Node *l, *r;
        Node(T val, T lazyVal) : l(NULL), r(NULL), value(val), lazy(lazyVal) {}
        Node(Node *l, Node *r, operation<T> op, T lazy) : l(l), r(r), lazy(lazy)
        {
            value = op(l->value, r->value);
        }
        Node(Node *org, operation<T> lazyOp, T updateBy) : l(org->l), r(org->r)
        {
            value = lazyOp(org->value, updateBy);
            lazy = lazyOp(org->lazy, updateBy);
        }
    };

    ll N;
    Node *root;
    operation<T> op;
    operation<T> lazyOp;
    T defaultVal;
    T lazyDefault;
    SegmentTree(T def, operation<T> op, T lazyDef, operation<T> lazyOp, ll N, Node *root) : root(root), N(N), op(op), defaultVal(def), lazyOp(lazyOp), lazyDefault(lazyDef) {}

    Node *_build(ll l, ll r, vector<T> &arr)
    {
        if (l == r) return new Node(arr[l], lazyDefault);
        ll mid = (l + r) / 2;
        return new Node(_build(l, mid, arr), _build(mid + 1, r, arr), op, lazyDefault);
    }

    SegmentTree(T def, operation<T> op, T lazyDef, operation<T> lazyOp, vector<T> arr) : op(op), defaultVal(def), lazyDefault(lazyDef), lazyOp(lazyOp)
    {
        N = pow(2, ceil(log2(arr.size())));
        for (ll i = arr.size(); i < N; i++) arr.pb(def);
        root = _build(0, N - 1, arr);
    }

    SegmentTree(T def, operation<T> op, T lazyDef, operation<T> lazyOp, ll n) : SegmentTree(def, op, lazyDefault, lazyOp, vector<T>(n, def)) {}

    void _push(Node *cur)
    {
        if (cur->lazy != lazyDefault && cur->l)
        {
            cur->l = new Node(cur->l, lazyOp, cur->lazy);
            cur->r = new Node(cur->r, lazyOp, cur->lazy);
            cur->lazy = lazyDefault;
        }
    }
    
    T _query(Node *cur, ll l, ll r, ll tl, ll tr)
    {
        _push(cur);
        if (tl >= l && tr <= r)
            return cur->value;
        if (tr < l || tl > r) return defaultVal;
        ll tmid = (tl + tr) / 2;
        return op(_query(cur->l, l, min(r, tmid), tl, tmid), _query(cur->r, max(l, tmid + 1), r, tmid + 1, tr));
    }
    T query(ll l, ll r)
    {
        return _query(root, l, r, 0, N - 1);
    }
    Node *_update(Node *cur, ll l, ll r, T updateBy, ll tl, ll tr)
    {
        _push(cur);
        if (r < tl || l > tr || l > r) return cur;
        if (l <= tl && r >= tr)
        {
            return new Node(cur, lazyOp, updateBy);
        }
        ll tmid = (tl + tr) / 2;
        return new Node(_update(cur->l, l, min(r, tmid), updateBy, tl, tmid), _update(cur->r, max(l, tmid + 1), r, updateBy, tmid + 1, tr), op, lazyDefault);
    }
    SegmentTree<T> update(ll l, ll r, T updateBy)
    {
        return SegmentTree(defaultVal, op, lazyDefault, lazyOp, N, _update(root, l, r, updateBy, 0, N - 1));
    }
};