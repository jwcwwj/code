# 1.priority_queue的介绍

1.优先队列是一种容器适配器，根据严格的弱排序标准，它的第一个元素总是它所包含的元素中最大的。

2.此上下文类似于堆，在堆中可以随时插入元素，并且只能检索最大堆元素(优先队列中位于顶部的元素)。

3.优先队列被实现为容器适配器，容器适配器即将特定容器类封装作为其底层容器类，priority_queue提供一组特

定的成员函数来访问其元素。元素从特定容器的“尾部”弹出，其称为优先队列的顶部。

4.底层容器可以是任何标准容器类模板，也可以是其他特定设计的容器类。容器应该可以通过**随机访问迭代器**访

问，并支持以下操作：

​		4.1empty()：检测容器是否为空

​		4.2size()：返回容器中有效元素个数

​		4.3front()：返回容器中第一个元素的引用

​		4.4push_back()：在容器尾部插入元素  

​		4.5pop_back()：删除容器尾部元素

5.标准容器类vector和deque满足这些需求。默认情况下，如果没有为特定的priority_queue类实例化指定容器

类，则使用vector。

6.需要支持随机访问迭代器，以便始终在内部保持堆结构。容器适配器通过在需要时自动调用算法函数

make_heap、push_heap和pop_heap来自动完成此操作。



# 2.priority_queue的使用

优先级队列底层是堆实现的。（默认情况下priority_queue是 一个大堆）

优先级队列默认使用vector作为其底层存储数据的容器，在vector上又使用了堆算法将vector中元素构造成堆的结

构，因此priority_queue就是堆，所有需要用到堆的位置，都可以考虑使用priority_queue。  

| 函数声明                                       | 接口说明                                          |
| ---------------------------------------------- | ------------------------------------------------- |
| priority_queue() / priority_queue(first, last) | 构造一个空的优先级队列                            |
| empty()                                        | 检测优先级队列是否为空，是放回true，否则返回false |
| top()                                          | 返回优先级队列中最大（最小）元素，即堆顶元素      |
| push(x)                                        | 在优先级队列中插入元素x                           |
| pop()                                          | 删除优先级队列中最大（最小）元素，即堆顶元素      |



```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <functional>	//greater算法的头文件

using namespace std;

//priority_queue的第三个参数
//greater按 > 进行比较，建小堆
//less按 < 进行比较，建大堆

//仿函数类模板
template <class T>
struct Greater
{
	//在类中重载函数运算符
	bool operator()(const T& val1, const T& val2)
	{
		return val1 > val2;		//没有{}会报错，不知道为啥
	}
};

//大堆	内置类型
void test1()
{
	priority_queue<int> q;	//可以存放自定义类型，自定义类型必须支持大小关系的比较（比较规则）
	q.push(100);
	q.push(1);
	q.push(150);
	q.push(10);
	q.push(20);

	while (!q.empty())
	{
		cout << q.top() << " ";		//堆顶，整个优先队列的最值（默认是最大值）
		//输出：150 100 20 10 1
		q.pop();
	}

	cout << endl;
}
//输出结果：
//150 100 20 10 1

struct A
{
	A(int a)
		:_a(a)
	{}

	//建大堆
	bool operator<(const A& a) const		//匿名对象具有常性
	{
		return _a < a._a;
	}

	//建小堆
	bool operator>(const A& a) const
	{
		return _a > a._a;
	}

	//友元函数可以直接在类的内部声明处实现，不需要在同一作用域类的外部实现
	friend ostream& operator<<(ostream& _cout, const A& a)
	{
		_cout << a._a;
		return _cout;
	}

private:
	int _a;
	//自定义成员的变量，可以重载 <<（输出运算符），提高类的封装性和安全性，把成员变量变为私有的。（使用友元在类外定义）
};

//大堆 自定义类型
void test2()
{
	priority_queue<A> q;
	q.push(A(1));			//匿名对象具有常性
	q.push(A(2));
	q.push(A(3));
	q.push(A(4));

	while (!q.empty())
	{
		cout << q.top() << " ";	//4 3 2 1
		q.pop();
	}

	cout << endl;
}
//输出结果：
//4 3 2 1

//小堆 内置类型
void test3()
{
	priority_queue<int, vector<int>, Greater<int>> q;	//使用自己的类模板仿函数
	//priority_queue<int,vector<int>,greater<int>> q;		//按小堆进行创建
	//greater提供一个大于比较，建小堆，默认是按照小于来比较，建大堆
	q.push(61);			//匿名对象具有常性
	q.push(22);
	q.push(3);
	q.push(41);

	while (!q.empty())
	{
		cout << q.top() << " ";	//1 2 3 4
		q.pop();
	}

	cout << endl;
}
//输出结果：
//3 22 41 61

//小堆 自定义类型	
void test4()
{
	//如果在priority_queue中放自定义类型的数据，
	//用户需要在自定义类型中提供> 或者< 的重载.
	priority_queue<A, vector<A>, Greater<A>> q;
	q.push(A(1));			//匿名对象具有常性
	q.push(A(2));
	q.push(A(3));
	q.push(A(4));

	while (!q.empty())
	{
		//输出a._a
		cout << q.top() << " ";	//1 2 3 4
		q.pop();
	}

	cout << endl;
}
//输出结果：
//1 2 3 4

void test5()
{
	//使用类模板仿函数：
	Greater<int> g;
	bool ret = g.operator()(10, 20);
	ret = g(10, 20);	//简写形式		仿函数不是函数，是重载括号运算符
	cout << ret << endl;   //0		表示第一个参数小于第二个参数
}
//输出结果：
//0

int main()
{
	test1();	//大堆	内置类型
	test2();	//大堆	自定义类型
	test3();	//小堆	内置类型
	test4();	//小堆	自定义类型
	test5();

	return 0;
}
```



