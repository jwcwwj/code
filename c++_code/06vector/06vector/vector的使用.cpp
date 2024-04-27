#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//���캯��
struct A
{
	A(int a = 1,int b = 2)
		:_a(a)
		,_b(b)
	{}
	int _a = 1;
	int _b = 2;
};

ostream& operator<<(ostream& out, const A& aa)
{
	out << " _a = " << aa._a << "  _b = " << aa._b << endl;
	return out;
}

void test1()
{
	//1.��vector
	vector<int> v1;
	vector<char> v2;

	//2.vector(n,value);		n��vector�����е�Ԫ�ظ���	value��ֵ
	//�������ͣ�ȱʡ��ֵΪ��0ֵ
	//int:0	float/double:0.0	char:'\0'	ָ��:nullptr
	vector<int> v3(5);			//���������Ǵ����ĸ���	5��0
	vector<int*> v4(5);
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
		cout << *it << " ";		//��������0 0 0 0 0
	cout << endl;

	//�Զ������ͣ�ȱʡֵΪĬ�Ϲ��촴���Ķ���
	vector<A> v5(8);
	//vector<�Զ�������> ������(num,���캯��(����))
	vector<A> v6(5, A(5, 10));

	//3.���乹��
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v7(arr, arr + sizeof(arr)/sizeof(arr[0]));
	//vector<int> v8(arr.begin(), arr.end());		//error������ԭ�򣺱��ʽ�������������
	string str = "123456";
	vector<char> v9(str.begin(), str.end());

	//��������
	vector<A> v10(v5);
	for (vector<A>::iterator it = v10.begin(); it != v10.end(); ++it)
		cout << *it << " ";		
	//��������
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
}

//vector������
void test2()
{
	string str("12345678");
	vector<char> v(str.begin(), str.end());

	//���������
	vector<char>::iterator it = v.begin();
	int idx = 0;
	while (it != v.end())
	{
		cout << *it << " ";		//��������1 2 3 4 5 6 7 8
		*it = 'a' + idx;
		++idx;
		++it;
	}
	cout << endl;

	//���������
	for (vector<char>::const_reverse_iterator crit = v.crbegin(); crit != v.crend(); ++crit)
		cout << *crit << " ";		//h g f e d c b a
	cout << endl;

	vector<char>::const_reverse_iterator crit = v.rbegin();
	while (crit != v.rend())
	{
		cout << *crit << " ";		//h g f e d c b a
		++crit;
	}
	cout << endl;
}

//��Χforѭ��
void test3()
{
	string s("123456");
	vector<char> v(s.begin(), s.end());
	for (const auto& ch : v)
		cout << ch << " ";	//��������1 2 3 4 5 6
	cout << endl;
}

struct B
{
	int a;
	char b;
	double c;
	char* d;
};

//max_size()����ʾ��ǰvector�����ܹ����ɵ����Ԫ������
//max_size ���ص��������Ͽ����ɵ����Ԫ��������ʵ���Ͽ������ڸ������ƶ��޷��ﵽ�����ֵ��
void test4()
{
	vector<char> v1;
	vector<int> v2;
	vector<int*> v3;
	vector<double> v4;
	vector<B> v5;
	cout << v1.max_size() << endl;	//2147483647	��
	//2147483647 ��һ������������ int ���͵����ֵ�����ʹ��32λ�з���������ʾ����
	cout << v2.max_size() << endl;	//1073741823
	cout << v3.max_size() << endl;	//1073741823
	cout << v4.max_size() << endl;	//536870911
	cout << v5.max_size() << endl;	//178956970
}

