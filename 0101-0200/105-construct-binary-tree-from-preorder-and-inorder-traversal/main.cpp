#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

	string Info() {
		return "Current: " + to_string(val) +
			"; Left: " + (left == nullptr ? "null" : "{" + left->Info() + "}") +
			"; Right: " + (right == nullptr ? "null" : "{" + right->Info() + "}");
	}
};

class Solution {

	vector<int> _preorder;
	vector<int> _inorder;
	unordered_map<int,size_t> _inorderIndices;

	TreeNode* helper(size_t li, size_t ri, size_t lp, size_t rp) {

		// Note: check below prevents stuff from being negative
		if (li > ri || ri >= _inorder.size()) { return nullptr; }
		if (li == ri) { return new TreeNode(_inorder[li]); }

		const int root{_preorder[lp]};
		const size_t pivot{_inorderIndices[root]};
		const size_t leftSize{pivot-li};
		TreeNode* left{helper(li, li+leftSize-1, lp+1, lp+leftSize)};
		TreeNode* right{helper(pivot+1, ri, lp+leftSize+1, rp)};
		return new TreeNode(root, left, right);
	}

public:
	TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {

		_preorder = vector<int>(preorder);
		_inorder = vector<int>(inorder);
		_inorderIndices.clear();
		for (size_t ii{0}; ii < inorder.size(); ++ii) {
			_inorderIndices[inorder.at(ii)] = ii;
		}

		return helper(0, _inorder.size()-1, 0, _preorder.size()-1);
	}

};

int main() {

	// const vector<int> preorder{3,9,20,15,7}, inorder{9,3,15,20,7};
	const vector<int> preorder{1,2}, inorder{2,1};
	Solution soln;
	cout << soln.buildTree(preorder,inorder)->Info() << endl;

}