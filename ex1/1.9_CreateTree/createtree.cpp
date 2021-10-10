#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* traversal(vector<int>& inorder, int inorderBegin, int inorderEnd, vector<int>& preorder, int preorderBegin, int preorderEnd) {

    //通过下标使用vector容器，可以减少内存开支
    if (preorderBegin == preorderEnd) return NULL; //递归出口
    int rootValue = preorder[preorderBegin]; 
    TreeNode* root = new TreeNode(rootValue);  
    if (preorderEnd - preorderBegin == 1) return root;  //构建结点，一个结点时直接返回
    int root_index;
    for (root_index = inorderBegin; root_index < inorderEnd; root_index++) {
        if (inorder[root_index] == rootValue) break;     
        //找到根节点在中序的下标
    } 

    // 切割中序数组
    int leftInorderBegin = inorderBegin;// 中序左区间，左闭右开[leftInorderBegin, leftInorderEnd)
    int leftInorderEnd = root_index;
    int rightInorderBegin = root_index + 1;// 中序右区间，左闭右开[rightInorderBegin, rightInorderEnd)
    int rightInorderEnd = inorderEnd;

        // 切割前序数组
        // 前序左区间，左闭右开[leftPreorderBegin, leftPreorderEnd)
    int leftPreorderBegin = preorderBegin + 1;
    int leftPreorderEnd = preorderBegin + 1 + root_index - inorderBegin; // 终止位置是起始位置加上中序左区间的大小size
        // 前序右区间, 左闭右开[rightPreorderBegin, rightPreorderEnd)
    int rightPreorderBegin = preorderBegin + 1 + (root_index - inorderBegin);
    int rightPreorderEnd = preorderEnd;

    root->left = traversal(inorder, leftInorderBegin, leftInorderEnd, preorder, leftPreorderBegin, leftPreorderEnd);
    root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, preorder, rightPreorderBegin, rightPreorderEnd);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (inorder.size() == 0 || preorder.size() == 0) return NULL;
    return traversal(inorder, 0, inorder.size(), preorder, 0, preorder.size());
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

int main() {
    vector<int> preResult = { 3,9,20,15,7 };
    vector<int> inResult = { 9,3,15,20,7 };
    vector<int> postResult;
    cout << "前序遍历的结果：" << endl;
    traverse(preResult);
    cout << "中序遍历的结果：" << endl;
    traverse(inResult);
    cout << "重构二叉树" << endl;
    //cout << "后序遍历的结果：" << '\n';
    TreeNode* root = buildTree(preResult, inResult);
    cout << "后序遍历的结果 验证重建的二叉树:" << endl;
    postOrder(root, postResult);
    traverse(postResult);
    system("pause");
    return 0;
}