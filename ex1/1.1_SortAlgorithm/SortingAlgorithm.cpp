#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<windows.h>
#include <vector>
using namespace std;

void show(long R[]) {
    cout << "输入n显示从n开始的10个数" << endl;
    long n;
    cin >> n;
    for (int i = n;  i < n + 10; i++) {
        cout << R[i]<<" ";
    }
    cout << endl;
}
/*
    冒泡排序
*/
void Bubblesort(long R[], long n)
{
    for(long i=1;i<n;i++)
    {								//i表示趟数,最多n-1趟
        for(long j=n-1;j>=i;j--)
        {
            if(R[j]<R[j-1])			//发生逆序
            {
                long t=R[j];
                R[j]=R[j-1];
                R[j-1]=t;
            }
        }
    }
}

/*
	直接插入排序
*/
void insertsort(long R[], long n)
{

    for(long i=1;i<n;i++)			//i表示插入次数,共进行n-1次插入
    {
        long temp=R[i];				//把待排序元素赋给temp
        long j=i-1;
        while((j>=0)&&(temp<R[j]))
        {
            R[j+1]=R[j];j--;		//顺序比较和移动
        }
        R[j+1]=temp;
    }
}

/*
	快速排序
*/
void quicksort(long R[], long left, long right)
{
    long i=left,j=right;
    long temp=R[i];
    while(i<j)
    {
        while((R[j]>temp)&&(j>i))
        {
            j=j-1;
        }
        if(j>i)
        {
            R[i]=R[j];
            i=i+1;
        }
        while((R[i]<=temp)&&(j>i))
        {
            i=i+1;
        }
        if(i<j)
        {
            R[j]=R[i];
            j=j-1;
        }
    }
    //二次划分得到基准值的正确位置
    R[i]=temp;
    if(left<i-1)
        quicksort(R,left,i-1);		//递归调用左子区间
    if(i+1<right)
        quicksort(R,i+1,right);		//递归调用右子区间
}


/*
	归并排序, 使用IDE是vs2019 新建long数组temp在赋值时会有写入的错误，使用容器vector可以解决问题
*/
void Merge(vector<long>& input, long left, long mid, long right, vector<long> temp) {
    long i = left;				// i是第一段序列的下标
    long j = mid + 1;			// j是第二段序列的下标
    long k = 0;					// k是临时存放合并序列的下标

    // 扫描第一段和第二段序列，直到有一个扫描结束
    while (i <= mid && j <= right) {
        // 判断第一段和第二段取出的数哪个更小，将其存入合并序列，并继续向下扫描
        if (input[i] <= input[j]) {
            temp[k++] = input[i++];
        }
        else {
            temp[k++] = input[j++];
        }
    }
    // 若第一段序列还没扫描完，将其全部复制到合并序列
    while (i <= mid) {
        temp[k++] = input[i++];
    }

    // 若第二段序列还没扫描完，将其全部复制到合并序列
    while (j <= right) {
        temp[k++] = input[j++];
    }

    k = 0;
    // 将合并序列复制到原始序列中
    while (left <= right) {
        input[left++] = temp[k++];
    }
}

// 归并排序
void MergeSort(vector<long>& input, long left, long right, vector<long> temp) {
    if (left < right) {
        long mid = (right + left) >> 1;
        MergeSort(input, left, mid, temp);
        MergeSort(input, mid + 1, right, temp);
        Merge(input, left, mid, right, temp);
    }
}

// 归并排序
void mergesort(vector<long>& input) {
    // 在排序前，先建好一个长度等于原数组长度的临时数组，避免递归中频繁开辟空间
    vector<long> temp(input.size());
    MergeSort(input, 0, input.size() - 1, temp);
}


/*
	操作选择函数
*/
void operate(long a[], int n)
{
    //每次重新赋予R 新数组 保证下一次排序的数组是打乱的
    char ch;
    cout << "请选择排序算法：\t";
    cin >> ch;
    switch(ch){
        case '1':
        {
            long* R1 = new long[n];
            for(long i = 0; i < n; i ++)
            {
                R1[i] = a[i];
            }
            long t1 = GetTickCount64();
            Bubblesort(R1, n);
            long t2 = GetTickCount64();
            long dif = t2-t1;
            cout << "冒泡排序所用时间：  " << dif << " 毫秒" << endl;
            cout << endl;
            show(R1);
            operate(a, n);
            break;
        }
        case '2':
        {
            long* R2 = new long[n];
            for(long i = 0; i < n; i ++)
            {
                R2[i] = a[i];
            }
            long t1 = GetTickCount64();
            insertsort(R2, n);
            long t2 = GetTickCount64();
            long dif = t2 - t1;
            cout << "直接插入排序所用时间：  " << dif << " 毫秒" << endl;
            cout << endl;
            show(R2);
            operate(a, n);
            break;
        }
        case '3':
        {
            long* R3 = new long[n];
            for(long i = 0; i < n; i ++)
            {
                R3[i] = a[i];
            }
            long t1 = GetTickCount64();
            quicksort(R3, 0, n - 1);
            long t2 = GetTickCount64();
            long dif = t2 - t1;
            cout << "快速排序所用时间：  " << dif << " 毫秒" << endl;
            cout << endl;
            show(R3);
            operate(a, n);
            break;
        }
        case '4':
        {
            vector<long> R4(n);
            for(long i = 0; i < n; i ++)
            {
                R4[i] = a[i];
            }
            long t1 = GetTickCount64();
            mergesort(R4);
            long t2 = GetTickCount64();
            long dif = t2 - t1;
            cout << "归并排序所用时间：  " << dif << " 毫秒" << endl;
            cout << endl;
            cout << "输入n显示从n开始的10个数" << endl;
            long n1;
            cin >> n1;
            if (n1 >= R4.size() || n1 < 0) { cout << "vetcor下标越界" << endl; break; } //要设置n1大小 否则会内存溢出直接退出
            for (long i = n1; i < n1 + 10; i++) {
                cout << R4[i] << " ";
            }
            cout << endl;
            operate(a, n);
            break;
        }
        case '0':
            break;
        default:
        {
            cout << "输入错误，请选择正确的操作！" << endl;
            operate(a, n);
            break;
        }
    }
    
}

/*
	主函数
*/
int main() {
    cout<<"1 --- 冒泡排序"<<endl;
    cout<<"2 --- 直接插入排序"<<endl;
    cout<<"3 --- 快速排序"<<endl;
    cout<<"4 --- 归并排序"<<endl;
    cout<<"0 --- 退出程序"<<endl;
    cout<<"===================================================="<<endl;
    cout << "请输入要产生的随机数的个数：";
    int n;
    cin >> n;
    cout << endl;
    long *a = new long [n];
    srand((unsigned int)time(NULL));
    for (long i = 0; i < n; i++)
    {

        long num = rand() % 32767 - 16383;   //rand()所能返回的最大数值，值为32767, 在测试10w数据中发现，再减去一半保证正负都有
        int mul = rand() % 100 + 1;  //再扩大倍数
        a[i] = num * mul;
    }
    operate(a, n);
    system("pause");
    return 0;
}