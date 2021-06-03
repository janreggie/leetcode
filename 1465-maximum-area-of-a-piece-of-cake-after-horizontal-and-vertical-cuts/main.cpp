#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int maxArea(int h, int w, const vector<int>& horizontalCuts, const vector<int>& verticalCuts) {
		
		vector<int> hCuts(horizontalCuts), vCuts(verticalCuts);
		hCuts.push_back(0);
		hCuts.push_back(h);
		vCuts.push_back(0);
		vCuts.push_back(w);
		sort(hCuts.begin(), hCuts.end());
		sort(vCuts.begin(), vCuts.end());

		unsigned long maxHeight = 0, maxWidth = 0;
		for (size_t ii{1}; ii<hCuts.size(); ++ii) {
			maxHeight = max(maxHeight, (unsigned long)(hCuts[ii]-hCuts[ii-1]));
		}
		for (size_t jj{1}; jj<vCuts.size(); ++jj) {
			maxWidth = max(maxWidth, (unsigned long)(vCuts[jj]-vCuts[jj-1]));
		}

		return (int)((maxHeight*maxWidth)%1000000007);
	}
};

int main() {

}
