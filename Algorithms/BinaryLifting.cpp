vv toLifting(v &next)
{
    ll N = next.size();
    ll logN = pow(2, ceil(log2(N)));
    vv res(N, v(logN + 1));
    for (ll i = 0; i < N; i++) res[i][0] = next[i];
    for (ll iter = 1; iter <= logN; iter++)
    {
        for (ll i= 0 ; i < N; i++) res[i][iter] = res[res[i][iter - 1]][iter - 1];
    }
    return res;
}