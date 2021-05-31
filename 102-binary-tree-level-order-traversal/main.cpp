#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> result;
		run(root, result, 0);
		return result;
	}

private:
	void run(TreeNode* root, vector<vector<int>>& vv, size_t level) {

		if (root == nullptr) { return; }

		run(root->left, vv, level+1);

		while (vv.size() <= level) {
			vv.push_back({});
		}
		vv[level].push_back(root->val);

		run(root->right, vv, level+1);
	}
};

int main() {

	TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
	Solution soln;
	vector<vector<int>> output{soln.levelOrder(root)};
	for (const auto& vv : output) {
		for (const int cc : vv) { cout << cc << " "; }
		cout << endl;
	}
}
