#include <cassert>
#include <iostream>
#include <vector>

using matrix = std::vector<std::vector<int>>;

class Solution {

	size_t _width;
	size_t _height;

public:
	int largestMagicSquare(const matrix& grid) {

		_width = grid.at(0).size();
		_height = grid.size();
		if (_width == 1 || _height == 1) { return 1; }

		matrix nextHor(_height, std::vector<int>(_width-1));
		for (size_t row{0}; row<_height; ++row) {
			for (size_t col{0}; col<_width-1; ++col) {
				nextHor[row][col] = grid.at(row).at(col) + grid.at(row).at(col+1);
			}
		}

		matrix nextVer(_height-1, std::vector<int>(_width));
		for (size_t row{0}; row<_height-1; ++row) {
			for (size_t col{0}; col<_width; ++col) {
				nextVer[row][col] = grid.at(row).at(col) + grid.at(row+1).at(col);
			}
		}

		matrix nextDia1(_height-1, std::vector<int>(_width-1));
		for (size_t row{0}; row<_height-1; ++row) {
			for (size_t col{0}; col<_width-1; ++col) {
				nextDia1[row][col] = grid.at(row).at(col) + grid.at(row+1).at(col+1);
			}
		}

		matrix nextDia2(_height-1, std::vector<int>(_width-1));
		for (size_t row{0}; row<_height-1; ++row) {
			for (size_t col{0}; col<_width-1; ++col) {
				nextDia2[row][col] = grid.at(row).at(col+1) + grid.at(row+1).at(col);
			}
		}

		const int result{evaluate(grid, grid, grid, grid, nextHor, nextVer, nextDia1, nextDia2, 2)};
		if (result == 0) { return 1; }
		return result;
	}

private:
	// Hor: sweep horizontally, Ver: sweep vertically,
	// Dia1: diagonally southeast, Dia2: diagonally southwest
	//
	int evaluate(const matrix& prevHor, const matrix& prevVer, const matrix& prevDia1, const matrix& prevDia2,
			const matrix& nextHor, const matrix& nextVer, const matrix& nextDia1, const matrix& nextDia2,
			size_t k) {
		
		// std::cout << "At k=" << k << std::endl;
		// std::cout << "nextHor:\n"; printMatrix(nextHor);
		// std::cout << "nextVer:\n"; printMatrix(nextVer);
		// std::cout << "nextDia1:\n"; printMatrix(nextDia1);
		// std::cout << "nextDia2:\n"; printMatrix(nextDia2);

		// There is no point if next is empty
		//
		if (nextHor.at(0).size() == 0 || nextVer.size() == 0) {
			return 0;
		}

		// Now, check if we have *something* in our next's.
		//
		bool kIsViable{false}; // There *is* a kxk Magic Square
		for (size_t ii{0}; ii < _height-k+1; ++ii) {

			if (kIsViable) { break; }
			for (size_t jj{0}; jj < _width-k+1; ++jj) {

				if (kIsViable) { break; }
				const int expect{nextHor.at(ii).at(jj)};
				bool isOkay{true}; // a kxk magic square with content *expect* exists.

				// Check horizontals
				for (size_t kk{0}; kk < k; ++kk) {
					if (nextHor.at(ii+kk).at(jj) != expect) {
						isOkay = false;
						break;
					}
				}
				if (!isOkay) { continue; }

				// Check verticals
				for (size_t kk{0}; kk < k; ++kk) {
					if (nextVer.at(ii).at(jj+kk) != expect) {
						isOkay = false;
						break;
					}
				}
				if (!isOkay) { continue; }

				// Check diagonals
				if (nextDia1.at(ii).at(jj) != expect || nextDia2.at(ii).at(jj) != expect) {
					continue;
				}

				// If we made it here...
				kIsViable = true;
			}
		}

		const int nextAnswer{evaluate(nextHor, nextVer, nextDia1, nextDia2,
			iterate(prevHor,nextHor,0), iterate(prevVer,nextVer,1), iterate(prevDia1,nextDia1,2), iterate(prevDia2,nextDia2,3), k+1)};
		if (kIsViable) {
			return ((int)k > nextAnswer ? (int)k : nextAnswer);
		}
		return nextAnswer;
	}

	// direction: 0 for horizontal, 1 for vertical, 2 for dia1, 3 for dia2
	//
	matrix iterate(const matrix& prev, const matrix& next, int direction) {

		if (direction == 0) { 

			matrix result(next.size(), std::vector<int>(next.at(0).size()-1));
			for (size_t row{0}; row < result.size(); ++row) {
				for (size_t col{0}; col < result.at(0).size(); ++col) {
					result[row][col] = next.at(row).at(col) + next.at(row).at(col+1) - prev.at(row).at(col+1);
				}
			}
			return result;
		}

		if (direction == 1) {

			matrix result(next.size()-1, std::vector<int>(next.at(0).size()));
			for (size_t row{0}; row < result.size(); ++row) {
				for (size_t col{0}; col < result.at(0).size(); ++col) {
					result[row][col] = next.at(row).at(col) + next.at(row+1).at(col) - prev.at(row+1).at(col);
				}
			}
			return result;
		}

		if (direction == 2) {

			matrix result(next.size()-1, std::vector<int>(next.at(0).size()-1));
			for (size_t row{0}; row < result.size(); ++row) {
				for (size_t col{0}; col < result.at(0).size(); ++col) {
					result[row][col] = next.at(row).at(col) + next.at(row+1).at(col+1) - prev.at(row+1).at(col+1);
				}
			}
			return result;
		}

		if (direction == 3) {

			matrix result(next.size()-1, std::vector<int>(next.at(0).size()-1));
			for (size_t row{0}; row < result.size(); ++row) {
				for (size_t col{0}; col < result.at(0).size(); ++col) {
					result[row][col] = next.at(row).at(col+1) + next.at(row+1).at(col) - prev.at(row+1).at(col+1);
				}
			}
			return result;
		}

		return {}; // Uh-oh!
	}

	// static void printMatrix(const matrix& grid) {

	// 	for (size_t row{0}; row < grid.size(); ++row) {
	// 		for (size_t col{0}; col < grid.at(0).size(); ++col) {
	// 			std::cout << grid.at(row).at(col) << " ";
	// 		}
	// 		std::cout << std::endl;
	// 	}
	// }
};

struct Testcase{
	const matrix _grid;
	const int _expected;
	Testcase(const matrix& grid, int expected) : _grid{grid}, _expected{expected} {}

	void info() const {
		std::cout << "Grid:" << std::endl;
		for (const std::vector<int>& row : _grid) {
			for (const int& item : row) {
				std::cout << item << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "Expected: " << _expected << std::endl;
	}

	void test() const {
		info();
		Solution soln;
		const int actual{soln.largestMagicSquare(_grid)};
		std::cout << "Expected: " << _expected << " Actual: " << actual << std::endl;
		assert(_expected==actual);
	}
};

int main() {

	const std::vector<Testcase> testcases{
		Testcase({{5,1,3,1},{9,3,3,1},{1,3,3,8}}, 2),
		Testcase({{7,1,4,5,6},{2,5,1,6,4},{1,5,4,3,2},{1,2,7,3,4}}, 3),
	};
	for (const Testcase& tc : testcases) { tc.test(); }
}