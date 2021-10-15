#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

class Solution
{
	size_t _width, _height;
	std::vector<std::vector<char>> _board;
	std::string _word;

public:
	bool exist(const std::vector<std::vector<char>>& board, const std::string& word)
	{
		_height = board.size();
		_width = board[0].size();
		_board = board;
		_word = word;

		for (size_t x = 0; x < _width; ++x) {
			for (size_t y = 0; y < _height; ++y) {
				if (_word[0] == _board[y][x] && exist(0, x, y)) {
					return true;
				}
			}
		}

		return false;
	}

private:
	// Check if word[ind:] exists starting from board[y][x]
	bool exist(size_t ind, size_t x, size_t y)
	{
		if (ind == _word.size()) {
			return true;
		}

		if (x >= _width || y >= _height) {
			return false;
		}

		const char first = _word.at(ind);
		if (_board[y][x] != first) {
			return false;
		}

		_board[y][x] = ' '; // Set it to any character
		const bool result = exist(ind + 1, x - 1, y) ||
				    exist(ind + 1, x + 1, y) ||
				    exist(ind + 1, x, y - 1) ||
				    exist(ind + 1, x, y + 1);

		_board[y][x] = first;
		return result;
	}
};

template<class T, class U>
std::ostream&
operator<<(std::ostream& os, const std::pair<T, U>& p)
{
	os << "(" << p.first << "," << p.second << ")";
	return os;
}

int
main()
{
	const std::vector<std::vector<char>> board{
		{ 'A', 'B', 'C', 'E' },
		{ 'S', 'F', 'E', 'S' },
		{ 'A', 'D', 'E', 'E' }
	};
	const std::vector<std::pair<std::string, bool>> testcases{
		{ "ABCESEEEFS", true }
	};
	for (const auto& tc : testcases) {
		std::cout << "testing " << tc << std::endl;
		Solution soln;
		const bool actual = soln.exist(board, tc.first);
		if (tc.second != actual) {
			return 1;
		}
	}
}
