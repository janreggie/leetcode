#include <vector>

class Solution
{
public:
	std::vector<int> findDuplicates(std::vector<int>& nums)
	{
		int n = nums.size();

		for (int ii = 0; ii < n; ++ii) {
			while (nums[ii] != (ii + 1)) {
				const int v = nums[ii];
				nums[ii] = nums[v - 1];
				nums[v - 1] = v;
				if (v == nums[ii]) {
					break;
				}
			}
		}

		std::vector<int> result;
		for (int ii = 0; ii < n; ++ii) {
			if (nums[ii] != ii + 1) {
				result.push_back(nums[ii]);
			}
		}

		return result;
	}
};
