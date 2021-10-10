#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		return splitAndReverse(n, 32);
	}

private:
	uint32_t splitAndReverse(uint32_t n, uint32_t bitCount) {
		if (bitCount == 1) { return n; }
		uint32_t halfBitCount{bitCount/2};
		uint32_t firstHalf{n >> halfBitCount};
		uint32_t secondHalf{n & ((1<<halfBitCount)-1)};

		firstHalf = splitAndReverse(firstHalf, halfBitCount);
		secondHalf = splitAndReverse(secondHalf, halfBitCount);
		return ((secondHalf<<halfBitCount) + firstHalf);
	}
};

int main() {
	uint32_t input{0b11111111111111111111111111111101};
	Solution soln;
	uint32_t output{soln.reverseBits(input)};

	cout << output << endl;
}
