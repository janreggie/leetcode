#include <string>

class Solution
{
public:
	std::string breakPalindrome(const std::string& palindrome)
	{
		const size_t n = palindrome.length();
		if (n <= 1) {
			return "";
		}

		size_t ind = 0; // lowest ind such that palindrome[ind] != 'a'
		for (; ind < (n + 1) / 2; ++ind) {
			if (palindrome.at(ind) != 'a') {
				break;
			}
		}

		std::string result(palindrome);
		if (result.at(ind) != 'a' && !(n % 2 == 1 && ind == n / 2)) {
			result.at(ind) = 'a';
		} else {
			result.at(result.length() - 1) = 'b';
		}

		return result;
	}
};
