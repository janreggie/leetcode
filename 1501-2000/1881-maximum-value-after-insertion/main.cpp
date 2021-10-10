#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	string maxValue(const string& n, int x) {

		size_t insertBefore{n.size()}; // Fallback value

		if (n[0] == '-') { // Negatives: Insert before when the digit is greater

			for (size_t ii{1}; ii < n.size(); ++ii) {
				if (int(n[ii]-'0') > x) {
					insertBefore = ii;
					break;
				}
			}
		} else { // Postiives: Insert before when the digit is less

			for (size_t ii{0}; ii < n.size(); ++ii) {
				if (int(n[ii]-'0') < x) {
					insertBefore = ii;
					break;
				}
			}
		}

		return n.substr(0,insertBefore) + (char)(x+'0') + n.substr(insertBefore);
	}
};

int main() {
	const string n{"-55"};
	const int x{2};
	Solution soln;
	const string result{soln.maxValue(n,x)};
	cout << result << endl;
}