template<class T>
struct Matrix
{
    vector<vector<T>> arr;

    Matrix() : arr(vector<vector<T>>(1, vector<T>(1))) {}
    Matrix(vector<vector<T>> mat) : arr(mat) {}
    Matrix(ll N, ll M) : Matrix(vector<vector<T>>(N, vector<T>(M, 0))) {}
    Matrix(const Matrix &other) : Matrix(other.arr) {}

    Matrix& operator+=(const Matrix &other)
    {
        for (ll i = 0; i < arr.size(); i++)
        {
            for (ll j =0; j < arr[0].size(); j++)
            {
                arr[i][j] += other.arr[i][j];
            }
        }
        return *this;
    }
    Matrix operator+(const Matrix &other)
    {
        Matrix res(*this);
        return res += other;
    }
    
    Matrix& operator-=(const Matrix &other)
    {
        for (ll i = 0; i < arr.size(); i++)
        {
            for (ll j =0; j < arr[0].size(); j++)
            {
                arr[i][j] -= other.arr[i][j];
            }
        }
        return *this;
    }
    Matrix operator-(const Matrix &other)
    {
        Matrix res(*this);
        return res -= other;
    }
    Matrix operator-()
    {
        Matrix zero(arr.size(),arr[0].size());
        return zero -= *this;
    }

    Matrix operator*(const Matrix &other)
    {
        vector<vector<T>> res(arr.size(), vector<T>(other.arr[0].size()));
        for (ll i= 0 ; i < arr.size(); i++)
        {
            for (ll k = 0; k < arr[0].size(); k++)
            {
                for (ll j = 0; j < other.arr[0].size(); j++)
                {
                    res[i][j] += arr[i][k] * other.arr[k][j];
                }
            }
        }
        return Matrix(res);
    }
    Matrix& operator*=(const Matrix &other)
    {
        return *this = (*this * other);
    }
    Matrix id(ll N)
    {
        vector<vector<T>> res(N, vector<T>(N, 0));
        for (ll i = 0; i < N; i++) res[i][i] = 1;
        return Matrix(res);
    }
    Matrix pow(ll exp)
    {
        if (exp == 0) return id(arr.size());
        Matrix res = pow(exp / 2);
        res *= res;
        if (exp % 2 == 1) res *= *this;
        return res;
    }
    bool operator==(const Matrix &other)
    {
        return arr == other.arr;
    }
    bool operator!=(const Matrix &other)
    {
        return arr != other.arr;
    }

    friend ostream &operator<<(ostream &os, const Matrix &mat)
    {
        for (ll i = 0; i < mat.arr.size(); i++)
        {
            for (ll j = 0; j < mat.arr[0].size(); j++)
            {
                os << mat.arr[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }
};