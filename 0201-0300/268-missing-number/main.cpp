#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
	int missingNumber(const vector<int>& nums) {
		int expected{xorFromOneTo(nums.size())};
		int actual{xorOfAll(nums)};
		return expected ^ actual;
	}

private:
	int xorFromOneTo(int n) {
		int modFour{n & 0x03};
		if (modFour == 1) { return 1; }
		if (modFour == 2) { return n+1; }
		if (modFour == 3) { return 0; }
		return n;
	}

	int xorOfAll(const vector<int>& nums) {
		int result{0};
		for (int num : nums) { result ^= num; }
		return result;
	}
};

int main() {
	const vector<int> input{9,6,4,2,3,5,7,0,1};
	Solution soln;
	const int output{soln.missingNumber(input)};
	cout << output << endl;
}
