#include <iostream>
#include <string>
#include <vector>

class Solution {

	std::vector<int> _letters;
public:
	int maxLength(const std::vector<std::string>& arr) {

		_letters = std::vector<int>(arr.size());
		for (size_t ii = 0; ii < arr.size(); ++ii) {
			_letters.at(ii) = toLetters(arr.at(ii));
		}

		return countLetters(maxLetters(0));
	}

private:

	// Gets `letters` which is the maximum combination between any amount of letters.
	// Takes note of `done`, which represent the letters that cannot be used.
	//
	int maxLetters(size_t ind, int done = 0) {
		if (ind == _letters.size()) { return done; }

		const int first = _letters.at(ind);
		if ((done & first) != 0) {
			return maxLetters(ind+1, done);
		}

		const int withFirst = maxLetters(ind+1, done | first);
		const int withoutFirst = maxLetters(ind+1, done);
		if (countLetters(withFirst) > countLetters(withoutFirst)) {
			return withFirst;
		}
		return withoutFirst;
	}

	static int toLetters(const std::string& word) {
		int result = 0;
		for (const char ch : word) {
			const int toOr = (1 << (ch - 'a'));
			if ((result & toOr) != 0) {
				return 0;
			}
			result |= (1 << (ch - 'a'));
		}
		return result;
	}

	static size_t countLetters(int letters) {
		size_t result = 0;
		while (letters > 0) {
			result += (letters & 1);
			letters >>= 1;
		}
		return result;
	}
};

struct Testcase {
	const std::vector<std::string> _input;
	const int _expected;
	friend std::ostream& operator<<(std::ostream& os, const Testcase& tc) {
		os << "{ ";
		for (const std::string& in : tc._input) {
			os << in << " ";
		}
		os << "} -> " << tc._expected;
		return os;
	}
};

int main() {

	const std::vector<Testcase> testcases {
		{{"un","iq","ie"}, 4},
		{{"cha","r","act","ers"}, 6},
		{{"qwertyuiopasdfghjklzxcvbnm"}, 26},
		{{"abc","bcd","dce","afg","npr","fan"}, 9},
		{{"yy","bkhwmpbiisbldzknpm"}, 0}
	};
	for (const Testcase& tc : testcases) {
		std::cout << "Testing " << tc << std::endl;
		Solution soln;
		const int actual = soln.maxLength(tc._input);
		std::cout << "Actual: " << actual << std::endl;
		if (tc._expected != actual) { return 1; }
	}
}
