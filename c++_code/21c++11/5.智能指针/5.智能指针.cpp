#include <iostream>
#include <memory>		//������ʵ�ֵ�����ָ���
#include <thread>
#include <atomic>	//ԭ�ӿ�
#include <mutex>	//������

using namespace std;

//�Զ��ͷŲ���Ҫ���ڴ棬�൱��java�е��������ջ���
//java�в���Ҫ�ֶ��ͷ��ڴ棬c++����Ҫ�ֶ��ͷ��ڴ�
//c++�е�����ָ�����Զ��ͷ��ڴ�ģ�ģ���˳���ָ�����Ϊ

//����ָ��ʵ�֣�
//1.ʵ��RAII˼��
//2.ʵ��ָ�빦�ܣ�ʵ��*��->����
template <class T>
class SmartPtr
{
public:
	//RAII
	//���캯������ȡ��Դ�Ĺ���Ȩ
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{}

	//�����������ͷ���Դ
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
	//����д����
	int* ptr = new int;
	SmartPtr<int> sp1(ptr);
	SmartPtr<int> sp2(ptr);
	�������������ʼ������������������Դ�ظ��ͷ�
	*/

	//����ָ�룺���������������Զ��ͷ��ڴ棬�������ڴ�й©������
	SmartPtr<int> sp(new int);	//��Դ��ȡ������ʼ��
	SmartPtr<int> sp3((int*)malloc(sizeof(int)));
	SmartPtr<A> sp4(new A);
	
	*sp = 10;		//�޸��¿��ռ������
	sp4->_a = 100;
	(*sp4)._a = 1000;

	//��ָͨ�룺�ֶ��ͷ��ڴ棬�����ڴ�й©����
	int* p = new int;
	A* pa = new A;
	*p = 1;
	pa->_a = 5;
	(*pa)._a = 55;
	delete p;		//��ָͨ��Ҫdelete������ָ���Ǳ��������������ͷ���Դ����ָͨ���ͷ��ڴ治һ���ɹ�������ָ�벻�������������
	delete pa;


	return;


	cout << "test" << endl;
}

//auto_ptr��ʹ��
void test2()
{
	auto_ptr<int> ap(new int);
	auto_ptr<int> ap2(new int(3));
	*ap = 10;
	*ap = 100;		

	//auto_ptr<int> ap3 = ap;		//�ƶ���ֵ

	cout << *ap << endl;
}

//auto_ptr��ģ��ʵ��
template <class T>
class autoPtr
{
public:
	//RAII
	//���캯������ȡ��Դ�Ĺ���Ȩ
	autoPtr(T* ptr)
		:_ptr(ptr)
	{}

	//�����������ͷ���Դ
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

	//��������  �ƶ�����  ����Ȩת��
	autoPtr(autoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = nullptr;
	}

	//���� = �����  �ƶ���ֵ  ����Ȩת��
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

//unique_ptr��ʹ��
void test3()
{
	unique_ptr<A> up1(new A);
	//unique_ptr<A> up2(up1);		//error��unique_ptr�Ŀ������캯�����Ѿ�ɾ���ĺ���

	unique_ptr<A> up3(new A);
	//up1 = up3;					//error��unique_ptr�ĸ�ֵ��������Ѿ�ɾ���ĺ���
}

//unique_ptr��ʵ��
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

	//�������͸�ֵ
	UniquePtr(const UniquePtr<T>& up) = delete;
	UniquePtr<T>& operator=(const UniquePtr<T>& up) = delete;

private:
	T* _ptr;
};

//shared_ptr��ʹ��
void test4()
{
	//֧�ֿ����͸�ֵ
	shared_ptr<A> sp1(new A);
	cout << sp1.use_count() << endl;	//1

	shared_ptr<A> sp2(sp1);		//����		���ü���	�������������ͷż���
	cout << sp1.use_count() << endl;	//2
	cout << sp2.use_count() << endl;	//2

	shared_ptr<A> sp3(new A); 
	cout << sp1.use_count() << endl;	//2
	cout << sp2.use_count() << endl;	//2
	cout << sp3.use_count() << endl;	//1 

	sp3 = sp1;		//��ֵ�ɹ�
	cout << sp1.use_count() << endl;	//3
	cout << sp2.use_count() << endl;	//3
	cout << sp3.use_count() << endl;	//3 
	//use_count���ж��ٸ�����ָ����������Դ
}

