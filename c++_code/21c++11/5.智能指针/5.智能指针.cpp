#include <iostream>
#include <memory>		//库里面实现的智能指针库
#include <thread>
#include <atomic>	//原子库
#include <mutex>	//互斥锁

using namespace std;

//自动释放不需要的内存，相当于java中的垃圾回收机制
//java中不需要手动释放内存，c++中需要手动释放内存
//c++中的智能指针是自动释放内存的，模拟了常规指针的行为

//智能指针实现：
//1.实现RAII思想
//2.实现指针功能：实现*和->操作
template <class T>
class SmartPtr
{
public:
	//RAII
	//构造函数：获取资源的管理权
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{}

	//析构函数：释放资源
	~SmartPtr()
	{
		if (_ptr)
			delete _ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

private:
	T* _ptr;
};

class A
{
//private:
public:
	int _a = 10;

	~A()
	{
		cout << "~A()" << endl;
	}
};

void test1()
{
	/*
	//错误写法：
	int* ptr = new int;
	SmartPtr<int> sp1(ptr);
	SmartPtr<int> sp2(ptr);
	这个不叫立即初始化，这个析构会造成资源重复释放
	*/

	//智能指针：编译器调用析构自动释放内存，不存在内存泄漏的问题
	SmartPtr<int> sp(new int);	//资源获取立即初始化
	SmartPtr<int> sp3((int*)malloc(sizeof(int)));
	SmartPtr<A> sp4(new A);
	
	*sp = 10;		//修改新开空间的内容
	sp4->_a = 100;
	(*sp4)._a = 1000;

	//普通指针：手动释放内存，存在内存泄漏问题
	int* p = new int;
	A* pa = new A;
	*p = 1;
	pa->_a = 5;
	(*pa)._a = 55;
	delete p;		//普通指针要delete，智能指针是编译器调用析构释放资源，普通指针释放内存不一定成功，智能指针不存在这种情况。
	delete pa;


	return;


	cout << "test" << endl;
}

//auto_ptr的使用
void test2()
{
	auto_ptr<int> ap(new int);
	auto_ptr<int> ap2(new int(3));
	*ap = 10;
	*ap = 100;		

	//auto_ptr<int> ap3 = ap;		//移动赋值

	cout << *ap << endl;
}

//auto_ptr：模拟实现
template <class T>
class autoPtr
{
public:
	//RAII
	//构造函数：获取资源的管理权
	autoPtr(T* ptr)
		:_ptr(ptr)
	{}

	//析构函数：释放资源
	~autoPtr()
	{
		if (_ptr)
			delete _ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	//拷贝构造  移动拷贝  管理权转移
	autoPtr(autoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = nullptr;
	}

	//重载 = 运算符  移动赋值  管理权转移
	autoPtr<T>& operator=(autoPtr<T>& ap)
	{
		if (this != &ap)
		{
			if(_ptr)
				delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = nullptr;
		}
		return *this;
	}

private:
	T* _ptr;
};

//unique_ptr的使用
void test3()
{
	unique_ptr<A> up1(new A);
	//unique_ptr<A> up2(up1);		//error，unique_ptr的拷贝构造函数是已经删除的函数

	unique_ptr<A> up3(new A);
	//up1 = up3;					//error，unique_ptr的赋值运算符是已经删除的函数
}

//unique_ptr的实现
template<class T>
class UniquePtr
{
public:
	UniquePtr(T* ptr)
		:_ptr(ptr)
	{}

	~UniquePtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}

	//防拷贝和赋值
	UniquePtr(const UniquePtr<T>& up) = delete;
	UniquePtr<T>& operator=(const UniquePtr<T>& up) = delete;

private:
	T* _ptr;
};

//shared_ptr的使用
void test4()
{
	//支持拷贝和赋值
	shared_ptr<A> sp1(new A);
	cout << sp1.use_count() << endl;	//1

	shared_ptr<A> sp2(sp1);		//拷贝		引用计数	创建几个对象释放几次
	cout << sp1.use_count() << endl;	//2
	cout << sp2.use_count() << endl;	//2

	shared_ptr<A> sp3(new A); 
	cout << sp1.use_count() << endl;	//2
	cout << sp2.use_count() << endl;	//2
	cout << sp3.use_count() << endl;	//1 

	sp3 = sp1;		//赋值成功
	cout << sp1.use_count() << endl;	//3
	cout << sp2.use_count() << endl;	//3
	cout << sp3.use_count() << endl;	//3 
	//use_count：有多少个智能指针管理这个资源
}

//SharedPtr的实现
template <class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		, _countPtr(new size_t(1))
	{}

	//拷贝构造
	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _countPtr(sp._countPtr)
	{
		//计算器累加
		++(*_countPtr);
	}

