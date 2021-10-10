#include <cassert>
#include <iostream>
#include <map>
#include <vector>

class Solution {

public:
    bool isCovered(const std::vector<std::vector<int>>& inputRanges, int left, int right) {

	std::map<int,int> ranges; // ranges[start] = end;
	for (const std::vector<int>& rr : inputRanges) {
		if (ranges.count(rr.at(0)) == 0 || ranges.at(rr.at(0)) < rr.at(1)) {
			ranges[rr.at(0)] = rr.at(1);
		}
	}

	// For every range, `left` is nudged to the right by a bit.
	// When possible, right is also nudged by a bit.
	//
	for (const auto& iter : ranges) {
		if (left > right) { return true; }

		// What now?
		if (iter.first <= left) {
			left = (left <= iter.second ? iter.second+1 : left);
		}
	}

	return left > right;
    }
};

struct Testcase {
	const std::vector<std::vector<int>> _ranges;
	const int _left;
	const int _right;
	const bool _expected;
	Testcase(const std::vector<std::vector<int>>& ranges, int left, int right, bool expected)
	: _ranges{ranges}, _left{left}, _right{right}, _expected{expected} {};
	void print() const {
		std::cout << "Ranges: ";
		for (const std::vector<int>& rng : _ranges) { std::cout << "(" << rng.at(0) << "," << rng.at(1) << ") "; }
		std::cout << "Left:" << _left << " Right:" << _right << std::endl;
	}

	void test() const {
		Solution soln;
		print();
		bool actual{soln.isCovered(_ranges, _left, _right)};
		assert(_expected == actual);
	}
};

int main() {

	const std::vector<Testcase> testCases{
		Testcase({{1,2},{3,4},{5,6}}, 2, 5, true),
		Testcase({{1,10},{10,20}}, 21, 21, false),
		Testcase({{25,42},{7,14},{2,32},{25,28},{39,49},{1,50},{29,45},{18,47}}, 15, 38, true),
		Testcase({{6,29},{33,43},{7,50},{11,34},{24,26},{32,47}}, 2, 31, false),
		Testcase({{23,43},{12,17},{14,35},{13,20},{16,24},{6,18},{6,49},{6,29},{37,42},{22,42},{15,25},{3,20},{12,21},{21,38},{16,20},{7,22},{35,40},{38,39},{6,16},{2,15},{16,26},{5,18},
			{5,36},{5,47},{2,41},{1,19},{23,49},{31,32},{7,10},{33,50},{5,21},{33,43},{12,12},{10,50},{10,21},{7,20},{33,46},{19,39},{9,14},{10,35},{3,47}}, 21, 50, true),
	};
	for (const Testcase& tc : testCases) { tc.test(); }
}
