#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(const vector<vector<int>>& grid) {

		vector<vector<bool>> visited(grid.size());
		for (size_t ii{0}; ii < grid.size(); ++ii) {
			visited[ii] = vector<bool>(grid[0].size());
			for (size_t jj{0}; jj < grid[0].size(); ++jj) {
				visited[ii][jj] = (grid[ii][jj] == 1);
			}
		}

		int record{0};
		for (size_t ii{0}; ii < grid.size(); ++ii) {
			for (size_t jj{0}; jj < grid[0].size(); ++jj) {
				record = max(record, areaAt(visited, ii, jj));
			}
		}

		return record;
    }

	int areaAt(vector<vector<bool>>& visited, size_t ii, size_t jj) {
		// Do the needful, sir.
		if (ii >= visited.size() || jj >= visited[0].size()) { return 0; }
		if (!visited[ii][jj]) { return 0; }

		visited[ii][jj] = false;
		return 1 + areaAt(visited, ii, jj-1) + areaAt(visited, ii, jj+1) + areaAt(visited, ii-1, jj) + areaAt(visited, ii+1, jj);
	}

};

int main() {

	const vector<vector<int>> grid{
		{0,0,1,0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,1,1,0,1,0,0,0,0,0,0,0,0},
		{0,1,0,0,1,1,0,0,1,0,1,0,0},
		{0,1,0,0,1,1,0,0,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0}};
	Solution soln;
	cout << soln.maxAreaOfIsland(grid) << endl;
}
