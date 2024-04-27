# 1.stack的介绍

1.stack是一种容器适配器，专门用在具有后进先出操作的上下文环境中，其删除只能从容器的一端进行以及元素

的插入与提取操作。

2.stack是作为容器适配器被实现的，容器适配器即是对特定类封装作为其底层的容器，并提供一组特定的成员函

数来访问其元素，将特定类作为其底层的，元素特定容器的尾部(即栈顶)被压入和弹出。

3.stack的底层容器可以是任何标准的容器类模板或者一些其他特定的容器类，这些容器类应该支持以下操作：

​	3.1empty：判空操作

​	3.2back：获取尾部元素操作

​	3.3push_back：尾部插入元素操作

​	3.4pop_back：尾部删除元素操作

4.标准容器vector、deque、list均符合这些需求，默认情况下，如果没有为stack指定特定的底层容器，默认情况

下使用deque（双端队列）。



# 2.stack的使用

| 函数说明 | 接口说明                |
| -------- | ----------------------- |
| stack()  | 构造空的栈              |
| empty()  | 检测stack是否为空       |
| size()   | 返回stack中元素的个数   |
| top()    | 返回栈顶元素的引用      |
| push()   | 将元素val压入stack中    |
| pop()    | 将stack中尾部的元素弹出 |

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

using namespace std;

int main()
{
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	cout << "出栈前的size : " << st.size() << endl;		//4

	while (!st.empty())
	{
		cout << st.top() << " ";  //4 3 2 1
		st.pop();
	}
	cout << endl;

	cout << "出栈后的size : " << st.size() << endl;		//0

	return 0;
}
//输出结果：
//出栈前的size : 4
//4 3 2 1
//出栈后的size : 0
```



# 3.力扣题

## 155.最小栈

题目：

设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。 



提示：

-231 <= val <= 231 - 1
pop、top 和 getMin 操作总是在 非空栈 上调用
push, pop, top, and getMin最多被调用 3 * 104 次 

```c++
示例 1：
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
```

```c++
class MinStack {
public:
    stack<int> _st;
    stack<int> _min_st;

    MinStack() {
        
    }
    
    void push(int val) {
        _st.push(val);
        
        if(_min_st.empty() || val <= _min_st.top())
            _min_st.push(val);
    }
    
    void pop() {
        if(_min_st.top() == _st.top())
            _min_st.pop();
        _st.pop();
    }
    
    int top() {
        return _st.top();
    }
    
    int getMin() {
        return _min_st.top();
    }
};

