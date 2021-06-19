#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

class Solution {

	static constexpr long _MODBOUND{1000000007};

public:
	int kInversePairs(int n, int k) {

		if (k < 0 || k > (n*(n-1)/2)) { return 0; }

		if (k == 0) { return 1; }
		if (k == 1) { return (n-1); }
		if (k == 2) { return (n-1)*n/2 - 1; }

		const std::vector<long> counts{generateInverseCounts((size_t)n, (size_t)k)};
		return (int)(counts.at(k) % _MODBOUND);
	}

	// generateInverseCounts creates an array which determines how many permutations are there of length n with some number of inverse pairs.
	// GIC(1) = {1}
	// GIC(2) = {1,1}
	// GIC(3) = {1,2,2,1}
	// GIC(4) = {1,3,5,6,5,3,1}
	std::vector<long> generateInverseCounts(size_t n, size_t k = 0) {

		// Base cases
		//
		if (n == 0) { return {}; }
		if (n == 1) { return {1}; }
		if (n == 2) { return {1,1}; }
		if (n == 3) { return {1,2,2,1}; }

		// Now, generate the current array from the previous one
		//
		const std::vector<long> prev{generateInverseCounts(n-1, k)};
		const size_t expectedLength{n*(n-1)/2 + 1}; // length if we weren't bounded by k
		const size_t actualLength{k == 0 ? expectedLength : std::min(expectedLength, k+1)};
		std::vector<long> result(actualLength, 0);

		// Populate first half of the result
		// First, populate the first n items
		//
		result.at(0) = 1;
		for (size_t ii{1}; ii < n && ii < actualLength; ++ii) {
			result.at(ii) = (result.at(ii-1) + prev.at(ii)) % _MODBOUND;
			if (result.at(ii) < 0) {
				result.at(ii) += _MODBOUND;
			}
		}
		// Next, populate the rest of the first half
		//
		for (size_t ii{n}; ii < (expectedLength+1)/2 && ii < actualLength; ++ii) {
			result.at(ii) = (result.at(ii-1)+prev.at(ii)-prev.at(ii-n)) % _MODBOUND;
			if (result.at(ii) < 0) {
				result.at(ii) += _MODBOUND;
			}
		}

		// Populate the rest of result using said first half
		//
		for (size_t ii{(expectedLength+1)/2}; ii < actualLength; ++ii) {
			result.at(ii) = result.at(expectedLength-ii-1);
			if (result.at(ii) < 0) {
				result.at(ii) += _MODBOUND;
			}
		}

		return result;
	}
};

struct Testcase{
	const int _n;
	const int _k;
	const int _expected;
	void info() const {
		std::cout << "n:" << _n << ", k:" << _k << ", expects:" << _expected << std::endl;
	}

	void test() const {
		info();
		Solution soln;
		int actual{soln.kInversePairs(_n,_k)};
		std::cout << "actual:" << actual << std::endl;
		assert(_expected==actual);
	}
};

int main() {

	const std::vector<Testcase> testcases{
		{3,0,1},
		{3,1,2},
		{4,0,1},
		{4,1,3},
	 	{4,2,5},
	 	{4,3,6},
	 	{4,4,5},
	 	{4,5,3},
	 	{4,6,1},
	 	{5,5,22},
	 	{5,11,0},
	 	{10,55,0},
	 	{1000,3,166665500},
		{1000,1000,663677020},
	};

	for (const Testcase& tc : testcases) { tc.test(); }

	Solution soln;
	for (size_t ii{0}; ii < 10; ++ii) {
		std::cout << std::setw(2) << ii;
		const std::vector<long> counts{soln.generateInverseCounts(ii)};
		for (const int cc : counts) { std::cout << std::setw(7) << cc; }
		std::cout << std::endl;
	}
}