# 3.力扣

## 215.数组中的第K个最大元素

题目：

给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

**提示：**

- `1 <= k <= nums.length <= 105`
- `-104 <= nums[i] <= 104`

```c++
示例 1:

输入: [3,2,1,5,6,4], k = 2
输出: 5
示例 2:

输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4
```

```c++
//方法1：使用priority_queue优先级队列
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q;

        for(const auto& e :nums)
            q.push(e);
        
        while(!q.empty() && k > 1)
        {
            q.pop();
            --k;
        }

        return q.top();
    }
};

class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		//将数组中的元素先放入优先级队列中
		priority_queue<int> p(nums.begin(), nums.end());		//priority_queue的迭代器区间构造
	
   		//将优先级队列中前k-1个元素删除掉
		for(int i= 0; i < k - 1; ++i)
			p.pop();
	
    	return p.top();
	}
};
```

```c++
方法2：基于快速排序的选择方法		算法导论9.2
class Solution {
public:
    int quickselect(vector<int> &nums, int l, int r, int k) {
        if (l == r)
            return nums[k];
        int partition = nums[l], i = l - 1, j = r + 1;
        while (i < j) {
            do i++; while (nums[i] < partition);
            do j--; while (nums[j] > partition);
            if (i < j)
                swap(nums[i], nums[j]);
        }
        if (k <= j)return quickselect(nums, l, j, k);
        else return quickselect(nums, j + 1, r, k);
    }

    int findKthLargest(vector<int> &nums, int k) {
        int n = nums.size();
        return quickselect(nums, 0, n - 1, n - k);
    }
};
```

```c++
方法3：堆排序
class Solution {
public:
    void maxHeapify(vector<int>& a, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) {
            largest = l;
        } 
        if (r < heapSize && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(a[i], a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int>& a, int heapSize) {
        for (int i = heapSize / 2; i >= 0; --i) {
            maxHeapify(a, i, heapSize);
        } 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
            swap(nums[0], nums[i]);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};
```



# 4.priority_queue的实现

底层是一个顺序表，因为支持随机访问，不能使用链表实现。

堆的操作：

​	push：尾插、向上调整

​	pop：arr[0]和arr[size - 1]进行交换，尾删，向下调整

​	top：arr[0]或者front

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <functional>	//greater算法的头文件
	
using namespace std;

