#include <iostream>
#include<set>
#include<algorithm>
#include<vector>
#include<ctime>

using namespace std;

const int maxn = 10005;
const double PI = acos(-1.0);
const int point_max_loc = 1000;

typedef struct point
{
	int x;
	int y;
} point;

point p[maxn],ans[maxn],que[maxn];
set<pair<int, int> > s;
int n;
int top;
int visit[maxn], mark[maxn];
vector<int> stack(maxn,-1);
vector<int> stackfenzhi;
int judge(point p1, point p2, point p3)
{
	int flag = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
	if (flag > 0) return 1;
	else if (flag == 0) return 2;
	else return 0;
}


int Djudge(point a1, point a2, point a3)
{
	int calculate = a1.x*a2.y + a3.x*a1.y + a2.x*a3.y - a3.x*a2.y - a2.x*a1.y - a1.x*a3.y;
	return calculate;
}
bool cmpxy(const point a, const point b) //按x轴排序,如果x相同,按y轴排序
{
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.y < b.y;
}
void DealLeft(int first, int last)
{
	int max = 0, index = -1;
	int i = first;
	if (first < last)
	{
		for (i = first + 1; i < last; i++) //注意两端,对于first和last,没必要再进行计算
		{
			int calcu = Djudge(p[first], p[i], p[last]);
			if (calcu == 0) { visit[i] = 1;
			} //
			if (calcu > max)
			{
				max = calcu;
				index = i;
			}

		}
	}
	else
	{
		for (i = first + 1; i >last; i--) //如果first>last,重复上述过程,注意这里下界不是0.
		{
			int calcu = Djudge(p[first], p[i], p[last]);
			if (calcu == 0) { visit[i] = 1; 
			} //
			if (calcu > max)
			{
				max = calcu;
				index = i;
			}
		}
	}
	if (index != -1)
	{
		visit[index] = 1; //对取到的点进行标注  
		stackfenzhi.push_back(index);
		DealLeft(first, index);
		DealLeft(index, last);//分治的部分
	}
}


void swap(point p[], int i, int j)
{
	point tmp;
	tmp = p[i];
	p[i] = p[j];
	p[j] = tmp;
}
double multi(point p1, point p2, point p0) //极角的比较
{

		return ((p1.x - p0.x)*(p2.y - p0.y) - (p1.y - p0.y)*(p2.x - p0.x));
}
double distence(point p1, point p2) //p1,p2的距离
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
int cmp(const void *a, const void *b)
{
	point *c = (point *)a;
	point *d = (point *)b;
	double k = multi(*c, *d, p[0]);
	if (k<0) return 1;
	else if (k == 0 && distence(*c, p[0]) > distence(*d, p[0])) return 1; //极角相同，比距离
	else return -1;
}
void grahamscan(int n)
{
	int i, u;
	u = 0;
	for (i = 1; i <= n - 1; i++) //找到最左下的点p0
		if ((p[i].y < p[u].y) || (p[i].y == p[u].y&&p[i].x < p[u].x))
			u = i;
	swap(p, 0, u);
	qsort(p + 1, n - 1, sizeof(p[0]), cmp); //按极角排序
//	for (int i = 0; i < n; i++) {
//		cout << "(" << p[i].x << " , " << p[i].y << ") ";
//	}
	//sort(p, p + n-1, cmp);
	for (i = 0; i <= 2; i++) stack[i]=i; //p0,p1,p2入栈
	top = 2;
	for (i = 3; i <= n - 1; i++) //最终凸包的各顶点的编号依次存在stack[]中。
	{
		while (top >= 1&&multi(p[stack[top]],p[i], p[stack[top - 1]]) < 0) //弹出非左转的点
		{
			//if (top == 1)break;
			top--;
			//if (top == 0)break;
		}
		top++;
		stack[top] = i;
	}
}


double polygonArea(int n, point p[])
{
	double area;
	int i;
	area = 0;
	for (i = 1; i <= n; i++) {
		area += (p[stack[i - 1]].x * p[stack[i % n]].y - p[stack[i % n]].x * p[stack[i - 1]].y);
	}
	return fabs(area) / 2;
}

void rand100(point p[],int pointnum) {
	int num = 100;
	int x, y;
	point  temp[4];
	temp[0].x = 0;
	temp[0].y = 0;
	temp[1].x = 100;
	temp[1].y = 0;
	temp[2].x = 0;
	temp[2].y = 100;
	temp[3].x = 100;
	temp[3].y = 100;
	for (int i = 0; i < pointnum; i++) {
		x = rand() % num;
		y = rand() % num;
		p[i].x = x;
		p[i].y = y;
	}
	for (int i = 0; i < 4; i++) {
		x = rand() % pointnum;
		//y = rand() % num;
		p[x].x = temp[i].x;
		p[x].y = temp[i].y;
		//swap(p, x, y);
	}
}

