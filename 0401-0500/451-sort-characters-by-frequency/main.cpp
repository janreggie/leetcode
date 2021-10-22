#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:
	std::string frequencySort(const std::string& s)
	{
		std::unordered_map<char, size_t> char_counts;
		for (const char c : s) {
			++char_counts[c];
		}

		std::vector<std::pair<char, size_t>> sorted_counts;
		for (const auto& p : char_counts) {
			sorted_counts.push_back(p);
		}
		std::sort(sorted_counts.begin(), sorted_counts.end(), [](auto& l, auto& r) { return l.second > r.second; });

		std::string result;
		for (const auto& p : sorted_counts) {
			result += std::string(p.second, p.first);
		}
		return result;
	}
};
