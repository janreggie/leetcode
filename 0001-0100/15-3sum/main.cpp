#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

class Solution {

	std::vector<int> _nums;
	std::vector<std::vector<int>> _answer;

public:
	std::vector<std::vector<int>> threeSum(const std::vector<int>& nums) {

		if (nums.size() < 3) { return {}; }
		if (nums.size() == 3) {
			if (nums.at(0) + nums.at(1) + nums.at(2) == 0) {
				return {{nums.at(0), nums.at(1), nums.at(2)}};
			}
			return {};
		}

		_nums = {};
		_answer = {};

		std::vector<int> sortedNums{nums};
		std::sort(sortedNums.begin(), sortedNums.end());
				
		// Trim "duplicate" nums
		// i.e., if a number occurs more than twice, remove the duplicates.
		//
		_nums.push_back(sortedNums.at(0));
		for (size_t ii{1}; ii < sortedNums.size()-1; ++ii) {

			if (sortedNums.at(ii) == sortedNums.at(ii-1) &&
					sortedNums.at(ii) == sortedNums.at(ii+1) &&
					sortedNums.at(ii) != 0) {
				continue;
			}
			_nums.push_back(sortedNums.at(ii));
		}
		_nums.push_back(sortedNums.at(sortedNums.size()-1));

		// Now, pull me a twoSum recursively...
		// 
		_answer = {};
		for (size_t ii{0}; ii < _nums.size()-2; ++ii) {

			const std::vector<std::pair<int,int>> twoSumPairs{twoSum(-_nums.at(ii), ii+1)};
			for (const std::pair<int,int>& ts : twoSumPairs) {
				addToAnswer({_nums.at(ii), ts.first, ts.second});
			}
		}
		return _answer;
	}

private:

	// Find twoSums of _nums[leftIndex:] that sum to target.
	//
	std::vector<std::pair<int,int>> twoSum(int target, size_t leftIndex) {

		std::vector<std::pair<int,int>> result;
		size_t left{leftIndex}, right{_nums.size()-1};

		while (left < right) {
			int sum{_nums.at(left)+_nums.at(right)};
			if (sum == target) {
				result.push_back({_nums.at(left), _nums.at(right)});
				++left;
				--right;
				continue;
			}
			if (sum < target) {
				++left;
			} else {
				--right;
			}
		}

		return result;
	}

	void addToAnswer(const std::vector<int>& triplet) {

		// It is guaranteed that _answer[ii][0] is sorted.
		//
		for (size_t ii{_answer.size()-1}; ii <= _answer.size(); --ii) {
			if (_answer.at(ii).at(0) != triplet.at(0)) { break; }
			if (_answer.at(ii) == triplet) { return; }
		}
		_answer.push_back(triplet);
	}
};

int main() {

	const std::vector<int> nums{1,2,-2,-1};
	Solution soln;
	const std::vector<std::vector<int>> result{soln.threeSum(nums)};

	for (const std::vector<int>& triplet : result) {

		for (const int term : triplet) { std::cout << term << " "; }
		std::cout << std::endl;
	}
}
