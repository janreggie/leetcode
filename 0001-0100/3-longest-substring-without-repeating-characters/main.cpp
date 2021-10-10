#include <algorithm>
#include <string>
#include <unordered_set>

class Solution
{
public:
	int lengthOfLongestSubstring(const std::string& s)
	{
		std::unordered_map<char, size_t> inds; // inds[c] = last index of c
		size_t a = 0, b = 0;
		size_t record = 0; // largest b-a

		// Now what is our loop condition?
		while (true) {
			while (b < s.size() && (inds.count(s.at(b)) == 0 || inds.at(s.at(b)) < a)) {
				inds[s.at(b)] = b;
				++b;
			}

			record = std::max(record, b - a);

			// At this point, either b == s.size() or s.at(b) in letters
			if (b == s.size()) {
				break;
			}
			a = inds[s.at(b)] + 1;
		}

		return record;
	}
};
