#include <utility>
#include <vector>

class Solution
{
	std::vector<int> _nums;

public:
	int majorityElement(const std::vector<int>& nums)
	{
		_nums = nums;
		return iter(0, _nums.size()).second;
	}

private:
	std::pair<bool, int> iter(size_t ii, size_t jj)
	{
		// Base case: len <= 3
		const size_t len = jj - ii;
		if (len == 1) {
			return { true, _nums[ii] };
		}
		if (len == 2) {
			if (_nums[ii] == _nums[ii + 1]) {
				return { true, _nums[ii] };
			}
			return { false, 0 };
		}
		if (len == 3) {
			int a = _nums[ii], b = _nums[ii + 1], c = _nums[ii + 2];
			if (a == b || a == c) {
				return { true, a };
			}
			if (b == c) {
				return { true, b };
			}
			return { false, 0 };
		}

		// Recursive case: this is a D&Q problem!
		const auto left = iter(ii, (ii + jj) / 2);
		const auto right = iter((ii + jj) / 2, jj);
		if (left.first) {
			return left;
		}
		return right;
	}
};
