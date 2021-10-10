#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int evalRPN(const vector<string> &tokens) {

		stack<int> operands;
		for (const string& token : tokens) {
			if (token == "+") { operands.push(add(getLastTwo(operands))); }
			else if (token == "-") { operands.push(sub(getLastTwo(operands))); }
			else if (token == "*") { operands.push(mul(getLastTwo(operands))); }
			else if (token == "/") { operands.push(div(getLastTwo(operands))); }
			else { operands.push(stoi(token)); }
		}

		return operands.top();
	}

private:
	pair<int, int> getLastTwo(stack<int>& operands) {
		int first, second;
		second = operands.top();
		operands.pop();
		first = operands.top();
		operands.pop();
		return pair<int,int>(first,second);
	}

	int add(const pair<int,int>& ops) { return ops.first + ops.second; }
	int sub(const pair<int,int>& ops) { return ops.first - ops.second; }
	int mul(const pair<int,int>& ops) { return ops.first * ops.second; }
	int div(const pair<int,int>& ops) { return ops.first / ops.second; }
};

int main() {

	const vector<string> tokens{"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
	Solution soln;
	const int result{soln.evalRPN(tokens)};

	cout << result << endl;
}
