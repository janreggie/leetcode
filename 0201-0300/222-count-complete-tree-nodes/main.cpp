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
	int countNodes(TreeNode* root)
	{
		if (root == nullptr) {
			return 0;
		}
		// What we can do is compare the left and right levels...
		int left_height = 0, right_height = 0;
		for (TreeNode* l = root->left; l != nullptr; l = l->left) {
			++left_height;
		}
		for (TreeNode* r = root->right; r != nullptr; r = r->right) {
			++right_height;
		}

		if (left_height == right_height) {
			return (1 << (left_height + 1)) - 1;
		}

		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};