//SharedPtr��ʵ��
template <class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		, _countPtr(new size_t(1))
	{}

	//��������
	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _countPtr(sp._countPtr)
	{
		//�������ۼ�
		++(*_countPtr);
	}

	//��ֵ����
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		//if (this != &sp)
		//�жϹ�����Ƿ�Ϊͬһ����Դ������һ����Դһ��һ��������һ����ԴҲ����һ����
		//��Դ��һ������һ����һ��������һ����Դ����һ��
		if(_ptr != sp._ptr)
		{
			//�������Լ�
			//���������Ϊ0��ʱ�򣬵�ǰ���������һ���������Դ�Ķ���
			if (--(*_countPtr) == 0)
			{
				//����ǰ�������Դ
				delete _ptr;
				delete _countPtr;
			}

			_ptr = sp._ptr;
			_countPtr = sp._countPtr;

			//�������ۼ�
			++(*_countPtr);
		}
		return *this;
	}

	~SharedPtr()
	{
		//�������Լ�
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

	//��ȡ���ü���
	size_t getCount()
	{
		return *_countPtr;
	}

//private:
	T* _ptr;
	size_t* _countPtr;	//������ָ��
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

//���̻߳������
void test6()
{
	SharedPtr<A> sp(new A);
	int n = 10000;		//����Խ����̳߳��ֵ�����Խ�ࣨ�����̣߳��߳��ǲ���ȫ��
	thread t1(fun6, ref(sp), n);		//ref��ʾ����
	thread t2(fun6, ref(sp), n);		//ref��ʾ����
	t1.join();
	t2.join();

	cout << sp.getCount() << endl;	
}


//SharedPtr��
//1.֧�ָ�ֵ�Ϳ���
//2.ͨ�����ü�����֤��Դ����ȷ��Ψһ���ͷ�
//3.���߳��У�ͨ�������ü������д��в�������֤����������ȷ
//4.ÿһ����Դ�����Լ����������ü���

//������̻߳�����⣬����
//SharedPtr��ʵ��
template <class T>
class SharedPtr1
{
public:
	SharedPtr1(T* ptr = nullptr)
		:_ptr(ptr)
		, _countPtr(new size_t(1))
		,_mtx(new mutex)
	{}

	//��������
	SharedPtr1(const SharedPtr1<T>& sp)
		:_ptr(sp._ptr)
		, _countPtr(sp._countPtr)
		,_mtx(sp._mtx)
	{
		//�������ۼ�
		//++(*_countPtr);
		addCount();
	}

	//��ֵ����
	SharedPtr1<T>& operator=(const SharedPtr1<T>& sp)
	{
		//if (this != &sp)
		//�жϹ�����Ƿ�Ϊͬһ����Դ������һ����Դһ��һ��������һ����ԴҲ����һ����
		//��Դ��һ������һ����һ��������һ����Դ����һ��
		if (_ptr != sp._ptr)
		{
			//�������Լ�
			//���������Ϊ0��ʱ�򣬵�ǰ���������һ���������Դ�Ķ���
			//if (--(*_countPtr) == 0)
			if(subCount() == 0)
			{
				//����ǰ�������Դ
				delete _ptr;
				delete _countPtr;

				//�ͷ���
				delete _mtx;
			}

			_ptr = sp._ptr;
			_countPtr = sp._countPtr;

			//�������ۼ�
			//++(*_countPtr);
			addCount();
		}
		return *this;
	}

	~SharedPtr1()
	{
		//�������Լ�
		//if (--(*_countPtr) == 0)
		if(subCount() == 0)
		{
			delete _ptr;
			delete _countPtr;

			//�ͷ���
			delete _mtx;

			_ptr = nullptr;
			_countPtr = nullptr;
			_mtx = nullptr;		//����Ϊ��
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

	//��ȡ���ü���
	size_t getCount()
	{
		return *_countPtr;
	}


	//��������
	size_t addCount()
	{
		_mtx->lock();
		++(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//��������
	size_t subCount()
	{
		_mtx->lock();
		--(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//private:
	T* _ptr;
	size_t* _countPtr;	//������ָ��

	//ÿһ����Դ��һ����������
	mutex* _mtx;
};



void fun7(const SharedPtr1<A>& sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		//�޸����ü������̰߳�ȫ�ģ����ݵĲ��������̰߳�ȫ�ģ���Ҫ�Լ���֤���ݵĲ����ǰ�ȫ�ģ�
		//��֤���ݵĲ����ǰ�ȫ�ģ�����������ʵ�ֵĶ�Ӧ�����м���
		SharedPtr1<A> copy(sp);

		copy->_a++;		//������һ�������Ĺ�ϵ
	}
}

//����֮��Ĳ��ԣ�������߳����ü��������⣬����˶��̰߳�ȫ�����⣨ʹ��������ɴ��в�����
void test7()
{
	SharedPtr1<A> sp1(new A);
	SharedPtr1<A> sp2(new A);
	int n = 10000;		

	//{t1,t2} �� {t3,t4} ���޸����ü���ʱ�ǲ��е�
	//t1 �� t2 ���޸����ü���ʱ�Ǵ��е�
	//t3 �� t4 ���޸����ü���ʱ�Ǵ��е�
	thread t1(fun7, ref(sp1), n);		//ref��ʾ����
	thread t2(fun7, ref(sp1), n);		//ref��ʾ����
	thread t3(fun7, ref(sp2), n);		//ref��ʾ����
	thread t4(fun7, ref(sp2), n);		//ref��ʾ����
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	cout << sp1.getCount() << endl;
	cout << sp2.getCount() << endl;

	cout << sp1->_a << endl;
	cout << sp2->_a << endl;
}

//ѭ������
struct ListNode
{
	//shared_ptr<ListNode> _next;
	//shared_ptr<ListNode> _prev;

	//���ѭ�����õķ�����ʹ����ָ��
	//weak_ptrֻ�����Զ���������ʹ��
	//weak_ptr���ܵ���ʹ��
	weak_ptr<ListNode> _next;	//��ֵ
	weak_ptr<ListNode> _prev;

	int _data;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

void test8()
{
	shared_ptr<ListNode> n1(new ListNode);		//ջ�ϵ�����ָ�����
	shared_ptr<ListNode> n2(new ListNode);

	cout << n1.use_count() << endl;
	cout << n2.use_count() << endl;

	n1->_next = n2;
	n2->_prev = n1;

	//cout << n1.use_count() << endl;
	//cout << n2.use_count() << endl;

	//weak_ptr���ܵ���ʹ��
	//weak_ptr<A> wp;
	//wp = n1;	//error
	shared_ptr<int> sp1(new int);
	weak_ptr<int> wp(sp1);
	cout << wp.use_count() << endl;

	shared_ptr<ListNode>* sp = new shared_ptr<ListNode>;	//���ϵ�����ָ�����
	delete sp;
}

//ɾ����
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

//�����Ŀռ�
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

	//��������
	SharedPtr2(const SharedPtr2<T>& sp)
		:_ptr(sp._ptr)
		, _countPtr(sp._countPtr)
		, _mtx(sp._mtx)
	{
		//�������ۼ�
		//++(*_countPtr);
		addCount();
	}

	//��ֵ����
	SharedPtr2<T>& operator=(const SharedPtr2<T>& sp)
	{
		//if (this != &sp)
		//�жϹ�����Ƿ�Ϊͬһ����Դ������һ����Դһ��һ��������һ����ԴҲ����һ����
		//��Դ��һ������һ����һ��������һ����Դ����һ��
		if (_ptr != sp._ptr)
		{
			//�������Լ�
			//���������Ϊ0��ʱ�򣬵�ǰ���������һ���������Դ�Ķ���
			//if (--(*_countPtr) == 0)
			if (subCount() == 0)
			{
				//����ǰ�������Դ
				//delete _ptr;
				_del(_ptr);	//ͨ��ɾ�����ͷſռ�
				delete _countPtr;

				//�ͷ���
				delete _mtx;
			}

			_ptr = sp._ptr;
			_countPtr = sp._countPtr;

			//�������ۼ�
			//++(*_countPtr);
			addCount();
		}
		return *this;
	}

	~SharedPtr2()
	{
		//�������Լ�
		//if (--(*_countPtr) == 0)
		if (subCount() == 0)
		{
			//delete _ptr;
			_del(_ptr);	//ͨ��ɾ�����ͷſռ�
			delete _countPtr;

			//�ͷ���
			delete _mtx;

			_ptr = nullptr;
			_countPtr = nullptr;
			_mtx = nullptr;		//����Ϊ��
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

	//��ȡ���ü���
	size_t getCount()
	{
		return *_countPtr;
	}

	//��������
	size_t addCount()
	{
		_mtx->lock();
		++(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//��������
	size_t subCount()
	{
		_mtx->lock();
		--(*_countPtr);
		_mtx->unlock();
		return *_countPtr;
	}

	//private:
	T* _ptr;
	size_t* _countPtr;	//������ָ��

	//ÿһ����Դ��һ����������
	mutex* _mtx;
	Del _del;	//ɾ����
};

//ɾ����
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