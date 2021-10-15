#include <iostream>
#include <map>
#include <string>
#include <vector>

class Solution {

	// _cache[a][b] stores the answer of numDistinct(s,t)
	// as per iter
	//
	std::vector<std::map<size_t, int>> _cache;
	std::string _s;
	std::string _t;

public:
	int numDistinct(const std::string& s, const std::string& t) {

		// Initialize _cache
		_cache = std::vector<std::map<size_t,int>>(s.size()+1);
		_s = s;
		_t = t;
		return iter(0,0);
    }

private:

	// iter(ii,jj) == numDistinct(s.substr(ii), t.substr(jj))
	int iter(size_t ii, size_t jj) {

		// Check if answer is already in _cache
		if (_cache.at(ii).count(jj) == 1) {
			return _cache.at(ii).at(jj);
		}

		const int slen = _s.length()-ii, tlen = _t.length()-jj;
		if (tlen == 0) { return 1; }
		if (slen < tlen) { return 0; }
		if (slen == tlen) {
			if (_s.substr(ii) == _t.substr(jj)) {
				_cache[ii][jj] = 1;
				return 1;
			}
			_cache[ii][jj] = 0;
			return 0;
		}

		int result = iter(ii+1, jj);
		if (_s.at(ii) == _t.at(jj)) {
			result += iter(ii+1,jj+1);
		}
		_cache[ii][jj] = result;
		return result;
	}
};

struct Testcase {
	const std::string _s;
	const std::string _t;
	const int _expected;

	Testcase(const std::string& s, const std::string& t, int expected)
	: _s{s}, _t{t}, _expected{expected} {}

	std::string details() const {
		return "s: " + _s + ", t: " + _t + ", expected: " + std::to_string(_expected);
	}
};

int main() {

	const std::vector<Testcase> testcases{
		Testcase("rabbbit", "rabbit", 3),
		Testcase("babgbag", "bag", 5),
		Testcase("abc", "a", 1),
		Testcase("aaaaaa", "aa", 15),
		Testcase("aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe", "bddabdcae", 10582116)
	};

	Solution s;

	for (const Testcase& tc : testcases) {
		std::cout << "Testing " << tc.details() << std::endl;
		int actual = s.numDistinct(tc._s, tc._t);
		if (actual != tc._expected) {
			std::cout << tc._expected << " does not match actual " << actual << std::endl;
			return 1;
		}
	}
}
