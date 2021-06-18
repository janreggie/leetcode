#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<string> generateParenthesis(int n) {
	
		vector<vector<int>> patterns{gen(n)};
		vector<string> result(patterns.size());

		for (size_t ii{0}; ii < patterns.size(); ++ii) {
			result[ii] = patternToParentheses(patterns.at(ii));
		}

		return result;
	}
	
private:
	
	string patternToParentheses(const vector<int>& pattern) {

		string result;
		int prev{0};
		for (const int pp : pattern) {
			
			result += string(1+prev-pp, ')'); // Closing parentheses
			result += '(';
			prev = pp;
		}
		result += string(prev, ')');
		return result;
	}
	
	// gen generates a set of "parenthesis patterns"
	// where a pattern represents a string of legitimate well-formed parentheses.
	// e.g., `1111` -> `()()()()`, `1121` -> `()(())()`, `1234` -> `(((())))`, ...
	//
	vector<vector<int>> gen(int n) {
	
		return gen(n, n);
	
	}

	vector<vector<int>> gen(int n, int ind) {

		if (ind == 1) {
			return {{1}}; // There is only one possibility.
		}
		
		vector<vector<int>> prevPatterns{gen(n,ind-1)};
		vector<vector<int>> result;
		for (const vector<int>& prev : prevPatterns) {
			int last{prev.at(ind-2)};
			for (int ii{1}; ii <= last+1; ++ii) {
			vector<int> rr{prev};
			rr.push_back(ii);
			result.push_back(rr);
			}
		}
		return result;
	}
	
};

int main() {

		Solution soln;
		for (const auto& ss : soln.generateParenthesis(4)) {
				cout << ss << endl;
		}
}
