#include <bits/stdc++.h>
using namespace std;

using Point = pair<size_t,size_t>;

// For hashing a Point
struct pair_hash {
    size_t operator () (const Point& p) const {
		return p.first*31+p.second;
    }
};

class Solution {

	size_t _height, _width;
	vector<vector<int>> _grid;
	vector<vector<int>> _distances;   // a way to check the distances easily
	queue<Point> _toVisit;  // pair<coordinates,distance>

public:
	int shortestPathBinaryMatrix(const vector<vector<int>>& grid) {

		_height = grid.size();
		_width = grid[0].size();
		_grid = vector<vector<int>>(grid);
		if (_grid[0][0] != 0 || _grid[_height-1][_width-1] != 0) { return -1; }

		_distances = vector<vector<int>>(_height, vector<int>(_width, 0));
		_distances[0][0] = 1;
		_toVisit = queue<Point>();
		_toVisit.emplace(0,0);

		const Point target(_height-1, _width-1);
		while (!_toVisit.empty()) {
			const Point current(_toVisit.front());
			_toVisit.pop();
			if (current == target) { return _distances[current.first][current.second]; }
			addNeighbors(current);
		}

		return -1;
	}

	void addNeighbors(const Point& current) {

		const size_t fst{current.first}, snd{current.second}; // coordinates for Point
		const int nextDistance{_distances[fst][snd]+1};

		if (snd != 0) { checkAndAppend(fst, snd-1, nextDistance); };
		if (snd != _width-1) { checkAndAppend(fst, snd+1, nextDistance); };

		if (fst != 0) {
			checkAndAppend(fst-1, snd, nextDistance);
			if (snd != 0) { checkAndAppend(fst-1, snd-1, nextDistance); };
			if (snd != _width-1) { checkAndAppend(fst-1, snd+1, nextDistance); };
		}

		if (fst != _height-1) {
			checkAndAppend(fst+1, snd, nextDistance);
			if (snd != 0) { checkAndAppend(fst+1, snd-1, nextDistance); };
			if (snd != _width-1) { checkAndAppend(fst+1, snd+1, nextDistance); };
		}
	}

	void checkAndAppend(size_t fst, size_t snd, int dist) {

		if (_grid[fst][snd] != 0) { return; }
		if (_distances[fst][snd] != 0) { return; }
		_toVisit.emplace(fst,snd);
		_distances[fst][snd] = dist;
	}

};

int main() {

	const vector<vector<int>> grid{
		{0,0,0},
		{1,1,0},
		{1,1,0}
	};
	Solution soln;
	cout << soln.shortestPathBinaryMatrix(grid) << endl;
}
