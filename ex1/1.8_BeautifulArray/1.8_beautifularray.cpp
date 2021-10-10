#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> beautifulArray(int n) {   //n  序列是从1-n的自然数

	if (n == 1) {
		return { 1 };
	}
    vector<int> result, left, right;
    left = beautifulArray((n + 1) / 2);    
	for (auto i : left) {
		result.push_back(i * 2 - 1);         //左边全为奇数组
	}
    right = beautifulArray(n / 2);          //限制大小    
	for (auto i : right) {
		result.push_back(i * 2);            //右边全为偶数组
	}
    return result;
}                                          //f1 = 1; f2 = L(f1) + R(f1) = {1,2};  f3 = L(f2)+R(f1) = {1,3,2}  
											//L=2i-1 R=2i                         f5 = L(f3)+R(f2) = {1,5,3,2,4}

void traverse(vector<int> nums)   //输出结果
{
	for (int i = 0; i < nums.size(); i++)
	{
		cout << nums[i] << ' ';
	}
	cout << endl;
}

int main() {
	int n;
	cout << "请输入n" << endl;
	cin >> n;
	cout << "漂亮数组为" << endl;
	traverse(beautifulArray(n));
	system("pause");
	return 0;
}