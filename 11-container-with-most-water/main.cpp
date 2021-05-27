#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int maxArea(const vector<int>& height) {

		size_t ii{0}, jj{height.size()-1};
		int record{0};
		while (ii != jj) {
			record = max(record, area(height, ii, jj));
			if (height[ii] < height[jj]) { ++ii; }
			else { --jj; }
		}
		return record;
	}

private:
	int area(const vector<int>& height, size_t ii, size_t jj) {
		return int(jj-ii) * min(height[ii], height[jj]);
	}
};

int main() {
	const vector<int> input{1,8,6,2,5,4,8,3,7};
	Solution soln;
	const int output{soln.maxArea(input)};
	cout << output << endl;
}
