#include <cstdlib>
#include <string>
#include <vector>

class Solution {
public:
	int minDistance(const std::string& word1, const std::string& word2) {
		const size_t n1 = word1.size(), n2 = word2.length();
		if (n1 == 0 || n2 == 0) {
			return std::max(n1, n2);
		}

		// dp[i1][i2] == minDistance(word1[:i1+1], word2[:i2+2])
		std::vector<std::vector<size_t>> dp(n1, std::vector<size_t>(n2, 0));
		if (word1[0] != word2[0]) {
			dp[0][0] = 1;
		}

		// Initialize zeroth row and zeroth column
		bool has_considered = word1[0] == word2[0]; // check if word1[0] or word2[0] has alr. been used
		for (size_t ii = 1; ii < n1; ++ii) {
			dp[ii][0] = dp[ii-1][0] + (has_considered || word1[ii] != word2[0] ? 1 : 0);
			has_considered |= word1[ii] == word2[0];
		}
		has_considered = word1[0] == word2[0];
		for (size_t ii = 1; ii < n2; ++ii) {
			dp[0][ii] = dp[0][ii-1] + (has_considered || word2[ii] != word1[0] ? 1 : 0);
			has_considered |= word2[ii] == word1[0];
		}

		// Note: minDistance(abcdef, azced)
		// == min(minDistance(abcde, azced) + minDistance(abcdef, azce) + minDistance(abcde, azce))
		//    + (does next one incur a cost ? 1 : 0).

		for (size_t ii = 1; ii < n1; ++ii) {
			for (size_t jj = 1; jj < n2; ++jj) {
				dp[ii][jj] = min3(dp[ii-1][jj] + 1,
					dp[ii][jj-1] + 1,
					dp[ii-1][jj-1] + (word1[ii] == word2[jj] ? 0 : 1));
			}
		}

		return dp[n1-1][n2-1];
	}

private:
	static int min3(int a, int b, int c) {
		return std::min(std::min(a, b), c);
	}
};
