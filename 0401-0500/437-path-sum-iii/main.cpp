#include <unordered_map>
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
	int pathSum(TreeNode* root, int targetSum)
	{
		if (root == nullptr) {
			return 0;
		}

		return iter(root, 0, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
	}

private:
	int iter(TreeNode* root, int current, int target)
	{
		if (root == 0) {
			return 0;
		}
		current += root->val;
		return (current == target) + iter(root->left, current, target) + iter(root->right, current, target);
	}
};