//建大堆
template <class T, class Container = vector<T>, class Compare = less<T> >
class PriorityQueue
{
public:
	//向上调整	用于入队尾插之后向上调整保持大堆性质
	void shiftUp(int child)		//这里的child是索引下标
	{
		int parent = (child - 1) / 2;		//找到给定节点的父节点的索引
		//调整
		while (child > 0)
		{
			//if (v[parent] < v[child])
			if (_cmp(v[parent], v[child]))
			{
				//把大的向树的根部靠近
				swap(v[parent], v[child]);
				//更新：子节点调整到子节点的父节点	父节点调整到父节点的父节点
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				//如果满足了父节点的值大于子节点的值，表示上面的值都满足大堆的情况（原因：是在大堆的基础上进行尾插进行调整的）
				break;		//或者 return;		//这里没有break不影响最终结果，但是影响性能
		}
	}

	//向下调整 用于出队首尾元素交换之后，尾删最后一个元素（实际没有删除，只是调整队列的大小），然后队首元素向下调整保持大堆的性质
	void shiftDown(int parent)
	{
		int child = parent * 2 + 1;
		//int child = 2 * parent + 1;		//初始化是左孩子
		while (child < v.size())		//左孩子存在保证这个节点存在子孩子，然后才能比较
		{
			//从左右孩子中找到最大值
			//if (child + 1 < v.size() && v[child] < v[child + 1])
			if (child + 1 < v.size() && _cmp(v[child], v[child + 1]))	//保证右孩子存在，在左孩子和右孩子中找到大的值和父节点进行交换
				//右孩子存在且右孩子的值大于左孩子的值
				++child;
			//if (v[parent] < v[child])
			if (_cmp(v[parent], v[child]))
			{
				//父节点小于孩子节点，进行交换
				swap(v[parent], v[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;		//这里没有break不影响最终结果，但是影响性能
		}
	}

	//构造函数	创造空的优先级队列
	PriorityQueue()
		:v()
	{}

	//迭代器区间构造
	template <class Iterator>
	PriorityQueue(Iterator first, Iterator last)
		: v(first, last)		//比如传参是v.begin(), v.end()
	{
		//将v中的结构调整成大堆的结构
		int count = v.size();
		//找到第一个非叶子节点
		int root = ((count - 2) >> 1);	//等价于int count = (count - 2) / 2;
		for (; root >= 0; --root)
			shiftDown(root);		//从第一个非叶子节点向下调整建大堆
	}

	//是在一个已近满足了大堆性质的队列上进行尾插
	void push(const T& val)	
	{
		//尾插
		v.push_back(val);
		//向上调整
		shiftUp(v.size() - 1);		//参数是尾插的val的下标索引
	}

	void pop()
	{
		if (empty())
			return;
		//交换首尾元素
		swap(v[0], v[v.size() - 1]);
		//或者	swap(v.front(), v.back());
		//尾删
		v.pop_back();
		//向下调整
		shiftDown(0);
	}

	T& top()
	{
		return v[0];
		//return v.front();		也可以
	}

	size_t size()
	{
		return v.size();
	}

	bool empty()
	{
		return v.empty();
	}

private:
	Container v;
	//vector<T> v;		//使用vector的原因是list不支持随机访问（交换就是随机访问）
	Compare _cmp;
};


class A
{
	friend ostream& operator<<(ostream& out, A& a);
public:
	A(int a)
		:_a(a)
	{}

	bool operator<(const A& a) const		//匿名对象具有常性
	{
		return _a < a._a;
	}

	bool operator>(const A& a) const
	{
		return _a > a._a;
	}

private:
	int _a;
}; 

ostream& operator<<(ostream& out, A& a)
{
	out << a._a;
	return out;
}

int main() 
{
	//加了第三个参数仿函数就不支持自定义类型了，不知道为啥
	//仿函数的优点：在不修改源码的情况下，可以修改代码本身的逻辑
	//仿函数类属于STL中的一个组件
	//创建一个优先级队列，并使用默认的比较器（less）
	PriorityQueue<int> pq1;

	// 将一些元素插入队列
	pq1.push(10);
	pq1.push(30);
	pq1.push(20);
	pq1.push(50);
	pq1.push(40);

	cout << pq1.size() << endl;		//5

	while (!pq1.empty())
	{
		cout << pq1.top() << " ";		//50 40 30 20 10
		pq1.pop();
	}

	cout << endl << pq1.size() << endl;		//0

	//创建一个优先级队列，并使用自定义的比较器（greater）
	PriorityQueue<int, vector<int>, greater<int>> pq2;		//小堆

	pq2.push(30);
	pq2.push(50);
	pq2.push(80);
	pq2.push(20);
	pq2.push(90);

	cout << pq2.size() << endl;		//5

	while (!pq2.empty())
	{
		cout << pq2.top() << " ";		//20 30 50 80 90
		pq2.pop();
	}

	cout << endl << pq2.size() << endl;		//0

	PriorityQueue<A, vector<A>, greater<A>> q1;		//第二个参数缺省，用vector<T>代替
	q1.push(A(1));
	q1.push(A(3));
	q1.push(A(2));
	q1.push(A(4));

	cout << q1.size() << endl;	//4

	while (!q1.empty())
	{
		cout << q1.top() << " ";	//1 2 3 4
		q1.pop();
	}

	cout << endl << q1.size() << endl;	//0

	int arr[] = { 5,2,6,7,4,3,0,1 };
	PriorityQueue<int> q(arr, arr + sizeof(arr) / sizeof(arr[0]));
	while (!q.empty())
	{
		cout << q.top() << " ";		//7 6 5 4 3 2 1 0
		q.pop();
	}

	cout << endl;

	vector<A> a = {A(40), A(20), A(30), A(50), A(80), A(60) };

	PriorityQueue<A, vector<A>, greater<A>> qq(a.begin(), a.end());

	cout << qq.size() << endl;	//6
	while (!qq.empty())
	{
		cout << qq.top() << " ";		//20 30 40 50 60 80
		qq.pop();
	}

	cout << endl << qq.size() << endl;	//0
	return 0;
}
//输出结果：
//5
//50 40 30 20 10
//0
//5
//20 30 50 80 90
//0
//4
//1 2 3 4
//0
//7 6 5 4 3 2 1 0
//6
//20 30 40 50 60 80
//0
```



# 5.容器适配器

## 5.1什么是容器适配器

适配器模式是把一种容器经过简单的转换变成另外一个容器。

转换后的容器叫适配器容器或者容器适配器，stack、queue、priority_queue都是适配器容器。

适配器是一种设计模式(设计模式是一套被反复使用的、多数人知晓的、经过分类编目的、代码设计经验的总结)，

该种模式是将一个类的接口转换成客户希望的另外一个接口。



## 5.2STL标准库中stack和queue的底层结构

虽然stack和queue中也可以存放元素，但在STL中并没有将其划分在容器的行列，而是将其称为**容器适配器**，这是

因为stack和队列只是对其他容器的接口进行了包装，STL中stack和queue默认使用deque（双端队列）。

![image-20230629162402603](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629162402603.png)

![image-20230629162330566](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629162330566.png)

![image-20230629162348685](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629162348685.png)



## 5.3deque（双端队列）的简单介绍

### 5.3.1deque的原理

deque(双端队列)：是一种双开口的"连续"空间的数据结构，双开口的含义是：可以在头尾两端进行插入和删除操

作，且时间复杂度为O(1)，与vector比较，头插效率高，不需要搬移元素；与list比较，空间利用率比较高。

![image-20230629164350857](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629164350857.png)

deque并不是真正连续的空间，而是由一段段连续的小空间拼接而成的，实际deque类似于一个动态的二维数组。

（缓冲区存放数据）

![image-20230629164525654](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629164525654.png)

双端队列底层是一段假象的连续空间，实际是分段连续的，为了维护其“整体连续”以及随机访问的假象，落在了

deque的迭代器身上，因此deque的迭代器设计就比较复杂，如下图所示：

![image-20230629165016140](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629165016140.png)

那deque是如何借助其迭代器维护其假想连续的结构呢？  

![image-20230629165221223](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629165221223.png)

![image-20230629220140166](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230629220140166.png)

双端队列是一个物理上不连续、逻辑上连续的线性结构。

双端队列中间插入比较麻烦。



### 5.3.2双端队列

与vector比较，deque的优势是：头部插入和删除时，不需要搬移元素，效率特别高，而且在扩容时，也不需要搬

移大量的元素，因此其效率是比vector高的。

与list比较，其底层是连续空间，空间利用率比较高，不需要存储额外字段。

但是，deque有一个致命缺陷：不适合遍历，因为在遍历时，deque的迭代器要频繁的去检测其是否移动到某段小

空间的边界，导致效率低下，而序列式场景中，可能需要经常遍历，因此在实际中，需要线性结构时，大多数情况

下优先考虑vector和list，deque的应用并不多，而能看到的一个应用就是，STL用其作为stack和queue的底层数

据结构。（stack和queue也不支持遍历。）



### 5.3.3为什么选择deque作为stack和queue的底层默认容器

stack是一种后进先出的特殊线性数据结构，因此只要具有push_back()和pop_back()操作的线性结构，都可以作为

stack的底层容器，比如vector和list都可以；

queue是先进先出的特殊线性数据结构，只要具有push_back和pop_front操作的线性结构，都可以作为queue的

底层容器，比如list。但是STL中对stack和queue默认选择deque作为其底层容器，主要是因为：

1.stack和queue不需要遍历(因此stack和queue没有迭代器)，只需要在固定的一端或者两端进行操作。

2.在stack中元素增长时，deque比vector的效率高(扩容时不需要搬移大量数据)；queue中的元素增长时，deque

不仅效率高，而且内存使用率高。

结合了deque的优点，而完美的避开了其缺陷。



# 6.stack、queue和priority_queue的对比和vector、list、deque的优缺点对比

| 适配器容器名称      | stack                                                        | queue                                                        | priority_queue（优先级队列）                                 |
| ------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| STL中的默认实现容器 | deque                                                        | deque                                                        | vector（堆）                                                 |
| 可以作为底层的容器  | vector、list、deque                                          | list、deque（vector不能实现，因为vector没有提供pop_front()接口） | vector、deque（list不能实现，因为list不支持随机访问，不满足优先级队列对于底层容器的要求） |
| 特点                | 1.stack不需要随机访问；（vector的随机访问的优势在这体现不出来，vector的增容代价比较大，双端队列增容代价比较小）                                         2.尾插和尾删；（vector、list、deque三个的尾插和尾删时间复杂度都是O(1)） | 1.queue不需要在中间位置进行操作；（底层容器中间性能低在这里没有影响）                          2.满足尾插和头删；（vector不满足头删，vector可以在任意位置插入和删除，但没有实现特定的头删） | 1.优先级队列要满足堆的结构，堆要随机访问，优先级队列也就要随机访问（list不满足随机访问，所以不行，双端队列支持随机访问，但性能不如vector）                                       2.增容不是随时发生的，只有空间满了才发生增容，但随机访问要经常使用的（插入和删除要调整，调整就要随机访问）；（deque增容比vector代价小）                                          3.总结：优先级队列主要是看中随机访问的，增容不是一个关注的重点； |
| 底层容器的选择对比  | 1.vector相比较deque的劣势：vector的增容代价比较大，要进行深拷贝，deque的增容代价比较小；（从增容来说双端队列更优一些）                              2.list相比较deque的劣势：list的空间不连续，都是小空间（相比较双端队列空间更小），list相比较deque更容易造成内存碎片，deque每次申请的空间相比较list更大，deque造成内存碎片的概率比list更小； | list相比较deque的劣势：因为list要频繁的申请和释放空间，list的空间利用率比较低，容易造成内存碎片； | deque相比较vector的劣势：deque和vector都支持随机访问，但deque的随机访问性能不如vector；（deque随机访问是通过迭代器的换算的，要调整迭代器的位置，比较麻烦）（deuqe是物理上不连续，逻辑上连续的适配器容器） |



|                                                           | 优点                                                         | 缺点                                                         |
| --------------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| vector                                                    | 1.随机访问；               2. 尾部插入和删除时间复杂度是O(1) ；    3.每次都是申请大空间，空间利用率比较高，不容易造成内存碎片 | 1.不适合频繁的插入和删除，在尾部时间复杂度是O(1)，在其他地方时是O(N)；        2.增容的代价比较大，是深拷贝； |
| list                                                      | 1.插入和删除性能比较高，任意位置的插入和删除时间复杂度都是O(1)，适合频繁的修改元素； | 1.不支持随机访问；       2.空间利用率比较低，因为频繁的申请和释放空间，容易造成内存碎片； |
| deque（双端队列）（一个比较中庸的适配器容器，优势不明显） | 1.支持随机访问，性能略低于vector；      2.头部和尾部的插入和删除性能比较高，都是O(1)；    3.增容的代价比较小； | 1.中间位置操作性能比较低，都是O(N)；     2.和vector相比，空间不是完全连续的；（物理上不连续，逻辑上连续） |

总结：双端队列作为stack和queue的默认底层容器是因为stack和queue不需要迭代器访问，规避了双端队列迭代

器访问麻烦的缺点。



# 7.STL标准库中对于stack和queue的模拟实现

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <functional>	//greater算法的头文件
	
using namespace std;

//STL标准库中对于stack的模拟实现
template<class T, class Con = deque<T>>
//template<class T, class Con = vector<T>>
//template<class T, class Con = list<T>>
class Stack
{
public:
	Stack() {}
	void push(const T& x) { _c.push_back(x); }
	void pop() { _c.pop_back(); }
	T& top() { return _c.back(); }
	const T& top()const { return _c.back(); }
	size_t size()const { return _c.size(); }
	bool empty()const { return _c.empty(); }
private:
	Con _c;
};

int main()
{
	Stack<int> s;
	for (int i = 0; i < 5; ++i)
		s.push(i);

	while (!s.empty())
	{
		cout << s.top() << " ";		//4 3 2 1 0
		s.pop();
	}

	cout << endl;

	return 0;
}
//输出结果：
//4 3 2 1 0
```

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <functional>	//greater算法的头文件
	
using namespace std;

//STL标准库中对于queue的实现
template<class T, class Con = deque<T>>
//template<class T, class Con = list<T>>
class Queue
{
public:
	Queue() {}
	void push(const T& x) { _c.push_back(x); }
	void pop() { _c.pop_front(); }
	T& back() { return _c.back(); }
	const T& back()const { return _c.back(); }
	T& front() { return _c.front(); }
	const T& front()const { return _c.front(); }
	size_t size()const { return _c.size(); }
	bool empty()const { return _c.empty(); }
private:
	Con _c;
};

int main()
{
	Queue<int> q;
	for (int i = 0; i < 5; ++i)
		q.push(i);

	while (!q.empty())
	{
		cout << q.front() << " ";		//0 1 2 3 4
		q.pop();
	}

	cout << endl;

	return 0;
}
//输出结果：
//0 1 2 3 4
```

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <stack>
//#include <queue>
#include <functional>	//greater算法的头文件
	
using namespace std;

//类名可以和标准库中的一样，但是要去掉相关类的头文件，否则会起冲突。
template<class T, class Con = deque<T>>
//template<class T, class Con = list<T>>
class queue
{
public:
	queue() {}
	void push(const T& x) { _c.push_back(x); }
	void pop() { _c.pop_front(); }
	T& back() { return _c.back(); }
	const T& back()const { return _c.back(); }
	T& front() { return _c.front(); }
	const T& front()const { return _c.front(); }
	size_t size()const { return _c.size(); }
	bool empty()const { return _c.empty(); }
private:
	Con _c;
};

int main()
{
	queue<int> q;
	for (int i = 0; i < 5; ++i)
		q.push(i);

	while (!q.empty())
	{
		cout << q.front() << " ";		//0 1 2 3 4
		q.pop();
	}

	cout << endl;

	return 0;
}
//输出结果：
//0 1 2 3 4
```