/**
//测试：
 * Your MinStack object will be instantiated and called as such:		
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```



## 946.验证栈序列

题目：

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 

给定 pushed 和 popped 两个序列，每个序列中的 值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 true；否则，返回 false 。 



提示：

1 <= pushed.length <= 1000
0 <= pushed[i] <= 1000
pushed 的所有元素 互不相同
popped.length == pushed.length
popped 是 pushed 的一个排列 

```c++
示例 1：
输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

示例 2：
输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
输出：false
解释：1 不能在 2 之前弹出。
```

```c++
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        //栈存储输入数组的元素
        stack<int> st;
        int pushIdx = 0;
        int popIdx = 0;

        //将输入数组中的元素全部入栈
        while(pushIdx < pushed.size())
        {
            //每次从输入数组中入栈一个元素
            st.push(pushed[pushIdx++]);

            //栈不为空的时候，且输出数组的元素和栈顶元素相等就出栈，直到栈为空或者输出数组的元素和栈顶元素不相等
            while(!st.empty() && st.top() == popped[popIdx])        //不能在这里++，必须是相等之后++
            {
                st.pop();
                popIdx++;
            }
        }

        if(st.empty())
            return true;
        else
            return false;
    }
};
```



## 150.逆波兰表达式求值

题目：

给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。

请你计算该表达式。返回一个表示表达式值的整数。

注意：

有效的算符为 '+'、'-'、'*' 和 '/' 。
每个操作数（运算对象）都可以是一个整数或者另一个表达式。
两个整数之间的除法总是 向零截断 。
表达式中不含除零运算。
输入是一个根据逆波兰表示法表示的算术表达式。
答案及所有中间计算结果可以用 32 位 整数表示。 



提示：

1 <= tokens.length <= 104
tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围 [-200, 200] 内的一个整数


逆波兰表达式：

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

```c++
示例 1：
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

示例 2：
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6

示例 3：
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
```

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(const auto& ch : tokens)
        {
            if(ch == "+" || ch == "-" || ch == "*" || ch == "/")
            {
                //遇到运算符执行运算，获取两次栈顶中的元素
                int right = st.top();
                st.pop();
                int left = st.top();
                st.pop();
                if(ch == "+")
                    st.push(left + right);
                else if(ch == "-")
                    st.push(left - right);
                else if(ch == "*")
                    st.push(left * right);
                else  
                    st.push(left / right);
            }
            else
                st.push(stoi(ch));        //字符串类型string是字母，将字符类型string的字母转换为数字，只能用于字母转数字
                //st.push(atoi(ch));      //将c语言中的字符转换为数字，不能用于c++中的string类型
        }

        return st.top();
    }
};
```



## 232.用栈实现队列

题目：

请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

实现 MyQueue 类：

void push(int x) 将元素 x 推到队列的末尾
int pop() 从队列的开头移除并返回元素
int peek() 返回队列开头的元素
boolean empty() 如果队列为空，返回 true ；否则，返回 false

说明：

你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。



提示：

1 <= x <= 9
最多调用 100 次 push、pop、peek 和 empty
假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作）


进阶：

你能否实现每个操作均摊时间复杂度为 O(1) 的队列？换句话说，执行 n 个操作的总时间复杂度为 O(n) ，即使其中一个操作可能花费较长时间。

```c++
示例 1：
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
```

```c++

```



# 4.实现stack

顺序表的优点：空间连续，只存放数据本身，不用存放指向，占用的空间更小，每次申请的空间比较大，相比较链

表来说不容易产生内存碎片。

实现stack（栈）优先选择顺序表，链表也可以实现。



stack的实现：

1.顺序表：

​	push（入栈）：push_back	头插

​	pop（出栈）：pop_back()	头删

​	top（获取栈顶元素）：back	获取最后一个元素

2.链表（单链表）

​	push（入栈）：push_front	头插

​	pop（出栈）：pop_front	头删

​	top（获取栈顶元素）	获取第一个节点的值

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

using namespace std;

//借助STL中的vector实现stack
template <class T>
class Stack
{
public:
	Stack()
	{}

	//下面的操作都是O(1)的操作
	//入栈
	void push(const T& val)
	{
		//尾插
		_st.push_back(val);
	}

	//出栈
	void pop()
	{
		//尾删
		_st.pop_back();
	}

	//获取栈顶元素
	T& top()
	{
		//获取vector的尾部元素
		return _st.back();
	}

	//获取size
	size_t size() const
	{
		return _st.size();
	}

	bool empty() const
	{
		return _st.empty();
	}

private:
	vector<T> _st;
};

int main()
{
	Stack<int> st;
	for (int i = 0; i < 5; ++i)
	{
		st.push(i);
	}

	cout << st.size() << endl;		//5

	while (!st.empty())
	{
		cout << st.top() << " ";	//4 3 2 1 0
		st.pop();
	}
	cout << endl;

	cout << st.size() << endl;		//0

	return 0;
}
//输出结果：
//5
//4 3 2 1 0
//0
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

using namespace std;

//借助STL中的list实现stack
template <class T>
class Stack
{
public:
	Stack()
	{}

	//下面的操作都是O(1)的操作
	//入栈
	void push(const T& val)
	{
		//尾插
		_l.push_front(val);
		//_l.push_back(val);	//也可以，下面也要使用pop_back()和back()接口
	}

	//出栈
	void pop()
	{
		//尾删
		_l.pop_front();
	}

	//获取栈顶元素
	T& top()
	{
		//获取vector的尾部元素
		return _l.front();
	}

	//获取size
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
	Stack<int> st;
	for (int i = 0; i < 8; ++i)
	{
		st.push(i);
	}

	cout << st.size() << endl;		//8

	while (!st.empty())
	{
		cout << st.top() << " ";	//7 6 5 4 3 2 1 0
		st.pop();
	}
	cout << endl;

	cout << st.size() << endl;		//0

	return 0;
}
//输出结果：
//8
//7 6 5 4 3 2 1 0
//0
```



















