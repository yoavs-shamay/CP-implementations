template<class T>
using operation = function<T(T,T)>;
const operation<ll> addOp = [](ll a, ll b){return a + b;};
const operation<ll> maxOp = [](ll a, ll b){return max(a, b);};
const operation<ll> minOp = [](ll a, ll b){return min(a, b);};

typedef complex<double> cd;
typedef vector<cd> vcd;
typedef vector<vcd> vvcd;
typedef vector<vvcd> vvvcd;

const double PI = acos(-1);