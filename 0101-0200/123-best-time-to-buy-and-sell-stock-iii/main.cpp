#include <limits>
#include <vector>

class Solution
{
public:
	int maxProfit(std::vector<int>& prices)
	{
		int minus_inf = std::numeric_limits<int>::min();
		long s0 = 0, b1 = minus_inf, s1 = minus_inf, b2 = minus_inf, s2 = minus_inf;

		for (const int p : prices) {
			s2 = std::max(s2, b2 + p);
			b2 = std::max(b2, s1 - p);
			s1 = std::max(s1, b1 + p);
			b1 = std::max(b1, long(-p));
		}

		return std::max(s0, std::max(s1, s2));
	}
};
