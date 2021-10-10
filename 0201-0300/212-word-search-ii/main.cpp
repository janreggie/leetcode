#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

class Cache
{
	static constexpr long long p = 31;
	static constexpr long long p1 = 838709685; // x * p1 == x / p mod m
	static constexpr long long m = 1e9 + 9;
	std::vector<std::string> _strs;

public:
	bool in(const std::string& word)
	{
		const size_t len = word.size();
		const long long substr_hash = hash(word);

		for (const std::string& str : _strs) {
			if (str.size() > len) {
				continue;
			}
			if (str.size() == len) {
				if (str == word) {
					return true;
				}
				continue;
			}

			// Now, for the rolling hash part...
			long long prev_hash = hash(str, len);
			if (prev_hash == substr_hash && cmp(str, 0, word)) {
				return true;
			}
			for (size_t ind = 1; ind <= (str.size() - len); ++ind) {
				const long long next_hash = hash(str, ind, len, prev_hash);
				if (next_hash == substr_hash && cmp(str, ind, word)) {
					return true;
				}
				prev_hash = next_hash;
			}
		}

		return false;
	}

	void add(const std::string& word)
	{
		_strs.push_back(word);
	}

private:
	static long long hash(const std::string& s)
	{
		long long hash_value = 0;
		long long p_pow = 1;
		for (char c : s) {
			hash_value = (hash_value + hash(c) * p_pow) % m;
			p_pow = (p_pow * p) % m;
		}

		return hash_value;
	}

	// Hash first len characters of s
	static long long hash(const std::string& s, size_t len)
	{
		long long hash_value = 0;
		long long p_pow = 1;
		for (size_t ii = 0; ii < len; ++ii) {
			hash_value = (hash_value + hash(s[ii]) * p_pow) % m;
			p_pow = (p_pow * p) % m;
		}

		return hash_value;
	}

	// Hash s[ind:ind+len] such that prev = hash(s[ind-1:ind+len-1]).
	static long long hash(const std::string& s, size_t ind, size_t len, long long prev)
	{
		long long hash_value = prev - hash(s[ind - 1]);
		while (hash_value < 0) {
			hash_value += m;
		}

		hash_value = (hash_value * p1 + (hash(s[ind + len - 1]) * ipow(p, len - 1))) % m;
		return hash_value;
	}

	static long long hash(const char c) { return c - 'a' + 1; }

	// Elias Yarrkov / Static Overflow <https://stackoverflow.com/a/101613/14020202>, CC BY-SA 3.0
	static long long ipow(long long base, long long exp)
	{
		long long result = 1;
		for (;;) {
			if (exp & 1)
				result *= base;
			exp >>= 1;
			if (!exp)
				break;
			base *= base;
		}

		return result % m;
	}

	// Compare str[ind : ind+substr.size()] and substr
	static bool cmp(const std::string& str, size_t ind, const std::string& substr)
	{
		for (size_t ii = 0; ii < ind; ++ii) {
			if (str[ind + ii] != substr[ii]) {
				return false;
			}
		}
		return true;
	}
};

class Solution
{
	std::vector<std::vector<char>> _board;
	std::multiset<char> _chars;
	size_t _width, _height;

public:
	std::vector<std::string> findWords(const std::vector<std::vector<char>>& board, std::vector<std::string> words)
	{
		_board = board;
		_width = board.at(0).size();
		_height = board.size();
		for (const std::vector<char>& row : _board) {
			for (const char c : row) {
				_chars.insert(c);
			}
		}

		Cache cache;

		// Sort words by length in reverse
		std::sort(std::begin(words), std::end(words), [](const std::string& l, const std::string& r) { return l.size() > r.size(); });

		std::vector<std::string> result;
		for (const std::string& word : words) {
			if (!isPossible(word)) {
				continue;
			}
			if (cache.in(word)) {
				result.push_back(word);
				continue;
			}

			refillBoard(board);
			if (find(word)) {
				cache.add(word);
				result.push_back(word);
			}
		}

		return result;
	}

private:
	bool find(const std::string& word)
	{
		// Go through the entire grid
		for (size_t x = 0; x < _width; ++x) {
			for (size_t y = 0; y < _height; ++y) {
				if (find(word, 0, x, y)) {
					return true;
				}
			}
		}

		return false;
	}

	bool find(const std::string& word, size_t ind, size_t x, size_t y)
	{
		if (ind == word.size()) {
			return true;
		}
		if (x >= _width || y >= _height) {
			return false;
		}

		const char ch = word[ind];
		if (_board[y][x] != ch) {
			return false;
		}

		_board[y][x] = ' ';
		const bool result = find(word, ind + 1, x - 1, y) ||
				    find(word, ind + 1, x + 1, y) ||
				    find(word, ind + 1, x, y - 1) ||
				    find(word, ind + 1, x, y + 1);
		_board[y][x] = ch;
		return result;
	}

	void refillBoard(const std::vector<std::vector<char>>& board)
	{
		for (size_t x = 0; x < _width; ++x) {
			for (size_t y = 0; y < _height; ++y) {
				_board[y][x] = board[y][x];
			}
		}
	}

	bool isPossible(const std::string& word)
	{
		std::multiset<char> chars;
		for (const char c : word) {
			chars.insert(c);
		}

		for (const char c : chars) {
			if (chars.count(c) > _chars.count(c)) {
				return false;
			}
		}

		return true;
	}
};

int
main()
{
	const std::vector<std::vector<char>> board{
		{ 'o', 'a', 'a', 'n' },
		{ 'e', 't', 'a', 'e' },
		{ 'i', 'h', 'k', 'r' },
		{ 'i', 'f', 'l', 'v' }
	};
	const std::vector<std::string> words{ "oath", "pea", "eat", "rain" };
	const std::unordered_set<std::string> expected{ "eat", "oath" };

	Solution soln;
	std::unordered_set<std::string> actual;
	for (const std::string& word : soln.findWords(board, words)) {
		actual.insert(word);
	}

	// Compare expected and actual
	for (const std::string& word : actual) {
		std::cout << "Checking if " << word << " in expected" << std::endl;
		if (expected.count(word) == 0) {
			std::cout << word << " not in expected" << std::endl;
		}
	}
	for (const std::string& word : expected) {
		std::cout << "Checking if " << word << " in actual" << std::endl;
		if (actual.count(word) == 0) {
			std::cout << word << " not in actual" << std::endl;
		}
	}
}
