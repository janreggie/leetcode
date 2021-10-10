#include <bits/stdc++.h>
using namespace std;

class Solution {

public:
    string removeOccurrences(const string& s, const string& part) {

        size_t ind{s.find(part)};
        if (ind == s.npos) { return s; }
        return removeOccurrences(string(s.begin(), s.begin()+ind) + string(s.begin()+ind+part.size(), s.end()), part);
    }
};

struct Testcase{
    const string _s;
    const string _part;
    const string _expected;

    void info() const {
        cout << "s: " << _s << endl;
        cout << "part: " << _part << endl;
        cout << "expected: " << _expected << endl;
    }

    void test() const {
        info();
        Solution soln;
        const string actual{soln.removeOccurrences(_s, _part)};
        cout << "acutal: " << actual << endl;
        assert(_expected==actual);
    }
};

int main() {

    const vector<Testcase> testcases{
        {"daabcbaabcbc", "abc", "dab"},
        {"axxxxyyyyb", "xy", "ab"},
    };
    for (const Testcase& tc : testcases) { tc.test(); }
}

