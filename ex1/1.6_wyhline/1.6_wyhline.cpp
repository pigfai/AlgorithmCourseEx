#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include<cmath>
#include<iomanip>
#define MAXN 100
using namespace std;
int n;
double a[MAXN], b[MAXN], k[MAXN];
double f(double x) {
    double minn = 100;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        double temp = k[i] * (x - a[i]) * (x - a[i]) + b[i];   // ki(x-ai)^2 + bi
        if (temp < minn) {
            minn = temp;
            cnt = i;
        }
    }    //cnt记住最小值的下标
    double t = 2 * k[cnt] * (x - a[cnt]); //导数
    return sqrt(1 + t * t);
}

double simpson(double a, double b) {      //Simpson公式
    double mid = (a + b) / 2;
    return (f(a) + 4 * f(mid) + f(b)) * (b - a) / 6;
}

double compare_asr(double a, double b, int dep, double eps, double ans) {
    double mid = (a + b) / 2;
    double left = simpson(a, mid);
    double right = simpson(mid, b);
    if (dep >= 10 && fabs(left + right - ans) <= 15 * eps) {
        return left + right + (left + right - ans) / 15;
    } //确认精度
    return compare_asr(a, mid, dep + 1, eps / 2, left) + compare_asr(mid, b, dep + 1, eps / 2, right);     //精度不够则递归调用
}
double wyhline(double a, double b, double eps) {  // x从0-100 精度设定10的-6次方
    double simpson_dis = simpson(a, b);
    return compare_asr(a, b, 0, eps, simpson_dis);
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> k[i] >> a[i] >> b[i];
    }
    cout << wyhline(0, 100, 1e-6) << endl;
    system("pause");
    return 0;
}