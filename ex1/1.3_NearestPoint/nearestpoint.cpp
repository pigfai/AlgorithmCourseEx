#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<random>
#define TOTALRAND 1000  //定义随机的范围，这里设定为1000
using namespace std;

class point
{
public:
	double x;
	double y;
	point() {}; //需要一个默认构造函数，否则在main中定义pair时会因为没默认函数报错
	point(double x, double y) :x(x), y(y) {}
};

double distance(const point& A, const point& B)//计算A和B之间的距离
{
	double dis = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
	return dis;
}

bool compare_x(const point& A, const point& B)//比较x坐标，A的x小返回true，A和B相等或B的x小返回false  是告诉sort函数排序方式
{
	if (A.x < B.x) {
		return true;
	}
	else return false;
	
}

bool compare_y(const point& A, const point& B)//比较y坐标，A的y小返回true，A和B的y相等或B的y小返回false 是告诉sort函数排序方式
{
	if (A.y < B.y) {
		return true;
	}
	else return false;
}

double NearestPointAll(vector<point> p, pair<point, point>& min_point)//穷举法
{
	double mindis = 9999999;
	for (int i = 0; i < p.size(); i++)
	{
		for (int j = i+1; j < p.size(); j++)   //避免自己和自己比
		{
			double d = distance(p[i], p[j]);
			if (d < mindis)
			{
				mindis = d;
				min_point = make_pair(p[i], p[j]);
			}
		}
	}
	return mindis;
}
double merge(vector<point>& points,vector<point>& points_y, double min_dis, int mid, pair<point, point>& min_point)
//合并函数  
{																						
	vector<point> left, right;
	for (int i = 0; i < points_y.size(); i++) //搜集左右两边在min_dis竖条内的点 把y排好序之后可以节省时间
	{
		if (points_y[i].x <= points[mid].x && points_y[i].x > points[mid].x - min_dis)
			left.push_back(points_y[i]);
		else if (points_y[i].x > points[mid].x && points_y[i].x < points[mid].x + min_dis)
			right.push_back(points_y[i]);
	}
	for (int i = 0; i < left.size(); i++)//遍历左边的点集合，与右边符合条件的计算距离
	{
		vector<point> metrix_right;
		for (int j = 0; j < right.size(); j++)
		{
			if (right[j].y <= left[i].y - min_dis) { continue; }
			else if(right[j].y > left[i].y - min_dis && right[j].y < left[i].y + min_dis)
			{
				metrix_right.push_back(right[j]);
			}
			else if (right[j].y >= left[i].y + min_dis) //已经按y排好序后，可以按照左边点y的大小 再继续画框
			{
				break;
			}
		}
		for (int k = 0; k < metrix_right.size(); k++) //遍历右边
		{
			if (distance(left[i], metrix_right[k]) < min_dis)
			{
				min_dis = distance(left[i], metrix_right[k]);
				min_point.first = left[i];
				min_point.second = right[k];
			}
		}

	}
	return min_dis;
}

