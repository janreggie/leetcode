#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int minCostClimbingStairs(const vector<int>& cost) {

		vector<int> cache(cost);
		for (size_t ii{cost.size()-3}; ii < cost.size(); --ii) {
			cache[ii] += min(cache[ii+1], cache[ii+2]);
		}
		return min(cache[0], cache[1]);
	}

	int minCostClimbingStairs(const vector<int>& cost, size_t ind, vector<int>& cache) {

		if (ind >= cost.size()) { return 0; }
		if (cache[ind] != 0) { return cache[ind]; }

		int result{cost[ind] + min(minCostClimbingStairs(cost, ind+1, cache), minCostClimbingStairs(cost, ind+2, cache))};
		cache[ind] = result;
		return result;
	}
};

int main() {

	const vector<int> cost{1,100,1,1,1,100,1,1,100,1};
	Solution soln;
	cout << soln.minCostClimbingStairs(cost) << endl;
}
