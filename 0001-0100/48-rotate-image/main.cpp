#include <vector>

class Solution
{
public:
	void rotate(std::vector<std::vector<int>>& matrix)
	{
		const size_t n = matrix.size();
		// Rotate 90 degrees === Transpose from lower-left to upper-right, and then flip horizontally

		// First, we transpose from LL to UR
		for (size_t ii = 0; ii < n; ++ii) {
			for (size_t jj = 0; jj < ii; ++jj) {
				const int tmp = matrix[ii][jj];
				matrix[ii][jj] = matrix[jj][ii];
				matrix[jj][ii] = tmp;
			}
		}

		// Then, we flip
		for (size_t col = 0; col < n / 2; ++col) {
			for (size_t row = 0; row < n; ++row) {
				const int tmp = matrix[row][col];
				matrix[row][col] = matrix[row][n - col - 1];
				matrix[row][n - col - 1] = tmp;
			}
		}
	}
};
