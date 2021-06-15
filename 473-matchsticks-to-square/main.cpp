#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

class Solution {

	static constexpr int M{1000000007};

	std::vector<long> _sticks; // long because i am NOT going to deal with overflows
	                           // (also have this sorted to make things easier)
	long _sideLength;

public:
	bool makesquare(const std::vector<int>& matchsticks) {

		// If there are few matchsticks
		//
		if (matchsticks.size() < 4) { return false; }
		if (matchsticks.size() == 4) {
			return matchsticks.at(0) == matchsticks.at(1) &&
				matchsticks.at(1) == matchsticks.at(2) &&
				matchsticks.at(2) == matchsticks.at(3);
		}

		long totalLength{0};
		_sticks = std::vector<long>(matchsticks.size());

		for (size_t ii{0}; ii < matchsticks.size(); ++ii) {
			totalLength += matchsticks.at(ii);
			_sticks.at(ii) = matchsticks.at(ii);
		}
		std::sort(_sticks.begin(), _sticks.end(), std::greater<>());

		if (totalLength % 4 != 0) { return false; }
		_sideLength = totalLength/4;

		// Check if there are any sticks that are longer than sideLength
		//
		if (_sticks.at(0) > _sideLength) { return false; }

		// Force the first stick to be at the first side
		//
		return iter(1, _sticks.at(0), 0, 0, 0);
	}

private:
	// Check if s1~s4 is "viable" and if so, insert _sticks.at(ind) to one of them
	//
	bool iter(size_t ind, long s1, long s2, long s3, long s4) {

		if (s1 > _sideLength || s2 > _sideLength || s3 > _sideLength || s4 > _sideLength) {
			return false;
		}
		if (ind >= _sticks.size()) { 
			return s1 == s2 && s2 == s3 && s3 && s4;
		}

		long side{_sticks.at(ind)};
		bool result{iter(ind+1, s1+side, s2, s3, s4) || 
			iter(ind+1, s1, s2+side, s3, s4) ||
			iter(ind+1, s1, s2, s3+side, s4) ||
			iter(ind+1, s1, s2, s3, s4+side)};
		return result;
	}
};

struct Testcase{

	const std::vector<int> _matchsticks;
	const bool _expected;

	void info() const {
		std::cout << "Matchsticks: {";
		for (const int& stick : _matchsticks) { std::cout << stick << " "; }
		std::cout << "} Expected: " << (_expected ? "true" : "false") << std::endl;
	}
	void test() const {
		info();
		Solution soln;
		bool actual{soln.makesquare(_matchsticks)};
		std::cout << "Actual: " << (actual ? "true" : "false") << std::endl;
		assert(_expected==actual);
	}
};

int main() {

	const std::vector<Testcase> testcases{
		{{1,1,2,2,2},true},
		{{3,3,3,3,4},false},
	};
	for (const Testcase& tc : testcases) { tc.test(); }
}