	//赋值操作
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		//if (this != &sp)
		//判断管理的是否为同一份资源（对象一样资源一定一样，对象不一样资源也可能一样）
		//资源不一样对象一定不一样，对象不一样资源可能一样
		if(_ptr != sp._ptr)
		{
			//计数器自减
			//如果计数器为0的时候，当前对象是最后一个管理此资源的对象
			if (--(*_countPtr) == 0)
			{
				//处理当前对象的资源
				delete _ptr;
				delete _countPtr;
			}

			_ptr = sp._ptr;
			_countPtr = sp._countPtr;

			//计数器累加
			++(*_countPtr);
		}
		return *this;
	}

	~SharedPtr()
	{
		//计数器自减
		if (--(*_countPtr) == 0)
		{
			delete _ptr;
			delete _countPtr;
			_ptr = nullptr;
			_countPtr = nullptr;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	//获取引用计数
	size_t getCount()
	{
		return *_countPtr;
	}

//private:
	T* _ptr;
	size_t* _countPtr;	//计数器指针
};

void test5()
{
	SharedPtr<A> sp1(new A);
	cout << *(sp1._countPtr) << endl;	//1

	SharedPtr<A> sp2(new A);
	cout << *(sp1._countPtr) << endl;	//1
	cout << *sp2._countPtr << endl;		//1

	SharedPtr<A> copy(sp1);
	cout << *(sp1._countPtr) << endl;	//2
	cout << *(sp2._countPtr) << endl;	//1
	cout << *(copy._countPtr) << endl;	//2

	sp1 = sp2;
	cout << *(sp1._countPtr) << endl;	//2
	cout << *(sp2._countPtr) << endl;	//1
	cout << *(copy._countPtr) << endl;	//2
}



void fun6(const SharedPtr<A>& sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		SharedPtr<A> copy(sp);
	}
}

//多线程会出问题
void test6()
{
	SharedPtr<A> sp(new A);
	int n = 10000;		//数字越大多线程出现的问题越多（（多线程）线程是不安全）
	thread t1(fun6, ref(sp), n);		//ref表示引用
	thread t2(fun6, ref(sp), n);		//ref表示引用
	t1.join();
	t2.join();

	cout << sp.getCount() << endl;	
}


//SharedPtr：
//1.支持赋值和拷贝
//2.通过引用计数保证资源被正确且唯一的释放
//3.多线程中，通过对引用计数进行串行操作，保证计数更新正确
//4.每一个资源都有自己独立的引用计数

//解决多线程会出问题，加锁
//SharedPtr的实现
template <class T>
class SharedPtr1
{
public:
	SharedPtr1(T* ptr = nullptr)
		:_ptr(ptr)
		, _countPtr(new size_t(1))
		,_mtx(new mutex)
	{}

	//拷贝构造
	SharedPtr1(const SharedPtr1<T>& sp)
		:_ptr(sp._ptr)
		, _countPtr(sp._countPtr)
		,_mtx(sp._mtx)
	{
		//计算器累加
		//++(*_countPtr);
		addCount();
	}

	//赋值操作
	SharedPtr1<T>& operator=(const SharedPtr1<T>& sp)
	{
		//if (this != &sp)
		//判断管理的是否为同一份资源（对象一样资源一定一样，对象不一样资源也可能一样）
		//资源不一样对象一定不一样，对象不一样资源可能一样
		if (_ptr != sp._ptr)
		{
			//计数器自减
			//如果计数器为0的时候，当前对象是最后一个管理此资源的对象
			//if (--(*_countPtr) == 0)
			if(subCount() == 0)
			{
				//处理当前对象的资源
				delete _ptr;
				delete _countPtr;

				//释放锁
				delete _mtx;
			}

			_ptr = sp._ptr;
			_countPtr = sp._countPtr;

			//计数器累加
			//++(*_countPtr);
			addCount();
		}
		return *this;
	}

