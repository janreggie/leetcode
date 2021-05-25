#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> result(n+1);
		for (uint32_t ii{0}; ii <= uint32_t(n); ++ii) {
			result[ii] = numberOfSetBits(ii);
		}
		return result;
	}

	int numberOfSetBits(uint32_t n) {
		return pops[n & 0xFF] + pops[(n>>8) & 0xFF] + pops[(n>>16) & 0xFF] + pops[(n>>24) & 0xFF]; 
	}

	const vector<int> pops{0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
						   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
						   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
						   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8}; // 0 to 255
};

int main() {
	Solution soln;
	const int input{5};
	const vector<int> result{soln.countBits(input)};
	for (int vv : result) cout << vv << endl;
}
