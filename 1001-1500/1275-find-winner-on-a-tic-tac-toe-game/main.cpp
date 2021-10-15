#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
	std::string tictactoe(const std::vector<std::vector<int>>& moves) {

		std::vector<std::vector<char>> grid(3, std::vector<char>(3, 0));
		for (size_t ii = 0; ii < moves.size(); ++ii) {
			const char to_add = ii % 2 == 0 ? 'A' : 'B';
			const auto& move = moves.at(ii);
			const int x = move.at(0), y = move.at(1);
			grid[x][y] = to_add;
		}

		// Check who won...
		for (size_t row = 0; row < 3; ++row) {
			if (grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2] && grid[row][0] != 0) {
				return std::string(1, grid[row][0]);
			}
		}
		for (size_t col = 0; col < 3; ++col) {
			if (grid[0][col] == grid[1][col] && grid[1][col] == grid[2][col] && grid[0][col] != 0) {
				return std::string(1, grid[0][col]);
			}
		}
		if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != 0) {
			return std::string(1, grid[0][0]);
		}
		if (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && grid[2][0] != 0) {
			return std::string(1, grid[2][0]);
		}

		// And if none matched...
		if (moves.size() == 9) {
			return "Draw";
		}
		return "Pending";
	}
};

struct Testcase {
	const std::vector<std::vector<int>> _moves;
	const std::string _expected;
	Testcase(const std::vector<std::vector<int>>& moves, const std::string& expected)
		: _moves{moves}, _expected{expected} {};
	
	std::string details() const {
		std::string result;
		result += "{ ";
		for (const auto& move : _moves) {
			result += "(" + std::to_string(move.at(0)) + "," + std::to_string(move.at(1)) + ")" + ", ";
		}
		result += "} => " + _expected;
		return result;
	}
};

int main() {

	const std::vector<Testcase> cases{
		Testcase({{0,0}, {2,0}, {1,1}, {2,1}, {2,2}}, "A"),
		Testcase({{0,0}, {1,1}, {0,1}, {0,2}, {1,0}, {2,0}}, "B"),
		Testcase({{0,0}, {1,1}, {2,0}, {1,0}, {1,2}, {2,1}, {0,1}, {0,2}, {2,2}}, "Draw"),
		Testcase({{0,0}, {1,1}}, "Pending")
	};

	Solution soln;
	for (const Testcase& tc : cases) {
		std::cout << "Testing " << tc.details() << std::endl;
		const std::string actual = soln.tictactoe(tc._moves);
		std::cout << "Actual: " << actual << std::endl;
		if (tc._expected != actual) {
			return 1;
		}
	}
}
