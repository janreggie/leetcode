#include <iostream>
#include <unordered_set>
#include <vector>

// C++ template to print vector container elements
template<typename T>
std::ostream&
operator<<(std::ostream& os, const std::vector<T>& v)
{
	os << "[";
	for (size_t i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "]";
	return os;
}

class Solution
{
	static constexpr int NOT_VISITED = 0,
			     TO_VISIT = 1,
			     HAS_VISITED = 2;
	std::vector<int> _statuses;
	std::vector<std::unordered_set<int>> _graph;

public:
	bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites)
	{
		_statuses = std::vector<int>(numCourses, NOT_VISITED);
		_graph = std::vector<std::unordered_set<int>>(numCourses);
		for (const std::vector<int>& prereq : prerequisites) {
			_graph[prereq[1]].insert(prereq[0]);
		}

		for (int course = 0; course < numCourses; ++course) {
			const int state = _statuses[course];
			if (state == HAS_VISITED) {
				continue;
			}
			if (state != NOT_VISITED) {
				return false; // This shouldn't happen, but it did
			}

			_statuses[course] = TO_VISIT;
			const bool result = visit(course);
			if (!result) {
				return false;
			}
		}

		return true;
	}

private:
	// returns true if successful and no loops
	bool visit(int course)
	{
		for (const int child : _graph[course]) {
			const int state = _statuses[child];
			switch (state) {
				case HAS_VISITED:
					continue;
				case NOT_VISITED: {
					_statuses[child] = TO_VISIT;
					const bool result = visit(child);
					if (!result) {
						return false;
					}
					break;
				}
				default:
					return false;
			}
		}
		_statuses[course] = HAS_VISITED;
		return true;
	}
};

struct Testcase
{
	const int _numCourses;
	const std::vector<std::vector<int>> _prerequisites;
	const bool _expected;

	friend std::ostream& operator<<(std::ostream& os, const Testcase& tc)
	{
		os << "numCourses: " << tc._numCourses << ", "
		   << "prerequisites: " << tc._prerequisites << ", "
		   << "expected: " << (tc._expected ? "true" : "false");
		return os;
	}
};

int
main()
{
	const std::vector<Testcase> testcases{
		{ 2, { { 1, 0 } }, true },
		{ 2, { { 1, 0 }, { 0, 1 } }, false },
		{ 4, { { 2, 0 }, { 1, 0 }, { 3, 1 }, { 3, 2 }, { 1, 3 } }, false }
	};
	for (const Testcase& tc : testcases) {
		std::cout << "Testing " << tc << std::endl;
		Solution soln;
		const bool actual = soln.canFinish(tc._numCourses, tc._prerequisites);
		if (actual != tc._expected) {
			return 1;
		}
	}
}