double NearestPointDivide(vector<point>& points, vector<point>& points_y, pair<point, point>& min_point)//递归求解points中的最近点对，返回最近点对距离，min_point存储这个点对
{
	if (points.size() == 2)//递归到两个点结束
	{
		min_point.first = points[0];
		min_point.second = points[1];
		return distance(points[0], points[1]);
	}
	if (points.size() == 3)//三个点
	{
		double min_distance = min(distance(points[0], points[1]), min(distance(points[0], points[2]), distance(points[1], points[2])));
		if (distance(points[0], points[1]) == min_distance)
		{
			min_point.first = points[0];
			min_point.second = points[1];
		}
		else if (distance(points[0], points[2]) == min_distance)
		{
			min_point.first = points[0];
			min_point.second = points[2];
		}
		else
		{
			min_point.first = points[1];
			min_point.second = points[2];
		}
		return min_distance;
	}
	pair<point, point> temp_min_point1, temp_min_point2;
	int mid = points.size() / 2 - 1;//size为偶数，mid为中点左边；size为奇数，mid为中点-1  mid作为下标-1
	double left_dis, right_dis, min_dis;
	vector<point> left, left_y;  //mid+1作为空间 所以需要+1
	vector<point> right, right_y;
	//copy(points.begin(), points.begin() + mid + 1, left.begin()); //copy函数左闭右闭
	//copy(points.begin() + mid + 1 , points.end(), right.begin());
	for (int k = 0; k < mid + 1; k++) {
		left.push_back(points[k]);
	}
	for (int j = mid+1; j < points.size(); j++) {
		right.push_back(points[j]);
	}
	
	for (int i = 0; i < points_y.size(); i++)  //将按y排好序的数组以point[mid]分为两部分，分完后还是按y排好序的
	{
		if (points_y[i].x <= points[mid].x)
			left_y.push_back(points_y[i]);
		else
			right_y.push_back(points_y[i]);
	}
	left_dis = NearestPointDivide(left, left_y, temp_min_point1);
	right_dis = NearestPointDivide(right, right_y, temp_min_point2);  //分别递归 左右2个部分的最小值

	if (left_dis < right_dis) {                             //选出2个部分的最小值和最小点对
		min_dis = left_dis;
		min_point = temp_min_point1;
	}
	else 
	{
		min_dis = right_dis;
		min_point = temp_min_point2;
	}
	return merge(points, points_y, min_dis, mid, min_point);
}


int main()
{
	int count;
	double min_distance1, min_distance2;
	vector<point> points;
	vector<point> points_y;
	pair<point, point> min_point1, min_point2;
	srand((unsigned int)time(NULL));
	cout << "请输入点的个数:";
	cin >> count;
	for (int i = 0; i < count; i++)
	{
		int n_x = rand() % TOTALRAND;
		int n_y = rand() % TOTALRAND;
		cout << "第" <<i + 1<< "个点:";
		point p(n_x, n_y);
		cout << p.x << "," << p.y << endl;
		points.push_back(p);
		points_y.push_back(p);
	}
/*
	points.push_back(point(832, 611));
	points.push_back(point(389, 690)); 
	points.push_back(point(408, 959)); 
	points.push_back(point(721, 129));
	points.push_back(point(471, 562));
	points.push_back(point(630, 54));
	points.push_back(point(261, 118));
	points.push_back(point(382, 957));
	points.push_back(point(423, 39));
	points.push_back(point(988, 617));
	points_y.push_back(point(832, 611));
	points_y.push_back(point(389, 690));
	points_y.push_back(point(408, 959));
	points_y.push_back(point(721, 129));
	points_y.push_back(point(471, 562));
	points_y.push_back(point(630, 54));
	points_y.push_back(point(261, 118));
	points_y.push_back(point(382, 957));
	points_y.push_back(point(423, 39));
	points_y.push_back(point(988, 617));
*/
	sort(points.begin(), points.end(), compare_x);//把所有的点按x从小到大排序
	sort(points_y.begin(), points_y.end(), compare_y);//把左边的点按y从小到大排序
	cout << "穷举法：" << endl;
	min_distance1 = NearestPointAll(points, min_point1);
	cout << "最近点对为 (" << min_point1.first.x << "," << min_point1.first.y << "),(" << min_point1.second.x << "," << min_point1.second.y << ")" << endl;
	cout << "最近点对距离为: " << min_distance1 << endl;
	cout << "分治法：" << endl;
	min_distance2 = NearestPointDivide(points, points_y, min_point2);
	cout << "最近点对为 (" << min_point2.first.x << "," << min_point2.first.y << "),(" << min_point2.second.x << "," << min_point2.second.y << ")" << endl;
	cout << "最近点对距离为: " << min_distance2 << endl;
	system("pause");
	return 0;
}