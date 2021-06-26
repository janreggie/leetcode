#include <bits/stdc++.h>
using namespace std;

class Solution {

    vector<int> _nums;

public:
    
    bool canBeIncreasing(const vector<int>& nums) {

        _nums = nums;

        if (_nums.size() == 2) {
            return true;
        }
        if (_nums.size() == 3) {
            return _nums.at(0) < _nums.at(1) || _nums.at(1) < _nums.at(2) || _nums.at(0) < _nums.at(2);
        }

        if (_nums.at(0) >= _nums.at(1)) {
            return mustBeIncreasing(0);
        }
        if (_nums.at(_nums.size()-2) >= _nums.at(_nums.size()-1)) {
            return mustBeIncreasing(_nums.size()-1);
        }

        // Now, check at the middle...
        for (size_t ii{0}; ii < _nums.size()-2; ++ii) {

            if (_nums.at(ii) >= _nums.at(ii+1)) {
                return mustBeIncreasing(ii) || mustBeIncreasing(ii+1);
            }
        }

        return true;
    }

private:

    // checks if _nums is strictly increasing if toRemove is removed
    //
    bool mustBeIncreasing(size_t toRemove) {

        cout << "mustBeIncreasing check at " << toRemove << endl;

        int lastVal{_nums.at(0)};
        if (toRemove == 0) {
            lastVal = _nums.at(1);
            for (size_t ii{2}; ii < _nums.size(); ++ii) {
                if (_nums.at(ii) <= lastVal) { return false; }
                lastVal = _nums.at(ii);
            }
            return true;
        }

        for (size_t ii{1}; ii < toRemove; ++ii) {

            if (_nums.at(ii) <= lastVal) { return false; }
            lastVal = _nums.at(ii);
        }

        for (size_t ii{toRemove+1}; ii < _nums.size(); ++ii) {
            if (_nums.at(ii) <= lastVal) { return false; }
            lastVal = _nums.at(ii);
        }

        return true;
    }

};

struct Testcase {

    const vector<int> _nums;
    const bool _expected;

    void info() const {
        cout << "nums:{";
        for (const int& num : _nums) { cout << num << ","; }
        cout << "}, expected:" << (_expected ? "true" : "false") << endl;
    }

    void test() const {
        info();
        Solution soln;
        bool actual{soln.canBeIncreasing(_nums)};
        cout << "actual:" << (actual ? "true" : "false") << endl;
        assert(_expected==actual);
    }
};

int main() {

    const vector<Testcase> testcases{
        {{1,2,10,5,7}, true},
        {{2,3,1,2}, false},
        {{1,1,1}, false},
        {{1,2,3}, true},
        {{105,924,32,968}, true},
        {{1,1}, true},
        {{100,21,100}, true},
        {{962,23,27,555}, true},
        {{493,211,437,575,797,973,374}, false},
    };

    for (const Testcase& tc : testcases) { tc.test(); }
}

