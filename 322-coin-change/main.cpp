#include <bits/stdc++.h>
using namespace std;

class Solution {

public:
	int coinChange(const vector<int>& coins, int amount) {

		_solutions = vector<int>(amount+1);
		_coins = vector<int>(coins);
		_leastCoin = *min_element(coins.begin(), coins.end());

		if (_coins.size() == 0) { return save(-1, amount); }
		if (_coins.size() == 1) {
			if (amount % _coins[0] == 0) { return save(amount/_coins[0], amount); }
			return save(-1, amount);
		}

		return solve(coins, amount);
	}

private:
	vector<int> _solutions; // -1: invalid, 0: no soln
	vector<int> _coins;
	int _leastCoin;

	int minValid(int a, int b) {
		if (a == -1) { return b; }
		if (b == -1) { return a; }
		return min(a, b);
	}

	int solve(const vector<int>& coins, int amount) {

		if (amount == 0) { return save(0, amount); }
		if (amount < 0) { return save(-1, amount); }
		if (amount == _leastCoin) { return save(1, amount); }
		if (amount < _leastCoin) { return save(-1, amount); }

		if (_solutions[amount] != 0) { return _solutions[amount]; }

		int record{-1};
		for (size_t ii{0}; ii < coins.size(); ++ii) {
			int contender{solve(coins, amount-coins[ii])};
			if (contender != -1) { record = minValid(record, contender+1); }
		}
		return save(record, amount);

	}


	string vectorToString(const vector<int>& v) {
		std::ostringstream oss;

		if (!v.empty())
		{
    		std::copy(v.begin(), v.end()-1,
				std::ostream_iterator<int>(oss, ","));
			oss << v.back();
		}

		return oss.str();
	}

	int save(int result, int amount = 0) {
		if (amount >= 0) {
			_solutions[amount] = result;
		}
		// log(amount, result);
		return result;
	}

	void log(int amount, int result) {
		cout << "{" << vectorToString(_coins) << "}, " << amount << " --> " << result << endl;
	}

};

int main() {
	vector<int> coins{1,2,5};
	const int amount{100};
	Solution soln;
	const int output{soln.coinChange(coins, amount)};
	cout << output << endl;
}
