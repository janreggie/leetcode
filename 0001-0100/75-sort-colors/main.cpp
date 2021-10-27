#include <vector>

class Solution
{
public:
	void sortColors(std::vector<int>& nums)
	{
		std::vector<int> counts(3, 0);
		for (const int num : nums) {
			++counts[num];
		}

		size_t ind = 0;
		for (int ii = 0; ii < 3; ++ii) {
			while (counts[ii] > 0) {
				nums[ind] = ii;
				++ind;
				--counts[ii];
			}
		}
	}
};
