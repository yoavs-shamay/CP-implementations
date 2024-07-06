struct SegmentTree
{
    struct Node
    {
        ll value;
        Node *l, *r;
        Node(ll val) : l(NULL), r(NULL), value(val) {}
        Node(Node *l, Node *r, operation op) : l(l), r(r)
        {
            value = op(l->value, r->value);
        }
    };

    ll N;
    Node *root;
    operation op;
    ll defaultVal;
    SegmentTree(ll N, Node *root, operation op, ll def) : root(root), N(N), op(op), defaultVal(def) {}

    Node *_build(ll l, ll r, v &arr)
    {
        if (l == r) return new Node(arr[l]);
        ll mid = (l + r) / 2;
        return new Node(_build(l, mid, arr), _build(mid + 1, r, arr), op);
    }

    SegmentTree(v arr, operation op, ll def) : op(op), defaultVal(def)
    {
        N = pow(2, ceil(log2(arr.size())));
        arr.resize(N);
        root = _build(0, N - 1, arr);
    }

    SegmentTree(ll n, operation op, ll def) : SegmentTree(v(n, 0), op, def) {}

    ll _query(Node *cur, ll l, ll r, ll tl, ll tr)
    {
        if (tl >= l && tr <= r)
            return cur->value;
        if (tr < l || tl > r) return defaultVal;
        ll tmid = (tl + tr) / 2;
        return op(_query(cur->l, l, min(r, tmid), tl, tmid), _query(cur->r, max(l, tmid + 1), r, tmid + 1, tr));
    }
    ll query(ll l, ll r)
    {
        return _query(root, l, r, 0, N - 1);
    }
    Node *_update(Node *cur, ll index, ll newVal, ll tl, ll tr)
    {
        if (tl == tr)
        {
            return new Node(newVal);
        }
        ll tmid = (tl + tr) / 2;
        if (index > tmid)
        {
            return new Node(cur->l, _update(cur->r, index, newVal, tmid + 1, tr), op);
        }
        else
        {
            return new Node(_update(cur->l, index, newVal, tl, tmid), cur->r, op);
        }
    }
    SegmentTree update(ll index, ll newVal)
    {
        return SegmentTree(N, _update(root, index, newVal, 0, N - 1), op, defaultVal);
    }
};