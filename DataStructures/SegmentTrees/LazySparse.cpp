struct SegmentTree
{
    ll size;
    operation op;
    ll defaultValue;
    ll lazyDefault;
    operation lazyOp;
    struct Node
    {
        Node *left;
        Node *right;
        ll value;
        ll lazy;
        Node(ll val, ll lazyVal) : value(val), lazy(lazyVal), left(NULL), right(NULL) {}
        Node *getLeft(ll def, ll lazyDef)
        {
            if (!left) left = new Node(def, lazyDef);
            return left;
        }
        Node *getRight(ll def, ll lazyDef)
        {
            if (!right) right = new Node(def, lazyDef);
            return right;
        }
    };
    Node *root;
    SegmentTree(operation op, ll defaultValue, operation lazyOp, ll lazyDefault, ll len)
    {
        size = (1ll << (64 - __builtin_clzll(len - 1)));
        this->op = op;
        this->defaultValue = defaultValue;
        this->lazyOp = lazyOp;
        this->lazyDefault = lazyDefault;
        root = new Node(defaultValue, lazyDefault);
    }
    void _push(Node *cur)
    {
        Node *l = cur->getLeft(defaultValue, lazyDefault), *r = cur->getRight(defaultValue, lazyDefault);
        l->lazy = lazyOp(l->lazy, cur->lazy);
        r->lazy = lazyOp(r->lazy, cur->lazy);
        l->value = lazyOp(l->value, cur->lazy);
        r->value = lazyOp(r->value, cur->lazy);
        cur->lazy = lazyDefault;
    }
    ll _query(Node *cur, ll l, ll r, ll tl, ll tr)
    {
        _push(cur);
        if (tl >= l && tr <= r)
            return cur->value;
        if (tr < l || tl > r) return defaultValue;
        ll tmid = (tl + tr) / 2;
        return op(_query(cur->getLeft(defaultValue, lazyDefault), l, min(r, tmid), tl, tmid), _query(cur->getRight(defaultValue, lazyDefault), max(l, tmid + 1), r, tmid + 1, tr));
    }
    ll query(ll l, ll r)
    {
        return _query(root, l, r, 0, size - 1);
    }
    void _update(Node *cur, ll from, ll to, ll updateBy, ll tl, ll tr)
    {
        _push(cur);
        if (tl >= from && tr <= to)
        {
            cur->value = lazyOp(cur->value, updateBy);
            cur->lazy = lazyOp(cur->lazy, updateBy);
            return;
        }
        if (to < tl || from > tr) return;
        ll tmid = (tl + tr) / 2;
        _update(cur->getLeft(defaultValue, lazyDefault), from, min(to, tmid), updateBy, tl, tmid);
        _update(cur->getRight(defaultValue, lazyDefault), max(from, tmid + 1), to, updateBy, tmid + 1, tr);
        cur->value = op(cur->getLeft(defaultValue, lazyDefault)->value, cur->getRight(defaultValue, lazyDefault)->value);
    }
    void update(ll from, ll to, ll updateBy)
    {
        _update(root, from, to, updateBy, 0, size - 1);
    }
};