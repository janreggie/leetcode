#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
	int finalValueAfterOperations(const std::vector<std::string>& operations) {

		int value = 0;

		for (const std::string& op : operations) {
			if (op == "++X" || op == "X++") {
				++value;
			} else {
				--value;
			}
		}

		return value;
	}
};

struct Testcase {
	const std::vector<std::string> _operations;
	const int _expected;

	std::string details() const {

		std::string result;
		result += "{ ";
		for (const std::string& op : _operations) {
			result += op + ", ";
		}
		result += "} => " + std::to_string(_expected);
		return result;
	}
};

int main() {

	const std::vector<Testcase> cases {
		{{"--X","X++","X++"}, 1},
		{{"++X","++X","X++"}, 3},
		{{"X++","++X","--X","X--"}, 0}
	};

	for (const auto& tc : cases) {
		Solution soln;
		std::cout << "Testing " << tc.details() << std::endl;
		const int actual = soln.finalValueAfterOperations(tc._operations);
		std::cout << "Actual: " << actual << std::endl;
		if (actual != tc._expected) {
			return 1;
		}
	}
}
