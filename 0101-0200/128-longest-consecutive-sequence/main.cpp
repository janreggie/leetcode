#include <algorithm>
#include <unordered_set>
#include <vector>

class Solution
{
public:
	int longestConsecutive(const std::vector<int>& nums)
	{
		if (nums.size() == 0) {
			return 0;
		}

		std::unordered_set<int> numbers;
		for (const int num : nums) {
			numbers.insert(num);
		}

		// starts are numbers that are also beginnings of some continuous sequence
		std::unordered_set<int> starts;
		for (const int num : nums) {
			if (numbers.count(num - 1) == 0 && numbers.count(num + 1) != 0) {
				starts.insert(num);
			}
		}

		int record = 1; // There will alsways be a seq. of len. 1
		for (const int start : starts) {
			int count = 0;
			for (int num = start; numbers.count(num) != 0; ++num) {
				++count;
			}
			record = std::max(record, count);
		}

		return record;
	}
};