//capacity	size	resize	reserve  empty	shrink_to_fit
void test5()
{
	string s;
	vector<char> v(s.begin(),s.end());
	//string��ЧԪ�ظ���������
	cout << s.capacity() << endl;		//15
	cout << s.size() << endl;			//0
	//vector��ЧԪ�ظ���������
	cout << v.capacity() << endl;		//0
	cout << v.size() << endl;			//0
	
	//������ЧԪ�صĸ������ı�size��������ӵ���ЧԪ�صĸ������������ͻ�ı�capacity�����򲻸ı�
	v.resize(10);
	cout << v.capacity() << endl;		//10
	cout << v.size() << endl;			//10
	
	//��С����ЧԪ�صĸ������ı�size�����ı�capacity
	v.resize(8);
	cout << v.capacity() << endl;		//10
	cout << v.size() << endl;			//8
	
	//��С��������С�����ı�size��capacity
	v.reserve(5);
	cout << v.capacity() << endl;		//10
	cout << v.size() << endl;			//8
	
	//���ӵ�������С���ı�capacity�����ı�size
	v.reserve(15);
	cout << v.capacity() << endl;		//15
	cout << v.size() << endl;			//8
	
	//�ܽ᣺resize����С��ЧԪ������ʱ���ı�size�����ı�capacity��
	//�ܽ᣺resize��������ЧԪ������ʱ���ı�size�����ܻ�ı�capacity��
	//�ܽ᣺reserve����С����ʱ�����ı�size��Ҳ���ı�capacity��
	//�ܽ᣺reserve����������ʱ�����ı�size��ֻ�ı�capacity��
	
	v.shrink_to_fit();	//���� vector �����������СΪ�䵱ǰԪ������
	cout << v.capacity() << endl;		//8
	cout << v.size() << endl;			//8	
	//shrink_to_fit��capacity��������sizeһ��
	//ֻ�е������Ĵ�С��������ʱ���Ż����������ڴ���ͷź����·��䡣
	//��ˣ���ʵ��ʹ���У�shrink_to_fit �����ܱ�֤һ���������������ڴ�ʹ�á�
	
	if (v.empty())
		cout << "empty�����ǿյ�" << endl;		 
	else
		cout << "empty�������ǿյ�" << endl;	//empty�������ǿյ�	
}

//[] at	front back 
//data����ȡvector�����Ĵ��Ԫ�ؿռ���׵�ַ
void test6()
{
	string str = "123456";
	vector<char> v(str.begin(), str.end());
	for (size_t i = 0; i < v.size(); ++i)
	{
		//cout << v.operator[](i) << " ";
		cout << v[i] << " ";	//1 2 3 4 5 6
	}
	cout << endl;
	
	//at��[]������
	cout << v.front() << endl;		//1
	cout << v.back() << endl;		//6

	char* ptr = v.data();		//��ȡvector�����Ĵ��Ԫ�ؿռ���׵�ַ
	ptr[0] = '8';
	for (int i = 0; i < v.size(); i++)
		cout << ptr[i] << " ";		//8 2 3 4 5 6
	cout << endl;
}

//��ֵ assign���滻�����ԭ�������е�Ԫ�أ����µ�Ԫ����ӽ�ȥ�� 
void test7()
{
	vector<int> v = { 1,2,3,4,5,6,7,8 };
	for (const auto& ch : v)
		cout << ch << " ";		//1 2 3 4 5
	cout << endl;
	cout << v.size() << endl;		//8
	cout << v.capacity() << endl;	//8

	vector<int> v1 = { 12,23,45,56 };	 
	v.assign(v1.begin(),v1.end());
	for (const auto& ch : v)
		cout << ch << " ";		//12 23 45 56
	cout << endl;
	cout << v.size() << endl;		//4
	cout << v.capacity() << endl;	//8

	v.assign(10,'a');
	for (const auto& ch : v)
		cout << ch << " ";		//97 97 97 97 97 97 97 97 97 97 
	cout << endl;
	cout << v.size() << endl;		//10
	cout << v.capacity() << endl;	//12
}

//push_back	pop_back insert erase
void test8()
{
	string s = "123456";
	string s1("789");
	vector<char> v(s.begin(), s.end());
	v.push_back('7');
	v.pop_back();
	v.insert(v.begin(), '0');		//ͷ��
	v.insert(--v.end(), 5, 'a');	//���һ��Ԫ�ص�ǰ���5���ַ�a
	v.insert(++v.begin(), s1.begin(), s1.end());	//�ڵ�һ��Ԫ�صĺ������s1��ȫ������
	for (const auto& ch : v)
		cout << ch << " ";		//0 7 8 9 1 2 3 4 5 a a a a a 6
	cout << endl;
	v.erase(v.begin());		//ͷɾ
	v.erase(++v.begin(), --v.end());		//ɾ���ڶ���Ԫ�ص������ڶ���Ԫ�������ȫ��Ԫ�أ���������ҿ���
	for (const auto& ch : v)
		cout << ch << " ";		//7 6
	cout << endl;
}

struct C
{
	explicit C(int c,int b)
		:_c(c)
		,_b(b)
	{}

private:
	int _c;
	int _b;
};

