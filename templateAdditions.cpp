typedef ll (*operation) (ll a, ll b);
const operation addOp = [](ll a, ll b){return a + b;};
const operation maxOp = [](ll a, ll b){return max(a, b);};
const operation minOp = [](ll a, ll b){return min(a, b);};

typedef complex<double> cd;
typedef vector<cd> vcd;
typedef vector<vcd> vvcd;
typedef vector<vvcd> vvvcd;

const double PI = acos(-1);