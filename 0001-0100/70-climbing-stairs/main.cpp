class Solution
{
public:
	int climbStairs(int n)
	{
		if (n <= 2) {
			return n;
		}
		int a = 1, b = 2;
		for (int ii = 2; ii < n; ++ii) {
			const int c = a + b;
			a = b;
			b = c;
		}
		return b;
	}
};
