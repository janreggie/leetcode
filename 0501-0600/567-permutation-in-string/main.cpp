#include <string>
#include <vector>

class Solution {
public:
	bool checkInclusion(const std::string& s1, const std::string& s2) {
		const size_t n1 = s1.size(), n2 = s2.size();
		if (n1 > n2) { return false; }

		// to_find is the character counts of s1
		std::vector<size_t> to_find(26);
		for (size_t ii = 0; ii < n1; ++ii) {
			++to_find[s1[ii]-'a'];
		}

		// counts[ii] return the character counts of s2[ii:ii+n1].
		//
		std::vector<std::vector<size_t>> counts(n2-n1+1, std::vector<size_t>(26));

		for (size_t ii = 0; ii < n1; ++ii) {  // Initialize zeroth element of counts
			++counts[0][s2[ii]-'a'];
		}
		if (counts[0] == to_find) { return true; }

		for (size_t ii = 1; ii < n2-n1+1; ++ii) {  // And initialize the rest...
			const char prev_char = s2.at(ii-1), next_char = s2.at(ii-1+n1);

			counts[ii] = counts[ii-1];
			--counts[ii][prev_char-'a'];
			++counts[ii][next_char-'a'];

			if (counts[ii] == to_find) { return true; }
		}

		return false;
	}

};
