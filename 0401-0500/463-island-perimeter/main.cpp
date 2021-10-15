#include <vector>

class Solution
{
public:
	int islandPerimeter(const std::vector<std::vector<int>>& grid)
	{
		const size_t height = grid.size(), width = grid[0].size();
		int result = 0;

		for (size_t ii = 0; ii < height; ++ii) {
			for (size_t jj = 0; jj < width; ++jj) {
				int contrib = (grid[ii][jj] == 1 ? 4 : 0);
				if (contrib == 0) {
					continue;
				}

				if (ii >= 1 && grid[ii - 1][jj] == 1) {
					--contrib;
				}
				if (ii < height - 1 && grid[ii + 1][jj] == 1) {
					--contrib;
				}
				if (jj >= 1 && grid[ii][jj - 1] == 1) {
					--contrib;
				}
				if (jj < width - 1 && grid[ii][jj + 1] == 1) {
					--contrib;
				}

				result += contrib;
			}
		}

		return result;
	}
};

int
main()
{
	// Do nothing
}
