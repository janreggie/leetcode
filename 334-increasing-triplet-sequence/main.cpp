#include <iostream>
#include <vector>

class Solution
{
public:
	bool increasingTriplet(const std::vector<int>& nums)
	{
		const size_t len = nums.size();
		if (len < 3) {
			return false;
		}
		if (len == 3) {
			return nums[0] < nums[1] && nums[1] < nums[2];
		}

		// Let us look for two indices i, i+1 such that nums[i] < nums[i+1]
		size_t i = 0;
		while (i < len - 1) {
			if (nums.at(i) < nums.at(i + 1)) {
				break;
			}
			++i;
		}
		if (i == len - 1) {
			return false;
		}

		int a1 = nums[i], a2 = nums[i + 1];
		int h = a1; // placeholder for number smaller than a1

		// Now, let's go through the rest of the array, looking for a consecutive pair.
		// If this pair is less than (a1,a2), update the pair.
		// If it's greater than a2, we found a winner.
		for (; i < len - 1; ++i) {
			if (nums.at(i) > a2) {
				return true;
			}
			if (nums.at(i) < h) {
				h = nums.at(i);
			} else if (h < nums.at(i) && nums.at(i) < a2) {
				a1 = h;
				a2 = nums.at(i);
				continue;
			}
		}

		// Final check
		return a2 < nums.at(len - 1);
	}
};

int
main()
{
	const std::vector<int> nums{ 1, 5, 0, 4, 1, 3 };
	Solution soln;
	std::cout << soln.increasingTriplet(nums) << std::endl;
}