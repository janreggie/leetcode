#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class Solution
{

	std::vector<int> _nums;
	std::vector<std::vector<int>> _result;

public:
	std::vector<std::vector<int>> threeSum(const std::vector<int>& nums)
	{
		if (nums.size() < 3) {
			return {};
		}
		if (nums.size() == 3) {
			if (nums.at(0) + nums.at(1) + nums.at(2) == 0) {
				return { nums };
			}
			return {};
		}

		_nums = nums;
		std::sort(_nums.begin(), _nums.end());
		_result = {};

		for (size_t ii = 0; ii < _nums.size(); ++ii) {
			const int target = -_nums.at(ii);
			twoSum(ii + 1, _nums.size() - 1, target);
		}

		return _result;
	}

private:
	void twoSum(size_t i1, size_t i2, int target)
	{
		if (i1 >= i2) {
			return;
		}

		const int sum = _nums.at(i1) + _nums.at(i2);
		if (sum == target) {
			addToResult({ -target, _nums.at(i1), _nums.at(i2) });
			twoSum(i1 + 1, i2 - 1, target);
		} else if (sum < target) {
			twoSum(i1 + 1, i2, target);
		} else {
			twoSum(i1, i2 - 1, target);
		}
	}

	void addToResult(const std::vector<int>& toAdd)
	{
		for (auto it = _result.rbegin(); it != _result.rend(); ++it) {
			if ((*it)[0] < toAdd[0]) {
				break;
			}
			if ((*it) == toAdd) {
				return;
			}
		}

		_result.push_back(toAdd);
	}
};

int
main()
{

	const std::vector<int> nums{ 1, 2, -2, -1, -1 };
	Solution soln;
	const std::vector<std::vector<int>> result{ soln.threeSum(nums) };

	for (const std::vector<int>& triplet : result) {

		for (const int term : triplet) {
			std::cout << term << " ";
		}
		std::cout << std::endl;
	}
}
