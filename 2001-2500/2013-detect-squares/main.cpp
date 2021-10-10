#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <utility>

class DetectSquares {

	std::vector<std::pair<int,int>> _points;
	std::unordered_map<int, std::set<size_t>> _abscissae;
	std::unordered_map<int, std::set<size_t>> _ordinates;

	// Counts the number of points `point` in `_points`
	size_t count_points(const std::pair<int,int>& point) {

		std::set<size_t> intersection;
		const int x = point.first, y = point.second;
		std::set_intersection(_abscissae[x].begin(), _abscissae[x].end(),
			_ordinates[y].begin(), _ordinates[y].end(),
			std::inserter(intersection, intersection.begin()));
		return intersection.size();
	}

public:
	DetectSquares() {
		// RAII works
	}

	void add(const std::vector<int>& point) {
		const int x = point.at(0), y = point.at(1);
		const size_t ind = _points.size();
		_points.push_back({x,y});
		_abscissae[x].insert(ind);
		_ordinates[y].insert(ind);

	}

	int count(const std::vector<int>& point) {

		int result = 0;
		const int x = point.at(0), y = point.at(1);

		for (const size_t ind : _ordinates[y]) {

			// _points[ind] and point lie in the same horizontal line...
			const std::pair<int,int>& p1 = _points.at(ind);
			const int x1 = p1.first;
			const int width = std::abs(x1 - x);
			if (width == 0) {
				continue;
			}

			result += (count_points({x1, y+width}) * count_points({x, y+width}));
			result += (count_points({x1, y-width}) * count_points({x, y-width}));
		}

		return result;
	}
};

size_t count_intersection(const std::pair<int,int>& pt,
		const std::unordered_map<int, std::set<size_t>>& xs,
		const std::unordered_map<int, std::set<size_t>>& ys) {
	
	const int x = pt.first, y = pt.second;

	// Omitted some error checking

	std::set<size_t> intersection;
	std::set_intersection(xs.at(x).begin(), xs.at(x).end(),
		ys.at(y).begin(), ys.at(y).end(),
		std::inserter(intersection, intersection.begin()));

	return intersection.size();
}

int main() {

	DetectSquares ds;
	ds.add({3,10});
	ds.add({11,2});
	ds.add({3,2});
	ds.count({11,10});
	ds.count({14,8});
	ds.add({11,2});
	ds.count({11,10});
}
