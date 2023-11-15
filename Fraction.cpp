typedef class Fraction
{
public:
    long long num, denom;

    void _reduce()
    {
        ll g = gcd(num, denom);
        num /= g;
        denom /= g;
    }

    Fraction(long long u, long long d)
    {
        num = u;
        denom = d;
        _reduce();
    }

    Fraction(long long x)
    {
        num = x;
        denom = 1;
    }

    Fraction operator+(Fraction o)
    {
        return Fraction(num * o.denom + o.num * denom, denom * o.denom);
    }

    Fraction operator-()
    {
        return Fraction(-1 * num, denom);
    }

    Fraction operator-(Fraction o)
    {
        return *this + (-o);
    }

    Fraction operator*(Fraction o)
    {
        return Fraction(num * o.num, denom * o.denom);
    }

    Fraction operator/(Fraction o)
    {
        return Fraction(num * o.denom, denom * o.num);
    }

    Fraction operator+=(Fraction o)
    {
        num = num * o.denom + o.num * denom;
        denom *= o.denom;
        _reduce();
    }

    Fraction operator-=(Fraction o)
    {
        num = num * o.denom - o.num * denom;
        denom *= o.denom;
        _reduce();
    }

    Fraction operator*=(Fraction o)
    {
        num *= o.num;
        denom *= o.denom;
        _reduce();
    }

    Fraction operator/=(Fraction o)
    {
        num *= o.denom;
        denom *= o.num;
        _reduce();
    }

    bool operator<(Fraction o)
    {
        return num * o.denom < o.num * denom;
    }

    bool operator>(Fraction o)
    {
        return num * o.denom > o.num * denom;
    }

    bool operator==(Fraction o)
    {
        return num * o.denom == o.num * denom;
    }

    operator long long() const {return num;}

    void operator++()
    {
        num += denom;
        _reduce();
    }

    void operator--()
    {
        num -= denom;
        _reduce();
    }
} Fraction;

ostream& operator<<(ostream& os, const Fraction& f)
{
    os << f.num;
    return os;
}

istream& operator>> (istream& is, Fraction& f)
{
    long long cur;
    is >> cur;
    f = Fraction(cur);
    return is;
}
