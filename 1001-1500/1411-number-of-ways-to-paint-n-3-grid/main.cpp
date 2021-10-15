#include <bits/stdc++.h>
using namespace std;

class Solution {

    static constexpr long _M{1000000007};

public:
    int numOfWays(int n) {
        
        if (n == 1) { return 12; }
        
        long matrix[4]{2,2,2,3};
        exp(matrix, n-1);
        return (int)((6*(matrix[0]+matrix[1]+matrix[2]+matrix[3]))%_M);
    }
    
private:

    // A matrix `long m[4]` is represented as {w,x,y,z}
    void exp(long matrix[4], int n) {

        if (n == 1) { return; }

        if (n % 2 == 0) {
            sq(matrix);
            exp(matrix, n/2);
            return;
        }

        long m[4]; // copy of the matrix
        memcpy(m, matrix, sizeof m);
        exp(matrix, n-1);
        mul(m, matrix);
    }
    
    // mul multiplies a to b and saves the result in b
    void mul(long a[4], long b[4]) {
        long c[4];
        c[0] = (a[0]*b[0] + a[1]*b[2]) % _M;
        c[1] = (a[0]*b[1] + a[1]*b[3]) % _M;
        c[2] = (a[2]*b[0] + a[3]*b[2]) % _M;
        c[3] = (a[2]*b[1] + a[3]*b[3]) % _M;
        memcpy(b, c, sizeof c);
    }
    
    // sq squares a matrix in-place
    void sq(long a[4]) {
        mul(a,a);
    }
};

struct Testcase{

    const int _n;
    const int _expected;

    void info() const {
        cout << "n:" << _n << ", expected:" << _expected << endl;
    }

    void test() const {
        info();
        Solution soln;
        int actual{soln.numOfWays(_n)};
        cout << "actual:" << actual << endl;
        assert(_expected==actual);
    }
};

int main() {

    const vector<Testcase> testcases{
        {1,12},
        {2,54},
        {3,246},
        {7,106494},
        {5000,30228214}
    };
    for (const Testcase& tc : testcases) { tc.test(); }
}

