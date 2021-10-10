#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;
#define TOTALNUM 10000 //数组的个数
#define TOTALRAND 1000 //随机的范围
//由于题目中为自然数，所以先设计背景为随机生成1000以内的1万个数字。
//可以通过宏定义修改
void ModeMul(int a[],int n) {
    int result[TOTALRAND] = {0}; //定义一个1000全0的数组用来计重复的个数
    for (int i = 0; i < n; i++) {
        int index = a[i];
        result[index]++;         //数组的大小作为 计数数组的下标  计数++
    }
    int maxNum = 0;
    vector<int> maxMode;         //众数不唯一，用容器push
    for (int j = 0; j < TOTALRAND; j++) {
        if (result[j] > maxNum) {   //换众数的时候 清空容器，再加入
            maxNum = result[j];
            maxMode.clear();
            maxMode.push_back(j);
        }
        else if (result[j] == maxNum) {  //相同众数时 push容器
            maxMode.push_back(j);
        }
    }
    cout << "众数是   ";
    for (int k = 0; k < maxMode.size(); k++) {
        cout << maxMode[k] << "    ";
    }
    cout << endl;
    cout << "重数是： " << maxNum << endl;
}

int main(){
    srand((unsigned int)time(NULL));
    int* a = new int[TOTALNUM];
    for (int i = 0; i < TOTALNUM; i++)
    {
        int n = rand() % TOTALRAND;
        a[i] = n;
    }
    cout << "随机生成1000以内的1万个数字" << endl;
    ModeMul(a, TOTALNUM);
    system("pause");
    return 0;
}