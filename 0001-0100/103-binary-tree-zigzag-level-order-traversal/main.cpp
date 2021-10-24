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
	std::vector<std::vector<int>> _result;

public:
	std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		_result = {};
		iter(root, 0);
		return _result;
	}

private:
	void iter(TreeNode* node, size_t level)
	{
		if (node == nullptr) {
			return;
		}

		append(node->val, level);
		iter(node->left, level + 1);
		iter(node->right, level + 1);
	}

	void append(int val, size_t level)
	{
		while (_result.size() <= level) {
			_result.push_back({});
		}
		if (level % 2 == 0) {
			_result.at(level).push_back(val);
		} else {
			_result.at(level).insert(_result.at(level).begin(), val);
		}
	}
};
