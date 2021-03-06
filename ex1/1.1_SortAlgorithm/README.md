### 1.1 排序
#### 问题描述：

对随机生成的若干组整数序列（比如规模为1000个数，10000个数，100000个数）进行排序，排序算法使用四种方法，插入排序算法、合并排序算法和快速排序算法

#### 重点问题和解决方法：

1. 随机生成数字

使用rand() 生成，但是有局限在于 只能生成 0 - 32767 大小的范围，所以又进行了减法和缩放，获得了正负都有的随机数

long num = rand() % 32767 - 16383;

int mul = rand() % 100 + 1;

a[i] = num * mul;

2. 统计算法时间

使用  GetTickCount64();  毫秒级

3. 排序算法实现

冒泡排序+插入排序较为简单。

快速排序选择第一个作为比较的点，递归比较每次排序完，作比较的点都落在了最终的位置

归并排序

将序列分为 左右2个区间分别递归，合并函数 等于做简单的2个有序顺序表的合并：谁大谁加入

#### 时空复杂度和稳定性

1. 插入排序

空间 O(1) 平均时间是O(n^2)  

不稳定：如果有相同的元素可能在交换后移动位置，导致不稳定

2. 冒泡排序

空间O(1) 平均时间O(n^2) 最好可能O(n)

稳定：相同元素不会移动位置

3. 快速排序

空间O(logn) 需要递归栈 平均时间是O(nlog2n) 最坏O(n^2)

不稳定： 相同的元素会因为位置分割开

4. 归并排序

空间复杂度就是临时数组和递归时压入栈的数据占用的空间n + logn，所以空间复杂度为:O(n)  平均时间复杂度是O(nlogn)

#### 降序排列

如果改为降序

冒泡排序和插入排序：最内层修改比较符

快速排序和归并排序 分别在递归和合并时 修改比较符号
