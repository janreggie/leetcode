#include <vector>
#include <utility>

class Solution {
public:
	int findMaxConsecutiveOnes(const std::vector<int>& nums) {
		int record = 0;
		int current_streak = 0;
		bool at_one_range = false;

		for (size_t ii = 0; ii < nums.size(); ++ii) {
			int x = nums.at(ii);
			if (x == 1) {
				at_one_range = true;
				++current_streak;
				record = std::max(record, current_streak);
			} else {
				at_one_range = false;
				current_streak = 0;
			}
		}

		return record;
	}
};
