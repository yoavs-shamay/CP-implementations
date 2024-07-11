template<class T>
struct SegmentTree
{
    ll size;
    operation<T> op;
    T defaultValue;
    struct Node
    {
        Node *left;
        Node *right;
        T value;
        Node(T val) : value(val), left(NULL), right(NULL) {}
        Node *getLeft(T def)
        {
            if (!left) left = new Node(def);
            return left;
        }
        Node *getRight(T def)
        {
            if (!right) right = new Node(def);
            return right;
        }
    };
    Node *root;
    SegmentTree(T defaultValue, operation<T> op, ll len)
    {
        size = (1ll << (64 - __builtin_clzll(len - 1)));
        this->op = op;
        this->defaultValue = defaultValue;
        root = new Node(defaultValue);
    }
    T _query(Node *cur, ll l, ll r, ll tl, ll tr)
    {
        if (tl >= l && tr <= r)
            return cur->value;
        if (tr < l || tl > r) return defaultValue;
        ll tmid = (tl + tr) / 2;
        return op(_query(cur->getLeft(defaultValue), l, min(r, tmid), tl, tmid), _query(cur->getRight(defaultValue), max(l, tmid + 1), r, tmid + 1, tr));
    }
    T query(ll l, ll r)
    {
        return _query(root, l, r, 0, size - 1);
    }
    void _update(Node *cur, ll index, T newVal, ll tl, ll tr)
    {
        if (tl == tr)
        {
            cur->value = newVal;
            return;
        }
        ll tmid = (tl + tr) / 2;
        if (index > tmid) _update(cur->getRight(defaultValue), index, newVal, tmid + 1, tr);
        else _update(cur->getLeft(defaultValue), index, newVal, tl, tmid);
        cur->value = op(cur->getLeft(defaultValue)->value, cur->getRight(defaultValue)->value);
    }
    void update(ll index, T newVal)
    {
        _update(root, index, newVal, 0, size - 1);
    }
};