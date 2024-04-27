//#pragma warning(disable:4996)		//����4996�������
#define _CRT_SECURE_NO_WARNINGS		
//����ȡ�� Visual Studio ��������MSVC����ʹ��ĳЩ��׼ C/C++ ����ʱ�����İ�ȫ������Ϣ
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>

using namespace std;

char* Mystrcpy(char* dest, const char* src)
{
	assert(dest && src);   //����
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
	//������
	typedef T* iterator;
	typedef const T* const_iterator;

	//Ĭ�Ϲ��캯��
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}

	//���죺n��val
	//Vector(size_t n,T& val = T())//����������г��ԣ�û��const�ᱨ������Ϊ��Ĭ�ϲ����޷���intת��ΪT&
	Vector(size_t n, const T& val = T())   //����������г���
		:_start(new T[n])		//�����ܹ����n��Ԫ�صĿռ�
		, _finish(_start + n)
		, _endOfStorage(_start + n)		//_finish
	{
		for (size_t i = 0; i < n; ++i)
		{
			_start[i] = val;
		}
	}

	//��������
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
	//���ʹ��iterator�����������ᵼ�³�ʼ���ĵ���������[first,last)ֻ����vector�ĵ�����
	//��������������������������[first,last]���������������ĵ�����
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

	//��������
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
	}

	/*
	//��ֵ�����
	//��ͳд��
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

	//��ֵ������ִ�д��
	void Swap(Vector<T>& v)			//���ã��ڲ��޸��൱���ⲿ�޸�
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endOfStorage, v._endOfStorage);
	}

	Vector<T>& operator=(Vector<T> v)	//ֵ����
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
			//����ԭʼ��size
			size_t sz = size();
			//���ռ�
			T* arr = new T[n];
			//��������
			if (_start)
			{
				/*
				//�Զ������ͣ�ǳ����  �������Դ���������Դ������ͷ�
				//memcpy(arr, _start, sizeof(T)*size());
				for (size_t i = 0; i < sz; i++)
					arr[i] = _start[i];
				delete[] _start;
				*/
				//���
				for (size_t i = 0; i < sz; i++)
				{
					//������Զ������ͣ����ø�ֵ��������غ���
					//ֻҪ��ֵ�����ʵ����������˴���Ϊ���
					arr[i] = _start[i];
				}
				delete[] _start;
			}
			//����
			_start = arr;
			_finish = _start + sz;		//�ռ���ˣ�����_finish�ͱ���
			_endOfStorage = _start + n;
		}
	}
//1.memcpy���ڴ�Ķ����Ƹ�ʽ��������һ���ڴ�ռ�������ԭ�ⲻ���Ŀ���������һ���ڴ�ռ���
//2.������������������͵�Ԫ�أ�memcpy����Ч�ֲ��������������������Զ�������Ԫ�أ�
//�����Զ�������Ԫ�����漰����Դ����ʱ���ͻ������Ϊmemcpy�Ŀ���ʵ����ǳ������
//���ۣ�����������漰����Դ����ʱ��ǧ����ʹ��memcpy���ж���֮��Ŀ�����
//��Ϊmemcpy��ǳ������������ܻ������ڴ�й©�������������

	void resize(size_t n, const T& val = T())
	{
		//n > capacity ����
		if (n > capacity())
		{
			reserve(n);
		}
		//szie < n < capacity [size,n - 1] ������Ĳ������val
		if (n > size())
		{
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}
		//n <= size��ֻ�޸�size
		_finish = _start + n;
	}

	void insert(iterator pos, const T& val)
	{
		//��Ч����:[0,size]
		if (pos >= _start && pos <= _finish)
		{
			//�������
			if (_finish == _endOfStorage)
			{
				//����Ԫ�صĸ���
				size_t num = pos - _start;
				//���ݻᵼ�µ�����ʧЧ������Ҫ���µ�����
				size_t n = _endOfStorage == nullptr ? 1 : 2 * capacity();
				reserve(n);
				//����֮�����pos
				pos = _start + num;    //����֮��_start,_finish,_endOfStorage���Զ������ˣ���posû�иı䣬�������_star��pos�����λ�ù�ϵ
			}
			//�ƶ�Ԫ��:�Ӻ���ǰ�ƶ�
			iterator end = _finish;
			while (end != pos)
			{
				*end = *(end - 1);
				end--;
			}
			//�����µ�Ԫ��
			*pos = val;
			//����
			++_finish;
		}
	}

	//ɾ��
	iterator erase(iterator pos)
	{
		//���λ��
		if (pos < _finish && pos >= _start)
		{
			//�ƶ�Ԫ��:��ǰ����ƶ�
			iterator start = pos + 1;
			while (start != _finish)
			{
				*(start - 1) = *start;
				start++;
			}
			//����
			_finish--;
		}
		return pos;   //����ɾ�������һ��λ��
	}

	//β��
	void push_back(const T& val)
	{
		//�������
		if (_finish == _endOfStorage)
		{
			//����
			size_t newC = _endOfStorage == nullptr ? 1 : 2 * capacity();
			reserve(newC);   //Ԥ���ռ� 
		}

		//����
		*_finish = val;
		//����size
		_finish++;
	}

	void pop_back()
	{
		erase(end() - 1);
	}

private:
	iterator _start;		//ָ�����ݿ�Ŀ�ʼ
	iterator _finish;		//ָ����Ч���ݵ�β
	iterator _endOfStorage;	//ָ��洢������β
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
	A(int a = 1)		//�������޲ι���
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
	for (const auto& e : v)    //�����constҪ�Լ��ӣ����ӵĻ��Ƶ�������Ϊint��vector�е����ݾͿ����޸��ˡ�
	{
		cout << e << " ";
		//cout << typeid(e).name() << " ";
		//e = T();   
	}
	cout << endl;
}

//c++�е�vector��û���ṩ<<�����
template <class T>
ostream& operator<<(ostream out, Vector<T>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		out << v[i] << " ";			//����T��<<�����Ҳ��������
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