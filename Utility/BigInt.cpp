struct BigInt
{
    vb digs;
    BigInt(int num)
    {
        while (num > 0)
        {
            digs.pb(num % 2);
            num /= 2;
        }
    }
    BigInt()
    {
        digs = vb();
    }
    BigInt(const BigInt &other)
    {
        digs.resize(other.digs.size());
        copy(all(other.digs),digs.begin());
    }
    BigInt(vb diggs)
    {
        digs = diggs;
        while (!digs.empty() && !digs.back()) digs.pop_back();
    }
    bool at(int i)
    {
        if (i < digs.size()) return digs[i];
        return 0;
    }
    BigInt operator+(BigInt other)
    {
        bool remain = false;
        BigInt res;
        for (ll i = 0; i < max(digs.size(),other.digs.size()); i++)
        {
            bool a = at(i), b = other.at(i);
            res.digs.pb(a ^ b ^ remain);
            remain = (remain && (a || b)) || (a && b);
        }
        if (remain) res.digs.pb(remain);
        return res;
    }
    void operator+=(BigInt other)
    {
        *this = *this + other;
    }
    BigInt operator*(BigInt other)
    {
        BigInt c = BigInt(*this);
        BigInt res = 0;
        for (bool x : other.digs)
        {
            if (x) res += c;
            c += c;
        }
        return res;
    }
    void operator*=(BigInt other)
    {
        *this = *this * other;
    }
    BigInt operator-(BigInt other)
    {
        BigInt cpy(*this);
        while (other.digs.size() < digs.size()) other.digs.pb(false);
        for (ll i = 0 ;i<  other.digs.size(); i++) other.digs[i] = !other.digs[i];
        other += 1;
        if (other.digs.size() > digs.size()) other.digs.pop_back();
        cpy += other;
        while (cpy.digs.size() > digs.size()) cpy.digs.pop_back();
        while (!cpy.digs.empty() && !cpy.digs.back()) cpy.digs.pop_back();
        return cpy;
    }
    void operator-=(BigInt other)
    {
        *this = *this - other;
    }
    bool operator<(BigInt other)
    {
        BigInt c1(*this);
        while (other.digs.size() < c1.digs.size()) other.digs.pb(false);
        while (c1.digs.size() < other.digs.size()) c1.digs.pb(false);
        reverse(all(c1.digs)); reverse(all(other.digs));
        return (c1.digs < other.digs);
    }
    bool operator==(BigInt other)
    {
        return digs == other.digs;
    }
    bool operator<=(BigInt other)
    {
        return *this < other || *this == other;
    }
    pair<BigInt,BigInt> divide(BigInt &other)
    {
        BigInt cpy(*this);
        vector<BigInt> p2;
        BigInt cur = BigInt(other);
        while (cur <= *this)
        {
            p2.pb(BigInt(cur));
            cur += cur;
        }
        reverse(all(p2));
        vb res(p2.size());
        ll i = p2.size() - 1;
        for (auto x : p2)
        {
            if (x <= cpy)
            {
                cpy -= x;
                res[i] = true;
            }
            i--;
        }
        return {BigInt(res), cpy};
    }
    BigInt operator/(BigInt other)
    {
        return divide(other).f;
    }
    BigInt operator%(BigInt other)
    {
        return divide(other).s;
    }
    void operator/=(BigInt other)
    {
        *this = *this / other;
    }
    void operator%=(BigInt other)
    {
        *this = *this % other;
    }
    int toInt()
    {
        int res = 0;
        int mul = 1;
        for (auto x : digs)
        {
            res += x * mul;
            mul <<= 1;
        }
        return res;
    }
};