#include <string>
#include <vector>

class Solution
{
public:
	std::string longestPalindrome(const std::string& s)
	{
		// Base cases:
		if (s.size() <= 1) {
			return s;
		}

		size_t a = 0, l = 1; // longest palindrome will centre at a and be of length l
		if (s.at(0) == s.at(1)) {
			l = 2; //  If l is even, centre at [s[a:a+2]]
		}

		for (size_t ii = 1; ii < s.size() - 1; ++ii) {
			if (s.at(ii - 1) == s.at(ii + 1)) {
				size_t jj = 1; // jj being the distance from ii
					       // such that s[ii-jj:ii+jj+1] is a palindrome
				for (; jj <= ii && ii + jj < s.size(); ++jj) {
					if (s.at(ii - jj) != s.at(ii + jj)) {
						break;
					}
				}

				// At this point, jj is just beyond the threshold
				--jj;
				if (jj * 2 + 1 > l) {
					a = ii;
					l = jj * 2 + 1;
				}
			}

			if (s.at(ii) == s.at(ii + 1)) {
				size_t jj = 1; // jj being the distance from ii
					       // such that s[ii-jj:ii+jj+2] is a palindrome
				for (; jj <= ii && ii + jj + 1 < s.size(); ++jj) {
					if (s.at(ii - jj) != s.at(ii + jj + 1)) {
						break;
					}
				}
				--jj;
				if (jj * 2 + 2 > l) {
					a = ii;
					l = jj * 2 + 2;
				}
			}
		}

		// Now, create the output
		if (l % 2 == 0) {
			return s.substr(a + 1 - l / 2, l);
		}
		return s.substr(a - l / 2, l);
	}
};
