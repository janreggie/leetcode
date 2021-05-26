#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int climbStairs(int n) {
		const double sqrt5{sqrt(5)};
		const double gr{(1.0+sqrt5)/2.0};
		const double grc{(1.0-sqrt5)/2.0};
		return int(round(pow(gr,n+1)/sqrt5 - pow(grc,n+1)/sqrt5));
	}
};
