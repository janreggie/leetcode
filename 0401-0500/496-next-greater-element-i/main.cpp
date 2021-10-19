#include <stack>
#include <unordered_map>
#include <vector>

class Solution
{
public:
	std::vector<int> nextGreaterElement(const std::vector<int>& nums1, const std::vector<int>& nums2)
	{
		std::unordered_map<int, int> next_greaters;
		std::stack<int> waiting;
		for (const int elem : nums2) {
			while (!waiting.empty() && waiting.top() < elem) {
				next_greaters[waiting.top()] = elem;
				waiting.pop();
			}
			waiting.push(elem);
		}

		std::vector<int> result(nums1.size(), -1);
		for (size_t ii = 0; ii < nums1.size(); ++ii) {
			const int n = nums1.at(ii);
			if (next_greaters.count(n) != 0) {
				result.at(ii) = next_greaters.at(n);
			}
		}

		return result;
	}
};
