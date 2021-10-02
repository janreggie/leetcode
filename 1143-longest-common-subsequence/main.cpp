#include <string>
#include <vector>

class Solution
{
public:
	int longestCommonSubsequence(const std::string& text1, const std::string& text2)
	{
		size_t n1 = text1.length(), n2 = text2.length();
		std::vector<std::vector<int>> dp(n1, std::vector<int>(n2, 0)); // dp[i][j] = LCS(text1[:i+1], text2[:j+1])

		// Populate zeroth row and col
		if (text1.at(0) == text2.at(0)) {
			dp[0][0] = 1;
		}
		for (size_t ii = 1; ii < n1; ++ii) {
			if (text1.at(ii) == text2.at(0)) {
				dp[ii][0] = 1;
			} else {
				dp[ii][0] = dp[ii - 1][0];
			}
		}
		for (size_t jj = 1; jj < n2; ++jj) {
			if (text2.at(jj) == text1.at(0)) {
				dp[0][jj] = 1;
			} else {
				dp[0][jj] = dp[0][jj - 1];
			}
		}

		// Now, for the rest of the grid
		for (size_t ii = 1; ii < n1; ++ii) {
			for (size_t jj = 1; jj < n2; ++jj) {
				dp[ii][jj] = std::max(dp[ii - 1][jj], dp[ii][jj - 1]);
				if (text1.at(ii) == text2.at(jj)) {
					dp[ii][jj] = std::max(dp[ii][jj], dp[ii - 1][jj - 1] + 1);
				}
			}
		}

		return dp[n1 - 1][n2 - 1];
	}
};
