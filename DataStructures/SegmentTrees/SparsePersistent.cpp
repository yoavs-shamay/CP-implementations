template<class T>
struct SegmentTree
{
    struct Node
    {
        T value;
        Node *l, *r;
        Node(T val) : l(NULL), r(NULL), value(val) {}
        Node(Node *l, Node *r, operation<T> op) : l(l), r(r)
        {
            value = op(l->value, r->value);
        }
        void extend(T def)
        {
            if (!l) l = new Node(def);
            if (!r) r = new Node(def);
        }
    };

    ll N;
    Node *root;
    operation<T> op;
    T defaultVal;
    SegmentTree(ll N, Node *root, operation<T> op, T def) : root(root), N(N), op(op), defaultVal(def) {}

    SegmentTree(T def, operation<T> op, ll n) : op(op), defaultVal(def)
    {
        N = pow(2, ceil(log2(n)));
        root = new Node(defaultVal);
    }

    T _query(Node *cur, ll l, ll r, ll tl, ll tr)
    {
        if (tl >= l && tr <= r)
            return cur->value;
        if (tr < l || tl > r) return defaultVal;
        cur->extend(defaultVal);
        ll tmid = (tl + tr) / 2;
        return op(_query(cur->l, l, min(r, tmid), tl, tmid), _query(cur->r, max(l, tmid + 1), r, tmid + 1, tr));
    }
    T query(ll l, ll r)
    {
        return _query(root, l, r, 0, N - 1);
    }
    Node *_update(Node *cur, ll index, T newVal, ll tl, ll tr)
    {
        if (tl == tr)
        {
            return new Node(newVal);
        }
        cur->extend(defaultVal);
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
    SegmentTree<T> update(ll index, T newVal)
    {
        return SegmentTree(N, _update(root, index, newVal, 0, N - 1), op, defaultVal);
    }
};