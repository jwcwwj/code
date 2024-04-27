//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>

using namespace std;

char* Mystrcpy(char* dest, const char* src)
{
	assert(dest && src);   //断言
	char* tmp = dest;
	while (*dest++ = *src++)
	{
		;
	}
	return tmp;
}

template <class T>
class Vector
{
public:
	//迭代器
	typedef T* iterator;
	typedef const T* const_iterator;

	//默认构造函数
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}

	//构造：n个val
	//Vector(size_t n,T& val = T())//匿名对象具有常性，没有const会报错，报错为：默认参数无法从int转化为T&
	Vector(size_t n, const T& val = T())   //匿名对象具有常性
		:_start(new T[n])		//申请能够存放n个元素的空间
		, _finish(_start + n)
		, _endOfStorage(_start + n)		//_finish
	{
		for (size_t i = 0; i < n; ++i)
		{
			_start[i] = val;
		}
	}

	//拷贝构造
	Vector(const Vector<T>& v)
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		size_t n = v.capacity();
		_start = new T[n];
		for (size_t i = 0; i < v.size(); ++i)
		{
			_start[i] = v[i];
		}
		_finish = _start + v.size();
		_endOfStorage = _start + n; //_start + capacity()
	}

	/* 
	//如果使用iterator做迭代器，会导致初始化的迭代器区间[first,last)只能是vector的迭代器
	//重新声明迭代器，迭代器区间[first,last]可以是任意容器的迭代器
	template <class inputIterator>
	Vector(inputIterator first, inputIterator last)
		: _start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		//[first,last)
		reserve(last - first);
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}
	*/

	//析构函数
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
	}

	/*
	//赋值运算符
	//传统写法
	Vector<T>& operator=(const Vector<T>& v)
	{
		if (this != &v)
		{
			delete[] _start;
			size_t n = v.capacity();
			_start = new T[n];
			for (size_t i = 0; i < v.size(); i++)
			{
				_start[i] = v[i];
			}
			_finish = _start + v.size();
			_endOfStorage = _start + n;
		}
		return *this;
	}
	*/

	//赋值运算符现代写法
	void Swap(Vector<T>& v)			//引用，内部修改相当于外部修改
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endOfStorage, v._endOfStorage);
	}

	Vector<T>& operator=(Vector<T> v)	//值拷贝
	{
		Swap(v);
		return *this;
	}

	size_t size() const
	{
		return _finish - _start;
	}

	size_t capacity() const
	{
		return _endOfStorage - _start;
	}

	bool empty()
	{
		return _start == _finish;
	}

	iterator begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const iterator begin() const
	{
		return _start;
	}

	const iterator end() const
	{
		return _finish;
	}

	T& operator[](size_t pos)
	{
		if (pos >= 0 && pos <= size())
		{
			return _start[pos];
		}
	}

	const T& operator[](size_t pos) const
	{
		if (pos >= 0 && pos <= size())
		{
			return _start[pos];
		}
	}

	void reserve(size_t n)
	{
		if (n > capacity())
		{
			//保存原始的size
			size_t sz = size();
			//开空间
			T* arr = new T[n];
			//拷贝内容
			if (_start)
			{
				/*
				//自定义类型：浅拷贝  如果有资源，会产生资源被多次释放
				//memcpy(arr, _start, sizeof(T)*size());
				for (size_t i = 0; i < sz; i++)
					arr[i] = _start[i];
				delete[] _start;
				*/
				//深拷贝
				for (size_t i = 0; i < sz; i++)
				{
					//如果是自定义类型，调用赋值运算符重载函数
					//只要赋值运算符实现了深拷贝，此处即为深拷贝
					arr[i] = _start[i];
				}
				delete[] _start;
			}
			//更新
			_start = arr;
			_finish = _start + sz;		//空间变了，扩容_finish就变了
			_endOfStorage = _start + n;
		}
	}
