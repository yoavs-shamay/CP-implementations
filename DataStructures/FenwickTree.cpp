template<class T>
struct FenwickTree
{
    vector<T> arr;
    T defaultVal;
    operation<T> op;

    FenwickTree(T def, operation<T> op, vector<T> a) : op(op), defaultVal(def)
    {
        arr = a;
        arr.insert(arr.begin(),def);
        for (ll i = 1; i < arr.size(); i++)
        {
            if (i + (i & -i) < arr.size()) arr[i + (i & -i)] = op(arr[i + (i & -i)], arr[i]);
        }
    }

    T query(ll r)
    {
        r++;
        T ans = defaultVal;
        for (;r>0;r-=(r&-r)) ans = op(ans, arr[r]);
        return ans;
    }

    void update(ll x, ll updateBy)
    {
        x++;
        for (;x<arr.size();x+=(x&-x)) arr[x] = op(arr[x], updateBy);
    }
};