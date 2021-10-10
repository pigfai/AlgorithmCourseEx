#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<windows.h>
#include <vector>
#define MAXN 1000
using namespace std;

int a[MAXN];  //序列 全局修改
vector<int>temp;

void traverse(vector<int> nums)   //输出
{
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << ' ';
    }
    cout << endl;
}

void antiPosition(int n, int x) {  // x位置取反，同时修改a 和temp数值
    x = n - x;
    if (x > n) {
        cout << "取位大于序列" << endl;
        return;
    }
    if (a[x] == 0) {
        a[x] = 1;
    }else a[x] = 0;

    if ((x + 1) % 2 == 0) { //偶数位置
        if (temp[x] == 2) {
            temp[x] = 0;
        }
        else {
            temp[x] == 2;
        }
    }
    else {
        if (temp[x] == 1) {
            temp[x] = 0;
        }
        else {
            temp[x] = 1;
        }
    }
}


void contribute(int n) {    //根据下标判断贡献值,转换到vector temp

    for (int index = 0; index < n; index++) {
        if ((index+1) % 2 == 0) {
            if (a[index] == 1) {//偶数1贡献2
                temp.push_back(2);         
            } else temp.push_back(0);
        }
        else {
            if (a[index] == 1) {//奇数1贡献1
                temp.push_back(1);
            }else temp.push_back(0);//贡献0
        }       
    }
}


int force(int l, int r) {  //暴力求解法

    int result = 0;
    for (int i=l; i <= r; i++) {
        if (i == r) {
            if (temp[i] == 0)
                result++;
            break;
        }
        int sum = temp[i];
        if (sum % 3 == 0) result++;
        for (int j = i+1; j <= r; j++) {
            sum += temp[j];
            if (sum % 3 == 0) result++;
        }
    }
    return result;
}

int merge() {
    return 0;
}
/*
int isMulTripe(int left, int right) {
    if (left == right) {  //结束条件
        
    }
    int sum3=0;
    for (int i = left; i <= right; i++) {
        sum3 += temp[i];
    }
    int mod = sum3 % 3;

    int mid = (left + right) / 2;
    vector<int> left_array;
    vector<int> right_array;
    copy(temp.begin(), temp.begin() + mid + 1, left_array.begin()); //copy函数左闭右闭
    copy(temp.begin() + mid + 1 , temp.end(), right_array.begin());

    
    int left_ans = isMulTripe(left, mid);
    int right_ans = isMulTripe(mid + 1, right);

    return 0;
}*/

int main() {
    int n, m;
	cin >> n >> m;       //输入 n m
	for (int i = 0; i < n; i++) {
		cin >> a[i];          //只输入 0 和 1 的序列
	}
    contribute(n);
    traverse(temp);

    while (m--)
    {
        int c; cin >> c;
        if (c == 1) {
            int x;
            cin >> x;
            antiPosition(n, x);
            traverse(temp);
        }
        else if (c == 2) {
            int l, r;
            cin >> l >> r;
            cout << force(n - r, n - l);
        }
    }
	system("pause");
	return 0;
}