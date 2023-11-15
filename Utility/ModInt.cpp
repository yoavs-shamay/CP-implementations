typedef struct ModInt
{
    ll val;
    ModInt(ll val = 0) : val(val % mod) {}
    ModInt operator+(const ModInt &other) const { return ModInt(val + other.val); }
    ModInt operator-(const ModInt &other) const { return ModInt(val - other.val + mod); }
    ModInt operator*(const ModInt &other) const { return ModInt(val * other.val); }
    ModInt pow(const ModInt &other) const {
        if (other.val == 0) return 1;
        ModInt res = pow(other.val / 2);
        res = res * res;
        if (other.val % 2 == 1) res = res * val;
        return res;
    }
    ModInt operator/(const ModInt &other) const { return ModInt(val * other.pow(mod - 2).val); }
    ModInt operator+=(const ModInt &other) { return *this = *this + other; }
    ModInt operator-=(const ModInt &other) { return *this = *this - other; }
    ModInt operator*=(const ModInt &other) { return *this = *this * other; }
    ModInt operator/=(const ModInt &other) { return *this = *this / other; }
    bool operator==(const ModInt &other) const { return val == other.val; }
    bool operator!=(const ModInt &other) const { return val != other.val; }
    friend ostream &operator<<(ostream &os, const ModInt &other) { return os << other.val; }
} ModInt;
ModInt modPow(ModInt a, ModInt b) {return a.pow(b);}