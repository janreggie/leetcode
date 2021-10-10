#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {

	std::unordered_map<char, std::unordered_set<std::string>> _words; // { 'a': {"apple", "anteater"}, 'b': {"banana", "basket"}, ...}
	std::string _input;
	std::vector<int> _result; // _result[ii] determines if _input[ii:] can be "formed" using _words.
	                          // 0: unknown, 1: yes, 2: no

public:

	bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict) {

		_input = std::string(s);
		_words.clear();
		for (const std::string& word : wordDict) {
			_words[word[0]].insert(word);
		}
		_result = std::vector<int>(s.size(), 0);

		// Check if there are letters in s that are NOT in wordDict
		// (for edge cases)
		//
		std::unordered_set<char> wordLetters;
		for (const std::string& word : wordDict) {
			for (const char& ch : word) {
				wordLetters.insert(ch);
			}
		}
		for (const char& ch : s) {
			if (wordLetters.count(ch) == 0) { return false; }
		}

		return iter(0);
	}

	bool iter(size_t index) {

		if (index == _input.size()) { return true; }
		if (index > _input.size()) { return false; }
		if (_result[index] != 0) { return _result[index] == 1; }

		const char current{_input[index]};
		for (const std::string& nextWord : _words[current]) {

			// Check if nextWord is even feasible by checking for length
			// and if the letters are all equal
			//
			if (index+nextWord.size() > _input.size()) { continue; }
			bool isOkay{true};
			for (size_t ii{0}; ii < nextWord.size(); ++ii) {
				if (_input.at(index+ii) != nextWord.at(ii)) {
					isOkay = false;
					break;
				}
			}
			if (isOkay && iter(index+nextWord.size())) {
				_result[index] = 1;
				return true;
			}
		}
		_result[index] = 2;
		return false;
	}

};

struct Testcase {
	const std::string _s;
	const std::vector<std::string> _wordDict;
	const bool _expected;
	Testcase(const std::string& s, const std::vector<std::string>& wordDict, const bool expected)
		: _s{s}, _wordDict{wordDict}, _expected{expected} {}

	std::string details() const {
		std::string result = "_s: \"" + _s + "\", _wordDict = {";
		for (const std::string& word : _wordDict) { result += "\"" + word + "\","; }
		result += "}, _expected: ";
		result += (_expected ? "true" : "false");
		return result;
	}
};

int main() {

	const std::vector<Testcase> testCases{
		Testcase("leetcode", {"leet","code"}, true),
		Testcase("applepenapple", {"apple","pen"}, true),
		Testcase("catsandog", {"cats","dog","sand","and","cat"}, false),
		Testcase("ccbb", {"bc","cb"}, false),
		Testcase("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"}, false),
		Testcase("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", {"aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba"}, false),
};
	Solution soln;

	for (const Testcase& tc : testCases) {
		std::cout << "Testing " << tc.details() << "..." << std::flush;
		assert(soln.wordBreak(tc._s, tc._wordDict) == tc._expected);
		std::cout << "okay.\n";
	}
}
