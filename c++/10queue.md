# 1.queue的介绍

1.队列是一种容器适配器，专门用于在FIFO上下文(先进先出)中操作，其中从容器一端插入元素，另一端提取元

素。

2.队列作为容器适配器实现，容器适配器即将特定容器类封装作为其底层容器类，queue提供一组特定的成员函数

来访问其元素。元素从队尾入队列，从队头出队列。

3.底层容器可以是标准容器类模板之一，也可以是其他专门设计的容器类。该底层容器应至少支持以下操作:

empty：检测队列是否为空

size：返回队列中有效元素的个数

front：返回队头元素的引用

back：返回队尾元素的引用

push_back：在队列尾部入队列

pop_front：在队列头部出队列

4.标准容器类deque和list满足了这些要求。默认情况下，如果没有为queue实例化指定容器类，则使用标准容器

deque。（意思就是在list和deque都满足条件的时候使用deque）



# 2.queue的使用

| 函数声明 | 接口说明                                    |
| -------- | ------------------------------------------- |
| queue()  | 构造空的队列                                |
| empty()  | 检测队列是否为空，是返回true，否则返回false |
| size()   | 返回队列中有效元素的个数                    |
| front()  | 返回队头元素的引用                          |
| back()   | 返回队尾元素的引用                          |
| push()   | 在队尾将元素val入队列                       |
| pop()    | 在队头元素出队列                            |

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

using namespace std;

int main()
{
	queue<int> q;
	for (int i = 0; i < 5; ++i)
		//队尾元素入队
		q.push(i);

	cout << q.back() << endl;		//4
	cout << q.size() << endl;		//5

	while (!q.empty())
	{
		//获取队头元素
		cout << q.front() << " ";	//0 1 2 3 4
		q.pop();					//队头元素出队
	}
	cout << endl;

	cout << q.size() << endl;		//0

	return 0;
}
//输出结果：
//4
//5
//0 1 2 3 4
//0
```



# 3.力扣题

## 225.用队列实现栈

题目：

请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 

empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。

int pop() 移除并返回栈顶元素。

int top() 返回栈顶元素。

boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。


注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。

你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标

准的队列操作即可。

提示：

1 <= x <= 9

最多调用100 次 push、pop、top 和 empty

每次调用 pop 和 top 都保证栈不为空


进阶：你能否仅用一个队列来实现栈。

```c++
示例：
输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False
```

```c++
方法1：用两个队列实现栈
class MyStack {
public:
    MyStack() {

    }
    
    void push(int x) {
        q1.push(x);
    }
    
    int pop() {
        int res;
        int len = q1.size() - 1;
        while(len--)
        {
            //除了最后一个元素先入队q2再出队q1
            int temp = q1.front();
            q1.pop();
            q2.push(temp);
        }

        //q1中最后一个元素出队
        res = q1.front();
        q1.pop();
 
        /*
        //把q2的内容拷贝到q1;
        q1 = q2;

        //q2出队
        while(!q2.empty())
        {
            q2.pop();
        }
        */
        swap(q1, q2);

        return res;     //返回删除的栈顶元素
    }
    
    int top() {
        return q1.back();
    }
    
    bool empty() {
        return q1.empty();
    }

private:
    queue<int> q1;      //q1存放栈
    queue<int> q2;      //借助q2出栈
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

```c++
方法2： 用一个队列实现栈
class MyStack {
public:
    MyStack() {

    }
    
    void push(int x) {
        q.push(x);
    }
    
    int pop() {
        //除了最后一个元素全部先出队，记录元素再入队，最后一个元素出队
        //返回值是要删除的队头元素值
        int res;
        int len = q.size() - 1;
        while(len--)
        {
            int temp = q.front();
            q.pop();
            q.push(temp);
        }
        res = q.front();
        q.pop();
        return res;
    }
    
    int top() {
        return q.back();
    }
    
    bool empty() {
        return q.empty();
    }

private:
    queue<int> q;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```



# 4.queue的实现

queue的实现：

1..顺序表

​	push（入队）：push_back	尾插

​	pop（出队）：pop_front	头删		时间复杂度：O(N)

​	front：front

2.链表（含有尾指针的单链表）

​	push（入队）：push_back	尾插

​	pop（出队）：pop_front	头删

​	front：front

dueue优先选择性能高的，选择链表实现。



因为queue的接口中存在头删和尾插，因此使用vector来封装效率太低，故可以借助list来模拟实现queue。

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

using namespace std;

//借助STL中的list实现Queue
template <class T>
class Queue
{
public:
	Queue()
	{}

	void push(const T& val)
	{
		_l.push_back(val);
		//_l.push_front(val);		//也可以
	}

	void pop()
	{
		_l.pop_front();
		//_l.pop_back();
	}

	T& front()
	{
		return _l.front();
		//return _l.back();
	}

	T& back()
	{
		return _l.back();
		//retunr _l.front();
	}

	size_t size() const
	{
		return _l.size();
	}

	bool empty() const
	{
		return _l.empty();
	}

private:
	list<T> _l;
};

int main()
{
	Queue<int> q;
	for (int i = 0; i < 5; ++i)
		q.push(i);

	cout << q.back() << endl;		//4
	cout << q.size() << endl;		//5

	while (!q.empty())
	{
		cout << q.front() << " ";		//0 1 2 3 4
		q.pop();
	}

	cout << endl;

	cout << q.size() << endl;		//0

	return 0;
}
//输出结果：
//4
//5
//0 1 2 3 4
//0
```

