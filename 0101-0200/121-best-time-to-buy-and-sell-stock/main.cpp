#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        
        if (prices.size() <= 1) {
            return 0;
        }
        
        int minPrice{prices[0]};
        int maxProfit{0};
        for (size_t ii{0}; ii < prices.size(); ++ii) {
            if (prices[ii] < minPrice) { minPrice = prices[ii]; }
            else if (prices[ii]-minPrice > maxProfit) { maxProfit = prices[ii] - minPrice; }
        }
        return maxProfit;
    }

};

int main() {

	const vector<int> prices{5,3,6,1,2};
	Solution soln;

	cout << soln.maxProfit(prices) << endl;
}