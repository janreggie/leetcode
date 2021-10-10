#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    int chalkReplacer(const std::vector<int>& chalk, int k) {

	    long sumTotalUse{0};
	    for (const int& ch : chalk) { sumTotalUse += ch; }
	    k %= sumTotalUse;

	    // Now, do the needful.
	    for (size_t ii{0}; ii < chalk.size(); ++ii) {
		    if (k < chalk.at(ii)) { return (int)ii; }
		    k -= chalk.at(ii);
	    }

	    return 0;
    }
};

struct Testcase {
	const std::vector<int> _chalk;
	const int _k;
	const int _expected;
	Testcase(const std::vector<int> chalk, int k, int expected)
	: _chalk{chalk}, _k{k}, _expected{expected} {};
	void details() const {
		std::cout << "Chalk: ";
		for (const int& ch : _chalk) { std::cout << ch << ","; }
		std::cout << " k: " << _k << " expected: " << _expected << std::endl;
	}
	void test() const {
		details();
		Solution soln;
		const int actual{soln.chalkReplacer(_chalk,_k)};
		std::cout << "Expected: " << _expected << " Actual: " << actual << std::endl;
		assert(_expected == actual);
	}
};

int main() {
	const std::vector<Testcase> testCases{
		Testcase({5,1,5}, 22, 0),
		Testcase({3,4,1,2}, 25, 1),
	};
	for (const Testcase& tc : testCases) { tc.test(); }
}