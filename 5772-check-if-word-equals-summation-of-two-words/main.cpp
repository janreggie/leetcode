#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	bool isSumEqual(const string& firstWord, const string& secondWord, const string& targetWord) {

		return (valueOf(firstWord)+valueOf(secondWord)) == valueOf(targetWord);
    }

	unsigned int valueOf(const string& word) {

		unsigned int result{0};
		for (const char& c : word) {
			result *= 10;
			result += (unsigned int)(c-'a');
		}
		return result;
	}
};

int main() {
	const string firstWord{"acb"}, secondWord{"cba"}, thirdWord{"cdb"};
	Solution soln;
	bool result{soln.isSumEqual(firstWord,secondWord,thirdWord)};

	cout << "Values are " << soln.valueOf(firstWord) << "," << soln.valueOf(secondWord) << "," << soln.valueOf(thirdWord) << endl;
	cout << "Result is " << (result ? "true" : "false") << endl;
}
