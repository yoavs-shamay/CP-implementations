vcd fft(vcd &arr)
{
    ll n = arr.size();
    if (n == 1) return arr;
    vcd a0(n / 2), a1(n / 2);
    for (ll i =0 ;i < n / 2; i++)
    {
        a0[i] = arr[2 * i];
        a1[i] = arr[2 * i + 1];
    }
    vcd a0fft = fft(a0), a1fft = fft(a1);
    cd baseRoot(cos(2 * PI / n), sin(2 * PI / n));
    cd curRoot = 1;
    vcd res(n);
    for (ll i = 0; i < n / 2; i++)
    {
        res[i] = a0fft[i] + curRoot * a1fft[i];
        res[i + n / 2] = a0fft[i] - curRoot * a1fft[i];
        curRoot *= baseRoot;
    }
    return res;
}

vcd inverseFFT(vcd &arr)
{
    ll n = arr.size();
    if (n == 1) return arr;
    vcd a0(n / 2), a1(n / 2);
    for (ll i =0 ;i < n / 2; i++)
    {
        a0[i] = arr[2 * i];
        a1[i] = arr[2 * i + 1];
    }
    vcd a0fft = inverseFFT(a0), a1fft = inverseFFT(a1);
    cd baseRoot(cos(-2 * PI / n), sin(-2 * PI / n));
    cd curRoot = 1;
    vcd res(n);
    for (ll i = 0; i < n / 2; i++)
    {
        res[i] = (a0fft[i] + curRoot * a1fft[i]) / cd(2);
        res[i + n / 2] = (a0fft[i] - curRoot * a1fft[i]) / cd(2);
        curRoot *= baseRoot;
    }
    return res;
}
v multiply(v a, v b)
{
    ll expectedSize = a.size() + b.size();
    expectedSize = (1ll << (64 - __builtin_clzll(expectedSize - 1)));
    vcd aComplex(expectedSize), bComplex(expectedSize);
    for (ll i = 0 ;i < a.size(); i++) aComplex[i] = a[i];
    for (ll i= 0; i < b.size(); i++) bComplex[i] = b[i];
    aComplex = fft(aComplex); bComplex = fft(bComplex);
    vcd mul(expectedSize);
    for (ll i = 0; i < expectedSize; i++) mul[i] = aComplex[i] * bComplex[i];
    mul = inverseFFT(mul);
    v res;
    ll actSize = a.size() + b.size();
    for (ll i =0; i < actSize; i++)
    {
        res.pb(round(mul[i].real()));
    }
    return res;
}