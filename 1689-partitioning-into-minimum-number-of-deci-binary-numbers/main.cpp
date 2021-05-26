#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int minPartitions(string n) {
		int maximumDigit{0};
		for (const char& c : n) {
			int d{c-48};
			if (d > maximumDigit) { maximumDigit = d; }
		}

		return maximumDigit;
    }
};

int main() {
	const string input{"82734"};
	Solution soln;
	const int output{soln.minPartitions(input)};
	cout << output << endl;
}
