#include <algorithm>
#include <tuple>
#include <utility>

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
	int diameterOfBinaryTree(TreeNode* root)
	{
		return recurse(root).second;
	}

private:
	// first: the farthest distance from the root
	// second: the farthest distances between the two legs
	std::pair<int, int> recurse(TreeNode* root)
	{
		if (root == nullptr) {
			return { 0, 0 };
		}

		const auto left = recurse(root->left);
		const auto right = recurse(root->right);

		const int depth = 1 + std::max(std::get<0>(left), std::get<0>(right));
		const int diameter = left.first + right.first;
		const int max_diameter = max3(diameter, left.second, right.second);

		return { depth, max_diameter };
	}

	template<typename T>
	T max3(T a, T b, T c)
	{
		return std::max(a, std::max(b, c));
	}
};