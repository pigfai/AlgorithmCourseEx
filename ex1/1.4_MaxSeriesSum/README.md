### 1.4 最大子序列和

#### 问题描述

随机给出一个整数序列，选出其中连续且
非空的一段使得这段和最大


#### 思路步骤

和1.3一样，分左右2个区，分别递归求最大值

合并函数不同  左区需要从mid点开始往前求最大和，右区同理，再相加，和最大值比较


#### 重点问题和解决方法：

1. 序列需要正负都有 否则题没有意义

2. 可以用贪心算法求解，第一个数字必定是正数，如果求和的过程产生负数，找再后的正数做头