void rand_suiji(point p[],int num) {
	int x, y;
	for (int i = 0; i < num ; i++) {
		x = rand() % point_max_loc;
		y = rand() % point_max_loc;
		p[i].x = x;
		p[i].y = y;
	}

}
void rand_suiji_num(point p[], int num) {
	int x, y;
	for (int i = 0; i < num ; i++) {
		x = rand() % num;
		y = rand() % num;
		p[i].x = x;
		p[i].y = y;
	}

}

int main()
{
	cout << "请输入坐标点的个数  ";
	cout << endl;
	cin >> n;
	//int num = 100;
	rand_suiji(p, n);
	//rand100(p, n);
	//rand_suiji_num(p, n);
	cout << endl;
	//for (int i = 0; i < n; i++) {
	//	cout << "("<<p[i].x << " , " << p[i].y <<") ";
	//}
		
	//cout << endl<<endl;
	cout << "请输入一个数，1表示蛮力法，2表示分治法，3表示Graham Scan法" << endl;
	int i;
	cin >> i;
	while (i > 0 && i < 4) {

		switch (i)
		{
		case 1:
		{
			//cout << "请输入各点的坐标 " << endl;
			//for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

			s.clear();
			clock_t starttime = clock();
			for (int i = 0; i < n; i++)
			{
				int t = 0;

				for (int j = 0; j < n; j++)
				{
					int flag = -1;
					if (i == j) continue;

					for (int k = 0; k < n; k++)
					{
						if (k == i || k == j) continue;

						if (flag == -1) flag = judge(p[i], p[j], p[k]);
						else
						{
							int temp = judge(p[i], p[j], p[k]);
							if (flag == temp || temp == 2) t = 1;
							else
							{
								t = 0;
								break;
							}
						}
					}

					if (t) s.insert(make_pair(p[j].x, p[j].y));
				}

				if (t) s.insert(make_pair(p[i].x, p[i].y));
			}
			cout << "蛮力法运行时间为： " << double(clock() - starttime) << " ms" << endl;
			set<pair<int, int> >::iterator it = s.begin();
		/*
			cout << "结果集合中点的坐标为：" << endl<<endl;

			while (it != s.end())
			{
				printf("(%d , %d) ", it->first, it->second);
				it++;
			}
			*/
			cout << endl;
			break;
		}
		case 2:
		{
			for (int i = 0; i < n; i++)
			{
				//cin >> p[i].x >> p[i].y;
				visit[i] = 0;
			}
			visit[0] = 1;
			visit[n - 1] = 1;
			sort(p, p + n, cmpxy);
			stackfenzhi.push_back(0);
			stackfenzhi.push_back(n-1);
			clock_t starttime = clock();
			DealLeft(0, n - 1); //上边
			DealLeft(n - 1, 0); //下包
			cout << "分治法运行时间为： " << double(clock() - starttime) << " ms" << endl;
			int t = 0;
			/*
			cout << "结果集合中点的坐标为：" << endl<<endl;
			/*
				for (int i = 0; i < n; i++)
			{
				if (visit[i] == 1)
				{
					
					cout << "(" << p[i].x << " , " << p[i].y << ") " ;
					
				}
			}
			
			
			for (int i = 0; i < stackfenzhi.size(); i++) {
				cout << "(" << p[stackfenzhi[i]].x << " , " << p[stackfenzhi[i]].y << ") ";
			}
			*/
			
			cout << endl;
			break;
		}
		case 3:
		
		{
			//int a;
			/*
			cout << "请输入各点的坐标 " << endl;
				int i;
				for (i = 0; i < n; i++)
					cin >> p[i].x >> p[i].y;
					*/
			clock_t starttime = clock();
			grahamscan(n);
			cout << "Graham Scan法运行时间为： " << double(clock() - starttime) << " ms" << endl;
			//	printf("%lf\n", polygonArea(n, p));
			vector<int>::iterator it = stack.begin();
			//cout << stack.size();
		/*
		    cout << "结果集合中点的坐标为：" << endl<<endl;
			//cout << stack.size() << endl;
			
			while (*it != -1)
			{
				printf("(%d , %d) ", p[*it].x, p[*it].y);
				it++;
			}
			*/
			cout << endl;

			break;
		}
		default:
			//cout << "byebye" << endl;
			break;
		}
		//cout << endl;
		cout << "请输入一个数，1表示蛮力法，2表示分治法，3表示Graham Scan法" << endl;
		cin >> i;
	}

	return 0;
}