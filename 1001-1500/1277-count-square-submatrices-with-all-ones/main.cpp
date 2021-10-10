#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int countSquares(const vector<vector<int>>& matrix) {
		
		const size_t height{matrix.size()}, width{matrix.at(0).size()};
		vector<vector<int>> coalesced(height, vector<int>(width, 0));

		// Populate zeroth row and col
		coalesced[0] = vector<int>(matrix.at(0));
		for (size_t ii{0}; ii<height; ++ii) {
			coalesced[ii][0] = matrix.at(ii).at(0);
		}

		// Populate the rest of the rows
		for (size_t ii{1}; ii<height; ++ii) {
			for (size_t jj{1}; jj<width; ++jj) {
				if (matrix[ii][jj] == 0) { continue; }
				coalesced[ii][jj] = 1 + min(coalesced.at(ii-1).at(jj-1), min(coalesced.at(ii-1).at(jj), coalesced.at(ii).at(jj-1)));
			}
		}

		// Find the sum of coalesced and return that
		int result{0};
		for (const vector<int>& row : coalesced) {
			for (const int& elem : row) {
				result += elem;
			}
		}
		return result;
	}
};

int main() {

	// Bruh...
	const vector<vector<int>> matrix{
		{0,1,1,1},
		{1,1,1,1},
		{0,1,1,1}
	};
	Solution soln;
	cout << soln.countSquares(matrix) << endl;
}
