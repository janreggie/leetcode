#include <iostream>
#include <vector>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode()
	  : val(0)
	  , left(nullptr)
	  , right(nullptr)
	{}
	TreeNode(int x)
	  : val(x)
	  , left(nullptr)
	  , right(nullptr)
	{}
	TreeNode(int x, TreeNode* left, TreeNode* right)
	  : val(x)
	  , left(left)
	  , right(right)
	{}
};

class Solution
{
public:
	bool isCousins(TreeNode* root, int x, int y)
	{
		std::vector<bool> xstack, ystack; // false: move left, true: move right
		find(root, xstack, x);
		find(root, ystack, y);

		return xstack.size() == ystack.size() &&
		       std::vector(xstack.begin(), --xstack.end()) != std::vector(ystack.begin(), --ystack.end());
	}

private:
	bool find(TreeNode* node, std::vector<bool>& stack, int target)
	{
		if (node == nullptr) {
			return false;
		}
		if (node->val == target) {
			return true;
		}

		// Otherwise, let's try moving
		stack.push_back(false);
		if (find(node->left, stack, target)) {
			return true;
		}
		stack.pop_back();
		stack.push_back(true);
		if (find(node->right, stack, target)) {
			return true;
		}
		stack.pop_back();

		return false;
	}
};
