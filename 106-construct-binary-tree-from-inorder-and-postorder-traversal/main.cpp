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
	TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder) {

		const size_t len{inorder.size()};
		if (len == 0) { return nullptr; }
		if (len == 1) { return new TreeNode(inorder[0]); }

		const int root{postorder[len-1]};
		size_t pivot{len};
		for (size_t ii{0}; ii<len; ++ii) {
			if (inorder[ii] == root) {
				pivot = ii;
				break;
			}
		}
		assert(pivot!=len);

		const vector<int> leftInorder(inorder.begin(), inorder.begin()+pivot),
						  rightInorder(inorder.begin()+pivot+1, inorder.end()),
						  leftPostorder(postorder.begin(), postorder.begin()+pivot),
						  rightPostorder(postorder.begin()+pivot, postorder.end()-1);
		TreeNode* left = buildTree(leftInorder, leftPostorder);
		TreeNode* right = buildTree(rightInorder, rightPostorder);
		return new TreeNode(root, left, right);
	}
};
