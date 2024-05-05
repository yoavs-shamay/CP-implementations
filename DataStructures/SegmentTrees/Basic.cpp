struct SegmentTree
{
    v st;
    ll N;
    ll initial;
    operation op;
    SegmentTree(ll initial, operation op, ll n) : initial(initial), op(op)
    {
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, initial);
    }
    SegmentTree(ll initial, operation op, v &arr) : initial(initial), op(op)
    {
        ll n = arr.size();
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, initial);
        for (ll i = N; i < N + n; i++)
        {
            st[i] = arr[i - N];
        }
        for (ll i=  N - 1; i > 0; i--) st[i] = op(st[2 * i], st[2 * i + 1]);
    }
    void update(ll index, ll value)
    {
        st[index + N] = value;
        ll i = (index + N) / 2;
        while (i > 0)
        {
            st[i] = op(st[2 * i], st[2 * i + 1]);
            i /= 2;
        }
    }
    ll query(ll l, ll r)
    {
        l += N;
        r += N;
        ll sum = initial;
        while (l <= r)
        {
            if (l % 2 == 1)
            {
                sum = op(sum, st[l]);
                l++;
            }
            if (r % 2 == 0)
            {
                sum = op(sum, st[r]);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
    }
};