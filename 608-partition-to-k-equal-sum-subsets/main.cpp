#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
	std::vector<int> _nums;
	int _target;
	std::vector<int> _buckets;

public:
	bool canPartitionKSubsets(const std::vector<int>& nums, int k)
	{
		_nums = nums;
		std::sort(_nums.begin(), _nums.end(), std::greater<>());
		int total_sum = 0;
		for (const int num : _nums) {
			total_sum += num;
		}
		_target = total_sum / k;

		// Check if it is even possible to begin with
		if (total_sum % k != 0) {
			return false;
		}
		if (_nums.at(0) > _target) {
			return false;
		}

		_buckets = std::vector<int>(k);
		// WLOG: Put the first element at the zeroth bucket
		_buckets[0] += _nums.at(0);

		return iter(1);
	}

private:
	bool iter(size_t ind)
	{
		if (ind == _nums.size()) {
			return true;
		}

		const int to_add = _nums.at(ind);
		for (size_t bk = 0; bk < _buckets.size(); ++bk) {
			if (_buckets.at(bk) + to_add > _target) {
				continue;
			}
			_buckets.at(bk) += to_add;
			if (iter(ind + 1)) {
				return true;
			}
			_buckets.at(bk) -= to_add;
		}

		return false;
	}
	// Returns true if it is possible to divide descending nums
	// into groups each having sum `target`.
	//
	// This function is incorrect.
	bool iterOld(std::vector<int> nums, int target)
	{
		if (nums.size() == 0) {
			return true;
		}

		size_t ii = 0, jj = 1; // take nums[ii:jj]
		int sum = nums.at(0);

		while (sum != target && jj < nums.size()) {
			if (sum < target) {
				sum += nums.at(jj);
				++jj;
			} else {
				sum -= nums.at(ii);
				++ii;
			}
		}

		if (sum != target) {
			return false;
		}

		nums.erase(nums.begin() + ii, nums.begin() + jj);
		return iterOld(nums, target);
	}
};

struct Testcase
{
	const std::vector<int> _nums;
	const int _k;
	const bool _expected;

	friend std::ostream& operator<<(std::ostream& os, const Testcase& tc)
	{
		os << "Nums: { ";
		for (const int num : tc._nums) {
			os << num << ", ";
		}
		os << "}, k: " << tc._k << ", expected: " << (tc._expected ? "true" : "false");
		return os;
	}
};

int
main()
{
	const std::vector<Testcase> testcases{
		{ { 4, 3, 2, 3, 5, 2, 1 }, 4, true },
		{ { 1, 2, 3, 4 }, 3, false },
		{ { 1, 1, 1, 2, 2, 2 }, 3, true },
		{ { 10, 10, 8, 7, 6, 4, 4, 3, 2, 2 }, 4, true }
	};

	for (const Testcase& tc : testcases) {
		std::cout << "Testing " << tc << std::endl;
		Solution soln;
		const bool actual = soln.canPartitionKSubsets(tc._nums, tc._k);
		if (actual != tc._expected) {
			return 1;
		}
	}
}
