#include <vector>
#include <iostream>

class Solution {
public:
	int rob(const std::vector<int>& nums) {

		const size_t length{nums.size()};
		if (length == 1) { return nums.at(0); }
		if (length == 2) {
			return nums.at(0) > nums.at(1) ? nums.at(0) : nums.at(1);
		}

		const int moneyWithoutFirst{robLinear(std::vector<int>(nums.begin()+1, nums.end()))};
		const int moneyWithoutLast{robLinear(std::vector<int>(nums.begin(), nums.end()-1))};
		return moneyWithoutFirst > moneyWithoutLast ? moneyWithoutFirst : moneyWithoutLast;
	}

	int robLinear(const std::vector<int>& nums) {

		const size_t length{nums.size()};
		if (length == 1) { return nums.at(0); }
		if (length == 2) {
			return nums.at(0) > nums.at(1) ? nums.at(0) : nums.at(1);
		}

		// accumulated[ii] = accumulated[ii+2] + nums[ii] or 
		//                   accumulated[ii+3] + nums[ii],
		// whichever is greater
		std::vector<int> accumulated(nums);
		accumulated[length-3] += nums.at(length-1);
		for (size_t ii{length-4}; ii < length; --ii) {
			accumulated[ii] += (accumulated[ii+2] > accumulated[ii+3] ?
					    accumulated[ii+2] :
					    accumulated[ii+3]);
		}

		return accumulated[0] > accumulated[1] ? accumulated[0] : accumulated[1];
	}
};

int main() {

	const std::vector<int> houses{5,6,131,4,6,696,7,420};
	Solution soln;
	std::cout << soln.rob(houses) << std::endl;
}
