#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Solution {

	std::vector<std::string> _words;
	std::unordered_map<char,std::vector<size_t>> _startingLetters; // _words[ii] for ii in _startingLetters['a'] will start with 'a'
	std::unordered_map<char,std::vector<size_t>> _endingLetters;   // Check _startingLetters but for ending letters
	std::unordered_set<size_t> _blanks; // _words[ii] for ii in _blanks is the empty string ""

public:
	std::vector<std::vector<int>> palindromePairs(const std::vector<std::string>& words) {

		_words = words;
		_startingLetters.clear();
		_endingLetters.clear();
		_blanks.clear();

		for (size_t ii{0}; ii < _words.size(); ++ii) {
			const std::string& word{_words.at(ii)};
			if (word.size() == 0) {
				_blanks.insert(ii);
				continue;
			}
			// Don't worry about not initializing them first. Default constructors will kick in for them.
			_startingLetters[word.at(0)].push_back(ii);
			_endingLetters[word.at(word.size()-1)].push_back(ii);
		}

		std::vector<std::vector<int>> result;
		// Now, compare for every letter
		//
		for (const auto& start : _startingLetters) {
			const char startLetter{start.first};
			const std::vector<size_t>& startingIndices{start.second};
			if (_endingLetters.count(startLetter) == 0) { continue; }
			for (const size_t startIndex : startingIndices) {
				for (const size_t endIndex : _endingLetters.at(startLetter)) {
					if (startIndex == endIndex) { continue; }
					if (check(startIndex, endIndex)) { result.push_back({(int)startIndex, (int)endIndex}); }
				}
			}
		}

		// And compare for each blank
		//
		if (_blanks.size() != 0) {
			for (size_t ii{0}; ii < _words.size(); ++ii) {
				const std::string& word{_words.at(ii)};
				if (word.size() == 0) { continue; }
				if (check(word)) {
					for (const size_t blank : _blanks) {
						result.push_back({(int)ii, (int)blank});
						result.push_back({(int)blank, (int)ii});
					}
				}
			}
		}

		return result;
	}

private:
	// Check if _words.at(ind1)+_words.at(ind2) form a palindrome
	bool check(size_t ind1, size_t ind2) {

		const std::string& word1{_words.at(ind1)}, word2{_words.at(ind2)};
		if (word1.size() + word2.size() <= 1) { return true; } // Guaranteed match

		// Check starting from the head of word1 and tail of word2
		auto i1{word1.begin()}, i2{--word2.end()};
		while (i1 < word1.end() && i2 >= word2.begin()) {
			if ((*i1) != (*i2)) { return false; }
			++i1;
			--i2;
		}
		if (i1 == word1.end()) { return check(word2.begin(), i2); }
		return check(i1, --word1.end());
	}

	// Check if a string is a palindrome
	bool check(const std::string& s) {
		if (s.size() <= 1) { return true; }
		for (size_t ii{0}; ii < s.size()/2; ++ii) {
			if (s.at(ii) != s.at(s.size()-ii-1)) { return false; }
		}
		return true;
	}

	// Check if the string represented by two iterators returns true
	bool check(std::string::const_iterator s1, std::string::const_iterator s2) {

		if (s1 > s2) { return true; }

		for (; s1 < s2; ++s1, --s2) {
			if ((*s1) != (*s2)) { return false; }
		}
		return true;
	}
};

struct Testcase {
	const std::vector<std::string> _words;
	const std::vector<std::vector<int>> _expected;

	Testcase(const std::vector<std::string>& words, const std::vector<std::vector<int>>& expected)
	: _words{words}, _expected{expected} {};

	void test() const {
		info();
		std::unordered_set<long> expected; // All expected but hashed
		for (const std::vector<int> ee : _expected) { expected.insert(hash(ee.at(0),ee.at(1))); }

		Solution soln;
		const std::vector<std::vector<int>> actual{soln.palindromePairs(_words)};
		std::cout << "Actual: {";
		for (const std::vector<int>& aa : actual) { std::cout << "(" << aa.at(0) << "," << aa.at(1) << ") "; }
		std::cout << "}" << std::endl;
		assert(actual.size() == _expected.size());

		for (const std::vector<int>& aa : actual) {
			if (expected.count(hash(aa.at(0), aa.at(1))) != 1) { 
				std::cout << "Could not find (" << aa.at(0) << "," << aa.at(1) << ") in expected" << std::endl;
				assert(false);
			}
		}
	}

	void info() const {
		std::cout << "Words: {";
		for (const std::string& word : _words) { std::cout << word << " "; }
		std::cout << "} Expected: {";
		for (const std::vector<int>& expect : _expected) { std::cout << "(" << expect.at(0) << "," << expect.at(1) << ") "; }
		std::cout << "}" << std::endl;
	}

	long hash(int i1, int i2) const {

		return long(i1) * long(_words.size()) + i2;
	}
};

int main() {

	const std::vector<Testcase> testCases{
		{{"abcd","dcba","lls","s","sssll"}, {{0,1},{1,0},{3,2},{2,4}}},
		{{"bat","tab","cat"}, {{0,1},{1,0}}},
		{{"a",""},{{0,1},{1,0}}},
	};

	for (const Testcase& tc : testCases) { tc.test(); }
}
