#include <iostream>

using namespace std;

/* 
//隐式实例化
template<typename T>
void my_swap(T& a, T& b)
{
	T temp = a;		//这里不能使用引用，使用引用之后改变temp的值就是改变a的值
	a = b;
	b = temp;
}

void test1()
{
	int a = 10;
	int b = 20;
	my_swap(a, b);
	cout << a << endl;	//20
	cout << b << endl;	//10
	double a1 = 1.2;
	double b1 = 2.3;
	my_swap(a1, b1);
	cout << a1 << endl;	//2.3
	cout << b1 << endl;	//1.2

	//my_swap(a, a1);	//error，报错：没有与参数列表匹配的函数模板"my_swap”实例参数类型为:(int, double)
	//上面语句不能通过编译，因为在编译期间，当编译器看到该实例化时，需要推演其实参类型，
	//通过实参a将T推演为int，通过实参a1将T推演为double类型，但模板参数列表中只有一个T，
	//编译器无法确定此处到底该将T确定为int 或者 double类型而报错
	//注意：在模板中，编译器一般不会进行类型转换操作
}
*/

/* 
//隐式实例化参数不一致问题解决
template<typename T>
T my_add(T a, T b)			//这里形参不能是引用
{
	return a + b;
}

void test2()
{
	int a = 10;
	int b = 20;
	double a1 = 1.2;
	double b1 = 2.3;
		
	//my_add(a, a1);	//error，报错：没有与参数列表匹配的函数模板"my_swap”实例参数类型为:(int, double)
	//解决方案：
	//1.用户自己来强制转化
	cout << my_add(a, (int)a1) << endl;		//11,double转int发生数据丢失
	//2.使用显示实例化
	cout << my_add<int>(a, a1) << endl;		//11
}
*/

/*
template<typename T>
T max(T a, T b)
{
	std::cout << "max(T, T) called." << std::endl;
	return (a > b) ? a : b;
}

template<typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype((a > b) ? a : b)
{
	std::cout << "max(T1, T2) called." << std::endl;
	return (a > b) ? a : b;
}

void test3()
{
	int i = 10;
	double d = 3.14;

	std::cout << "max(i, d) = " << max(i, d) << std::endl; // 自动类型转换，输出 10
	std::cout << "max(d, i) = " << max(d, i) << std::endl; // 自动类型转换，输出 10
}
*/

//类模板
//动态顺序表
//注意：Vector不是具体的类，是编译器根据被实例化的类型生成具体类的模具
template<class T>
class Vector
{
public:
	Vector(size_t capacity = 10)
		: _pData(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}
	// 使用析构函数演示：在类中声明，在类外定义。
	~Vector();
	void PushBack(const T& data)；
		void PopBack()；
		// ...
		size_t Size() { return _size; }
	T& operator[](size_t pos)
	{
		assert(pos < _size);
		return _pData[pos];
	}
private:
	T* _pData;
	size_t _size;
	size_t _capacity;
};
// 注意：类模板中函数放在类外进行定义时，需要加模板参数列表
template <class T>
Vector<T>::~Vector()
{
	if (_pData)
		delete[] _pData;
	_size = _capacity = 0;
}

void test4()
{
	// Vector类名，Vector<int>才是类型
	Vector<int> s1(10);
	Vector<double> s2;
}

int main()
{
	//test1();		//隐式实例化
	//test2();		//隐式实例化参数不一致问题解决
	//test3();
	test4();
	return 0;
}