	~SharedPtr1()
	{
		//计数器自减
		//if (--(*_countPtr) == 0)
		if(subCount() == 0)
		{
			delete _ptr;
			delete _countPtr;

			//释放锁
			delete _mtx;

			_ptr = nullptr;
			_countPtr = nullptr;
			_mtx = nullptr;		//置锁为空
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	//获取引用计数
	size_t getCount()
	{
		return *_countPtr;
	}


	//加锁操作
	size_t addCount()
	{
		_mtx->lock();
		++(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//减锁操作
	size_t subCount()
	{
		_mtx->lock();
		--(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//private:
	T* _ptr;
	size_t* _countPtr;	//计数器指针

	//每一份资源有一个独立的锁
	mutex* _mtx;
};



void fun7(const SharedPtr1<A>& sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		//修改引用计数是线程安全的，数据的操作不是线程安全的（需要自己保证数据的操作是安全的）
		//保证数据的操作是安全的：在数据类中实现的对应操作中加锁
		SharedPtr1<A> copy(sp);

		copy->_a++;		//数据是一个竞争的关系
	}
}

//加锁之后的测试，解决多线程引用计数的问题，解决了多线程安全的问题（使计数器变成串行操作）
void test7()
{
	SharedPtr1<A> sp1(new A);
	SharedPtr1<A> sp2(new A);
	int n = 10000;		

	//{t1,t2} 和 {t3,t4} 在修改引用计数时是并行的
	//t1 和 t2 在修改引用计数时是串行的
	//t3 和 t4 在修改引用计数时是串行的
	thread t1(fun7, ref(sp1), n);		//ref表示引用
	thread t2(fun7, ref(sp1), n);		//ref表示引用
	thread t3(fun7, ref(sp2), n);		//ref表示引用
	thread t4(fun7, ref(sp2), n);		//ref表示引用
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	cout << sp1.getCount() << endl;
	cout << sp2.getCount() << endl;

	cout << sp1->_a << endl;
	cout << sp2->_a << endl;
}

//循环引用
struct ListNode
{
	//shared_ptr<ListNode> _next;
	//shared_ptr<ListNode> _prev;

	//解决循环引用的方法：使用弱指针
	//weak_ptr只能在自定义类型中使用
	//weak_ptr不能单独使用
	weak_ptr<ListNode> _next;	//赋值
	weak_ptr<ListNode> _prev;

	int _data;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

void test8()
{
	shared_ptr<ListNode> n1(new ListNode);		//栈上的智能指针对象
	shared_ptr<ListNode> n2(new ListNode);

	cout << n1.use_count() << endl;
	cout << n2.use_count() << endl;

	n1->_next = n2;
	n2->_prev = n1;

	//cout << n1.use_count() << endl;
	//cout << n2.use_count() << endl;

	//weak_ptr不能单独使用
	//weak_ptr<A> wp;
	//wp = n1;	//error
	shared_ptr<int> sp1(new int);
	weak_ptr<int> wp(sp1);
	cout << wp.use_count() << endl;

	shared_ptr<ListNode>* sp = new shared_ptr<ListNode>;	//堆上的智能指针对象
	delete sp;
}

//删除器
template <class T>
struct DeleteDel
{
	void operator()(T* ptr)
	{
		delete ptr;	
	}
};

template <class T>
struct FreeDel
{
	void operator()(T* ptr)
	{
		free(ptr);
	}
};

//连续的空间
template <class T>
struct DeleteArrDel
{
	void operator()(T* ptr)
	{
		delete[] ptr;
	}
};

template <class T, class Del = DeleteDel<T>>
class SharedPtr2
{
public:
	/*
	SharedPtr2(T* ptr = nullptr)
		:_ptr(ptr)
		, _countPtr(new size_t(1))
		, _mtx(new mutex)
	{}
	*/

	SharedPtr2(T* ptr = nullptr, Del del = DeleteDel<T>)
		:_ptr(ptr)
		, _countPtr(new size_t(1))
		, _mtx(new mutex)
		,_del(del)
	{}

	//拷贝构造
	SharedPtr2(const SharedPtr2<T>& sp)
		:_ptr(sp._ptr)
		, _countPtr(sp._countPtr)
		, _mtx(sp._mtx)
	{
		//计算器累加
		//++(*_countPtr);
		addCount();
	}

	//赋值操作
	SharedPtr2<T>& operator=(const SharedPtr2<T>& sp)
	{
		//if (this != &sp)
		//判断管理的是否为同一份资源（对象一样资源一定一样，对象不一样资源也可能一样）
		//资源不一样对象一定不一样，对象不一样资源可能一样
		if (_ptr != sp._ptr)
		{
			//计数器自减
			//如果计数器为0的时候，当前对象是最后一个管理此资源的对象
			//if (--(*_countPtr) == 0)
			if (subCount() == 0)
			{
				//处理当前对象的资源
				//delete _ptr;
				_del(_ptr);	//通过删除器释放空间
				delete _countPtr;

				//释放锁
				delete _mtx;
			}

			_ptr = sp._ptr;
			_countPtr = sp._countPtr;

			//计数器累加
			//++(*_countPtr);
			addCount();
		}
		return *this;
	}

	~SharedPtr2()
	{
		//计数器自减
		//if (--(*_countPtr) == 0)
		if (subCount() == 0)
		{
			//delete _ptr;
			_del(_ptr);	//通过删除器释放空间
			delete _countPtr;

			//释放锁
			delete _mtx;

			_ptr = nullptr;
			_countPtr = nullptr;
			_mtx = nullptr;		//置锁为空
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	//获取引用计数
	size_t getCount()
	{
		return *_countPtr;
	}

	//加锁操作
	size_t addCount()
	{
		_mtx->lock();
		++(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//减锁操作
	size_t subCount()
	{
		_mtx->lock();
		--(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//private:
	T* _ptr;
	size_t* _countPtr;	//计数器指针

	//每一份资源有一个独立的锁
	mutex* _mtx;
	Del _del;	//删除器
};

//删除器
void test9()
{
	//SharedPtr2<A,DeleteArrDel<A>> sp(new A[100]);
	shared_ptr<A> sp1(new A[100], DeleteArrDel<A>());
	//shared_ptr<A> sp2(new A[100]);		//error
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();	
	//test8();
	test9();
	return 0;
}