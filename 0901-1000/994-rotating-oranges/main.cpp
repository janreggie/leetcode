#include <algorithm>
#include <vector>

class Solution
{
	std::vector<std::vector<int>> _grid;
	size_t _height;
	size_t _width;

public:
	int orangesRotting(const std::vector<std::vector<int>>& grid)
	{
		_grid = grid;
		_height = grid.size();
		_width = grid.at(0).size();

		// Look for infected oranges
		for (size_t x = 0; x < _width; ++x) {
			for (size_t y = 0; y < _height; ++y) {
				if (_grid.at(y).at(x) == 2) {
					iter(x, y, 2);
				}
			}
		}

		// Finally, scan through the entire grid.
		// If there are any 1's, that means there's unaffected stuff.
		int max_minutes = 2;
		for (size_t x = 0; x < _width; ++x) {
			for (size_t y = 0; y < _height; ++y) {
				const int current = _grid.at(y).at(x);
				if (current == 1) {
					return -1;
				}
				max_minutes = std::max(max_minutes, current);
			}
		}

		return max_minutes - 2; // Padded by 2 during iter
	}

private:
	void iter(size_t x, size_t y, int v)
	{
		const int current = _grid.at(y).at(x);
		if (current == 0) {
			return;
		}
		// There's probably a rotten orange nearby.
		// Don't duplicate efforts.
		if (current > 1 && current < v) {
			return;
		}

		_grid.at(y).at(x) = v;

		if (x > 0) {
			iter(x - 1, y, v + 1);
		}
		if (x < _width - 1) {
			iter(x + 1, y, v + 1);
		}
		if (y > 0) {
			iter(x, y - 1, v + 1);
		}
		if (y < _height - 1) {
			iter(x, y + 1, v + 1);
		}
	}
};
