#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

typedef std::pair<int, std::pair<size_t, size_t>> pis;

class Solution
{
public:
	int kthSmallest(const std::vector<std::vector<int>>& matrix, int k)
	{
		const size_t n = matrix.size();

		// Store values, where first == value in matrix, second == (row, col).
		auto comp = [](const pis& p1, const pis& p2) { return p1.first > p2.first; };
		std::priority_queue<pis, std::vector<pis>, decltype(comp)> pq(comp);

		// Initial values
		for (size_t ii = 0; ii < n; ++ii) {
			pq.push({ matrix[ii][0], { ii, 0 } });
		}

		for (int ii = 0; ii < k - 1; ++ii) {
			const auto top = pq.top();
			pq.pop();

			const size_t row = top.second.first, col = top.second.second;
			if (col >= n - 1) {
				continue;
			}
			pq.push({ matrix[row][col + 1], { row, col + 1 } });
		}

		return pq.top().first;
	}
};

int
main()
{
	const std::vector<std::vector<int>> matrix{
		{ 1, 2 },
		{ 1, 3 }
	};
	const int k = 4;
	Solution soln;
	std::cout << soln.kthSmallest(matrix, k) << std::endl;
}