//emplace emplace_back
void test9()
{
	vector<C> v;
	C c1(1,2);
	v.push_back(c1);
	//v.push_back(2,2);			//�������ι��죬Ҳ��������û�д����Ķ���
	v.emplace_back(2,2);		//֧�ֵģ��ò������ù��캯������һ�����󣬰����������뵽vectorĩβ
	//emplaceֻ��Ҫ���ݹ��캯����Ҫ�Ĳ������ӿ��ڲ�ֱ�Ӵ�������	
	//�Զ�������emplace_back��push_back�����ƣ�emplace��insert������
	v.emplace_back(c1);
	v.insert(v.begin(), C(2, 3));
	//v.insert(v.begin(), 2, 3);	//error
	v.emplace(v.begin(), 5, 6);		//��ͷ������(5,6)

	//�ܽ᣺
	//push_back��insert����ı������Ѿ������Ķ���
	//emplace��emplace_back���Բ�����������û�д����Ķ�����Գ��룻
	//emplace��emplace_back�ڲ����ʱ������󣬹�����󲢲���
	//push_back��insert���ṹ�����

	//emplace����һ��ָ���Ѳ���Ԫ�صĵ�������emplace_back������ֵ��
}

//���ݵĹ���
void test10()
{
	vector<int> v;
	size_t c = v.capacity();	 
	cout << c << endl;		//0
	for (size_t i = 0; i < 200; ++i)
	{
		v.push_back(i);
		if (c != v.capacity())
		{
			c = v.capacity();
			cout << c << endl;
		}
	}
	//�����
	//1
	//2
	//3
	//4
	//6
	//9
	//13
	//19
	//28
	//42
	//63
	//94
	//141
	//211
	//��va2017����1.5�������ݣ���Linux����2��������
}

//������ʧЧ����
void test11()
{
	vector<int> v(3, 10);		//3��Ԫ�أ�ֵΪ10
	vector<int>::iterator it = v.begin();
	
	cout << *it << endl;	//10
	v.push_back(4);
	//cout << *it << endl;//error,����ԭ����β���ʱ�������ˣ�ԭ�ȵĿռ��ͷ��ˣ�������ָ��ԭ���Ŀռ䲻�ܷ�����
	//�����ʩ��ÿ������֮�����»�ȡ�����ĵ�����
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";		//10 10 10 4
		++it;
	}
	cout << endl;

	//erase
	it = v.begin();
	cout << *it << endl;	//10
	v.erase(it);
	//cout << *it << endl;	//eror������ԭ�򣺵�������λ�����������Ƚ��ϸ񣨵�����ָ���λ�÷����˱仯��
	//������ʧЧ��Ϊ�˱���ɾ���������һ��Ԫ�أ���һ��Ԫ�ز��ɷ���

	//�ᵼ�µ���������ʧЧ�Ľӿڣ�
	//���ݣ�resize��reserve��push_back��insert��emplace��emplace_back
	//ɾ��������erase��pop_back��clear�����vector�����е�����Ԫ�أ�
}

//ɾ�����е�ż��
void test12()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			//std::vector �� erase ��Ա�����᷵��һ��ָ��ɾ��Ԫ��֮���Ԫ�صĵ�������
			//�������ɾ���������һ��Ԫ�أ��򷵻� end() ��������
			it = v.erase(it);
			//it = v.begin();	//��linux�²����»�ȡ�������ǿ���ͨ���ģ�windows�²��У�Ϊ�˰�ȫ�������»�ȡ������
			//��linxu�����һ��Ԫ��Ҫ��ż�����ᱨ���δ��󣬷Ƿ����ʡ�����д����else��ʱ��
		}
		else
			++it;
	}
	for (const auto& ch : v)
		cout << ch << " ";		//1 3 5
	cout << endl;
}

//vector�����е�swap��vectorû���ṩfind�ӿڣ�algorithm�ṩ��find�ӿ�
void test13()
{
	vector<int> v1 = { 1,2,3,4,5 };
	//��v1�в���Ԫ��2
	for (const auto&ch : v1)	
		cout << ch << " ";		//1 2 3 4 5
	cout << endl;
	
	vector<int>::iterator pos = find(v1.begin(),v1.end(),2);	//����2λ�õĵ�����
	cout << *pos << endl;	//2
	v1.erase(pos);
	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";		//1 3 4 5
		++it;
	}
	cout << endl;

	vector<int> v2(8, 10);
	cout << v1.size() << endl;		//4
	cout << v1.capacity() << endl;	//5
	cout << v2.size() << endl;		//8
	cout << v2.capacity() << endl;	//8
	for (const auto&ch : v2)
		cout << ch << " ";		//10 10 10 10 10 10 10 10 
	cout << endl;

	v1.swap(v2);
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
		cout << *it << " ";		//10 10 10 10 10 10 10 10 
	cout << endl;
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
		cout << *it << " ";		//1 3 4 5
	cout << endl;
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
	//test9();
	//test10();
	//test11();
	//test12();
	test13();
	return 0;
}