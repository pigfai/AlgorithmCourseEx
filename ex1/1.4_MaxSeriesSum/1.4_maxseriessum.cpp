#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<random>
#define TOTALRAND 100 
#define TOTALRANDMINUS 50  //定义随机的范围 //减去一半，保证负数，范围在-50，50之间
using namespace std;

int merge_1(vector<int>& a, int mid) //合并函数
{
	int max_l = -9999, max_r = -9999;
	int sum_l = 0, sum_r = 0;
	for (int i = mid; i >= 0; i--) { //寻找包括mid在内左边最大的序列
		sum_l += a[i];
		if (sum_l > max_l) max_l = sum_l;
	}
	for (int j = mid + 1; j < a.size(); j++) { //寻找包括mid在内左边最大的序列
		sum_r += a[j];
		if (sum_r > max_r) max_r = sum_r;
	}
	return (max_l+max_r);
}

int SeriesSum(vector<int>& a) {

	if (a.size() == 1) {
		return a[0];
	}
	int mid = a.size() / 2 - 1; //size为偶数，mid为中点左边；size为奇数，mid为中点-1  mid作为下标-1
	vector<int> left;  //mid+1作为空间 所以需要+1
	vector<int> right;

	int left_max, right_max, max_all;
	for (int k = 0; k < mid + 1; k++) {
		left.push_back(a[k]);
	}
	for (int j = mid + 1; j < a.size(); j++) {
		right.push_back(a[j]);
	}
	left_max = SeriesSum(left);
	right_max = SeriesSum(right);
	max_all = left_max > right_max ? left_max : right_max;
	int merge_sum = merge_1(a, mid);
	return max_all > merge_sum ? max_all : merge_sum;
}

int main() {
	int max_sum;
	int count;
	
	srand((unsigned int)time(NULL));
	cout << "请输入点的个数:";
	cin >> count;
	vector<int>a;
	cout << "序列为：";
	for (int i = 0; i < count; i++) {
		a.push_back(rand() % TOTALRAND - TOTALRANDMINUS);
		cout << a[i]<<",";
	}
	//{ -2,1,-3,4,-1,2,1,-5,4 };
	//pair<int, int> index;
	max_sum = SeriesSum(a);
	cout << "最大子序列和为:" << max_sum << endl;
	system("pause");
	return 0;
}