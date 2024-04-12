#define stinitial 0
#define stoperation(A, B) ((A)+(B))
typedef struct SegmentTree
{
    v st;
    ll N;
    SegmentTree(ll n) 
    {
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, stinitial);
    }
    SegmentTree(ll n, v &arr)
    {
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, stinitial);
        for (ll i = N; i < N + n; i++)
        {
            st[i] = arr[i - N];
        }
        for (ll i=  N - 1; i > 0; i--) st[i] = stoperation(st[2 * i], st[2 * i + 1]);
    }
    void update(ll index, ll value)
    {
        st[index + N] = value;
        ll i = (index + N) / 2;
        while (i > 0)
        {
            st[i] = stoperation(st[2 * i], st[2 * i + 1]);
            i /= 2;
        }
    }
    ll query(ll l, ll r)
    {
        l += N;
        r += N;
        ll sum = stinitial;
        while (l <= r)
        {
            if (l % 2 == 1)
            {
                sum = stoperation(sum, st[l]);
                l++;
            }
            if (r % 2 == 0)
            {
                sum = stoperation(sum, st[r]);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
    }
} SegmentTree;