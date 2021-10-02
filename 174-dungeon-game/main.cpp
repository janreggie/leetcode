#include <vector>

class Solution
{
public:
	int calculateMinimumHP(const std::vector<std::vector<int>>& dungeon)
	{
		const size_t m = dungeon[0].size(), n = dungeon.size();
		std::vector<std::vector<int>> dp(n, std::vector<int>(m));

		// Fill in lower right corner, and then bottom row + rightmost col
		dp[n - 1][m - 1] = 1 - std::min(0, dungeon[n - 1][m - 1]);
		for (size_t jj = m - 2; jj < m; --jj) {
			dp[n - 1][jj] = std::max(1, dp[n - 1][jj + 1] - dungeon[n - 1][jj]);
		}
		for (size_t ii = n - 2; ii < n; --ii) {
			dp[ii][m - 1] = std::max(1, dp[ii + 1][m - 1] - dungeon[ii][m - 1]);
		}

		// Then, the rest of the grid
		for (size_t ii = n - 2; ii < n; --ii) {
			for (size_t jj = m - 2; jj < m; --jj) {
				dp[ii][jj] = std::max(1, std::min(dp[ii + 1][jj], dp[ii][jj + 1]) - dungeon[ii][jj]);
			}
		}

		return dp[0][0];
	}
};
