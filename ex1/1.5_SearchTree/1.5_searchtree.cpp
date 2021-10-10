#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* initBTree(int elements[], int size)
{
	if (size < 1)
	{
		return NULL;
	}
	TreeNode** nodes = new TreeNode * [size];
	for (int i = 0; i < size; i++) //现将数组内数字全转换为结点
	{
		if (elements[i] == 0) //数组中的0代表空节点
		{
			nodes[i] = NULL;
		}
		else
		{
			nodes[i] = new TreeNode(elements[i]);
		}
	}
	queue<TreeNode*> nodeQueue;   
	nodeQueue.push(nodes[0]);  //队列加入根节点

	TreeNode* node;
	int index = 1;
	while (index < size)
	{
		node = nodeQueue.front();  //获得队头作为局部根节点
		nodeQueue.pop();           //当前移出队列
		nodeQueue.push(nodes[index++]);  //把该节点的左孩子加入队列
		node->left = nodeQueue.back();   //返回最后一个元素
		nodeQueue.push(nodes[index++]);  //同上操作右节点
		node->right = nodeQueue.back();
	}
	return nodes[0];  //返回根节点
}

void preOrder(TreeNode* root, vector<int>& result) //先序遍历
{
	if (root == NULL) return;
	result.push_back(root->val);
	preOrder(root->left, result);
	preOrder(root->right, result);
}

void inOrder(TreeNode* root, vector<int>& result) //中序遍历
{
	if (root == NULL) return;
	inOrder(root->left, result);
	result.push_back(root->val);
	inOrder(root->right, result);
}

void postOrder(TreeNode* root, vector<int>& result) //后序遍历
{
	if (root == NULL) return;
	postOrder(root->left, result);
	postOrder(root->right, result);
	result.push_back(root->val);
}

void traverse(vector<int> nums)   //输出遍历后的结果
{
	for (int i = 0; i < nums.size(); i++)
	{
		cout << nums[i] << ' ';
	}
	cout << endl;
}

string isValidBST1(vector<int>& inOrder) {
	for (int i = 1; i < inOrder.size(); i++) {
		// 注意要小于等于，搜索树里不能有相同元素
		if (inOrder[i] <= inOrder[i - 1]) return "false";
	}
	return "true";
}

bool process(TreeNode* root) {
	if (root == NULL) {
		return false;
	}
	// 找左节点的最大值，就是左子树的最右结点
	bool leftFlag = true;
	if (root->left != NULL) {
		TreeNode* leftNode = root->left;
		while (leftNode->right != NULL) {
			leftNode = leftNode->right;
		}
		leftFlag = leftNode->val < root->val;
	}

	// 找右节点的最小值，就是右子树的最左结点
	bool rightFlag = true;
	if (root->right != NULL) {
		TreeNode* rightNode = root->right;
		while (rightNode->left != NULL) {
			rightNode = rightNode->left;
		}
		rightFlag = rightNode->val > root->val;
	}
	return rightFlag && leftFlag;
}

bool isValidBST2(TreeNode* root) {
	if (root == NULL) { //到底了 就返回正确
		return true;
	}
	if ((root->left != NULL && root->val <= root->left->val) || ((root->right != NULL && root->val >= root->right->val))) {
		return false;
	}  //左右结点都在时 比较
	//根要大于左的最大值，小于右的最小值 //pdf中写的有误
	return process(root) && isValidBST2(root->left) && isValidBST2(root->right);
}

int main() {
	int a[] = { 5,1,4,0,0,3,6 }; //使用队列初始化二叉树，以满二叉树的层次的形式输入
	TreeNode* root = initBTree(a, 7);
	vector<int> preResult;
	vector<int> inResult;
	vector<int> postResult;
	preOrder(root, preResult);
	inOrder(root, inResult);
	postOrder(root, postResult);
	//cout << "前序遍历的结果：" << endl;
	//traverse(preResult);
	cout << "中序遍历的结果：" << endl;
	traverse(inResult);
	//cout << "后序遍历的结果：" << endl;
	//traverse(postResult);
	cout << "通过中序遍历判断是否为二叉搜索树 " << isValidBST1(inResult) << endl;
	cout << "通过递归判断是否为二叉搜索树 " << isValidBST2(root) << endl;
	system("pause");
	return 0;
}