//1.memcpy是内存的二进制格式拷贝，将一段内存空间中内容原封不动的拷贝到另外一段内存空间中
//2.如果拷贝的是内置类型的元素，memcpy即高效又不会出错，但如果拷贝的是自定义类型元素，
//并且自定义类型元素中涉及到资源管理时，就会出错，因为memcpy的拷贝实际是浅拷贝。
//结论：如果对象中涉及到资源管理时，千万不能使用memcpy进行对象之间的拷贝，
//因为memcpy是浅拷贝，否则可能会引起内存泄漏甚至程序崩溃。

	void resize(size_t n, const T& val = T())
	{
		//n > capacity 增容
		if (n > capacity())
		{
			reserve(n);
		}
		//szie < n < capacity [size,n - 1] 多出来的部分填充val
		if (n > size())
		{
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}
		//n <= size，只修改size
		_finish = _start + n;
	}

	void insert(iterator pos, const T& val)
	{
		//有效区间:[0,size]
		if (pos >= _start && pos <= _finish)
		{
			//检查容量
			if (_finish == _endOfStorage)
			{
				//保存元素的个数
				size_t num = pos - _start;
				//增容会导致迭代器失效，增容要更新迭代器
				size_t n = _endOfStorage == nullptr ? 1 : 2 * capacity();
				reserve(n);
				//增容之后更新pos
				pos = _start + num;    //增容之后_start,_finish,_endOfStorage都自动更新了，而pos没有改变，不变的是_star和pos的相对位置关系
			}
			//移动元素:从后向前移动
			iterator end = _finish;
			while (end != pos)
			{
				*end = *(end - 1);
				end--;
			}
			//插入新的元素
			*pos = val;
			//更新
			++_finish;
		}
	}

	//删除
	iterator erase(iterator pos)
	{
		//检查位置
		if (pos < _finish && pos >= _start)
		{
			//移动元素:从前向后移动
			iterator start = pos + 1;
			while (start != _finish)
			{
				*(start - 1) = *start;
				start++;
			}
			//更新
			_finish--;
		}
		return pos;   //返回删除后的下一个位置
	}

	//尾插
	void push_back(const T& val)
	{
		//检查容量
		if (_finish == _endOfStorage)
		{
			//增容
			size_t newC = _endOfStorage == nullptr ? 1 : 2 * capacity();
			reserve(newC);   //预留空间 
		}

		//插入
		*_finish = val;
		//更新size
		_finish++;
	}

	void pop_back()
	{
		erase(end() - 1);
	}

private:
	iterator _start;		//指向数据块的开始
	iterator _finish;		//指向有效数据的尾
	iterator _endOfStorage;	//指向存储容量的尾
};

class String
{
public:
	String(const char* ptr = " ")
		:_ptr(new char[strlen(ptr) + 1])
	{
		strcpy(_ptr, ptr);
	}

	~String()
	{
		if (_ptr)
		{
			delete[] _ptr;
			_ptr = nullptr;
		}
	}

	String(const String& str)
		:_ptr(new char[strlen(str._ptr) + 1])
	{
		strcpy(_ptr, str._ptr);
	}

	String& operator=(const String& str)
	{
		if (this != &str)
		{
			delete[] _ptr;
			_ptr = new char[strlen(str._ptr) + 1];
			strcpy(_ptr, str._ptr);
		}
		return *this;
	}

private:
	char* _ptr;
};


struct A
{
	A(int a = 1)		//必须有无参构造
		:_a(a)
	{
		cout << "A(int)" << endl;
	}
	int _a = 10;
};

template <class T>
void printVector(const Vector<T>& v)
{
	typename Vector<T>::const_iterator it = v.begin();

	while (it != v.end())
	{
		cout << *it << " ";
		//*it = T();
		it++;
	}
	cout << endl;
}

template <class T>
void printForVector(const Vector<T>& v)
{
	for (const auto& e : v)    //这里的const要自己加，不加的话推导出来的为int，vector中的内容就可以修改了。
	{
		cout << e << " ";
		//cout << typeid(e).name() << " ";
		//e = T();   
	}
	cout << endl;
}

//c++中的vector类没有提供<<运算符
template <class T>
ostream& operator<<(ostream out, Vector<T>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		out << v[i] << " ";			//类型T的<<运算符也必须重载
	}

	out << endl;
	return out;
}

int main()
{
	Vector<int> v1(5,10);
	//Vector<int> v2(v1.begin(), v1.end());
	for (const auto& ch : v1)
		cout << ch << " ";
	cout << endl;
	vector<vector<int>> v2;
	return 0;
}