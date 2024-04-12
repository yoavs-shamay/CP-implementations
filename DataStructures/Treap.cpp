struct Treap
{
    struct Node
    {
        Node *l, *r;
        ll val, priority, size, sum, lazy;
        bool reverse;
        Node(ll _val) : val(_val), priority(rand()), size(1), l(NULL), r(NULL),reverse(false), sum(_val), lazy(0) {};
    };
    
    Node *t;

    Treap()
    {
        t = NULL;
    }

    Treap(Node *tree) : t(tree) {}

    Treap(v &arr)
    {
        t = NULL;
        for (ll x : arr) addBack(x);
    }

    static ll _size(Node *x)
    {
        if (x == NULL) return 0;
        return x->size;
    }
    
    static void _pull(Node *x)
    {
        if (x != NULL)
        {
            x->size = _size(x->l) + _size(x->r) + 1;
            x->sum = x->val + (x->l?x->l->sum:0) + (x->r?x->r->sum:0);
        }
    }
    static void _push(Node *x)
    {
        if (x == NULL) return;
        if (x->reverse)
        {
            swap(x->l,x->r);
            if (x->r) x->r->reverse ^= true;
            if (x->l) x->l->reverse ^= true;
            x->reverse = false;
        }
        if (x->lazy != 0)
        {
            if (x->l)
            {
                x->l->lazy += x->lazy;
                x->l->val += x->lazy;
                x->l->sum += x->l->size * x->lazy;
            }
            if (x->r)
            {
                x->r->lazy += x->lazy;
                x->r->val += x->lazy;
                x->r->sum += x->r->size * x->lazy;
            }
            x->lazy = 0;
        }
    }
    
    static void _split(Node *t, Node *&l, Node *&r, ll val) //first val values
    {
        _push(t);
        if (t == NULL)
        {
            l = r = NULL;
            return;
        }
        ll s = _size(t->l);
        if (s >= val)
        {
            _split(t->l,l,t->l,val); r = t;
        }
        else
        {
            _split(t->r,t->r,r, val - s - 1); l = t;
        }
        _pull(l);
        _pull(r);
    }   
    static void _merge(Node *&t, Node *l, Node *r)
    {
        _push(l);
        _push(r);
        if (l == NULL || r == NULL)
        {
            t = l? l : r;
            return;
        }
        if (l->priority > r->priority)
        {
            _merge(l->r,l->r,r); t = l;
        }
        else
        {
            _merge(r->l,l,r->l); t = r;
        }
        _pull(t);
    }
    
    static void _toArray(Node *t, v &res)
    {
        if (t == NULL) return;
        _push(t);
        _toArray(t->l, res);
        res.pb(t->val);
        _toArray(t->r, res);
    }
    
    void insert(ll val, ll index) //after index values
    {
        Node *n = new Node(val);
        Node *l, *r;
        _split(t, l, r, index);
        Node *m;
        _merge(m, l, n);
        _merge(t, m, r);
    }

    v toArray()
    {
        v res;
        _toArray(t, res);
        return res;
    }

    Treap erase(ll l, ll r)
    {
        Node *left, *range, *right;
        _split(t, left, right, r + 1);
        _split(left, left, range, l);
        _merge(t, left, right);
        return Treap(range);
    }

    ll at(ll index)
    {
        Node *l, *r, *cur;
        _split(t, l, r, index);
        _split(r, cur, r, 1);
        ll res = cur->val;
        _merge(l, l, cur);
        _merge(t, l, r);
        return res;
    }

    ll query(ll l, ll r)
    {
        Node *left, *range, *right;
        _split(t, left, right, l);
        _split(right, range, right, r - l + 1);
        ll res = range->sum;
        _merge(left,left,range);
        _merge(t,left,right);
        return res;
    }

    void reverse(ll l, ll r)
    {
        Node *left, *range, *right;
        _split(t, left, right, l);
        _split(right, range, right, r - l + 1);
        range->reverse = true;
        _merge(left,left,range);
        _merge(t,left,right);
    }
    
    void updatePoint(ll index, ll newVal)
    {
        erase(index, index);
        insert(newVal, index);
    }

    void updateRange(ll l, ll r, ll add)
    {
        
        Node *left, *range, *right;
        _split(t, left, right, l);
        _split(right, range, right, r - l + 1);
        range->lazy += add;
        range->val += add;
        range->sum += add * range->size;
        _merge(left,left,range);
        _merge(t,left,right);
    }

    void paste(ll index, Treap pas)
    {
        Node *l, *r;
        _split(t, l, r, index);
        _merge(l, l, pas.t);
        _merge(t, l, r);
    }

    ll size()
    {
        return _size(t);
    }

    void addBack(ll val)
    {
        insert(val, size());
    }

    void pasteBack(Treap pas)
    {
        paste(size(), pas);
    }
};