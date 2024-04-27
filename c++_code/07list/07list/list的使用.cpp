#include <iostream>
#include <list>
#include <vector>

using namespace std;

//���캯��
void test1()
{
	//�޲ι���
	list<int> l1;

	//n��val
	list<int> l2(3, 5);		//����Ԫ��ֵΪ5������

	//���乹�죨����������ָ�룩
	string str = "123456";
	list<char> l3(str.begin(), str.end());
	char arr[] = "abcdef";
	list<char> l4(arr, arr + sizeof(arr) / sizeof(arr[0]));

	//��������
	list<char> l5(l4);
}

//list iterator(������) 
void test2()
{
	string s("123456");
	list<char> l(s.begin(), s.end());
	list<char>::iterator it = l.begin();
	while (it != l.end())
	{
		cout << *it << " ";		//1 2 3 4 5 6
		++it;
	}
	cout << endl;

	list<char>::const_reverse_iterator crit = l.crbegin();
	while (crit != l.crend())
	{
		cout << *crit << " ";	//6 5 4 3 2 1
		++crit;
	}
	cout << endl;

	it = l.begin();
	it++;
	cout << *it << endl;	//2
	--it;
	cout << *it << endl;	//1
	//it = it + 1;	//error����֧�֣�ֻ��������ʵ�����֧��
	//vector������֧�֣�����ֱ���������Ԫ��
	//��������Ϊ3�࣬�ֱ���ǰ���������˫���������������ʵ�����
	//������ʵ������ṩ��һϵ�й��ܣ����ܹ����е������Ӽ����㡢�±�������������ʵȣ�
	//ʹ�������ܹ�����ز��������е�Ԫ�ء���Щ�������Ը���ʵ������ѡ���Ա����Ч�ش洢�Ͳ������ݡ�

	//֧��������ʵĵ�����
	//std::array���̶���С������������
	//std::vector����̬����������
	//std::deque��˫�˶���������
	//std::string���ַ���������
	//std::valarray��ֵ����������������ֵ���㡣
	//std::map �� std::multimap�������������ṩ��ֵ�Ե�ӳ�䡣
	//std::set �� std::multiset�������������洢���ظ���Ԫ�أ�����һ��˳������
	//std::unordered_map �� std::unordered_multimap����������������ṩ��ֵ�Ե�ӳ�䡣
	//std::unordered_set �� std::unordered_multiset����������������洢���ظ���Ԫ�أ��������С�
}

//��Χfor���ײ���ͨ��������ʵ�ֵ�
void test3()
{
	string s("123456");
	list<char> l(s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//1 2 3 4 5 6
	cout << endl;

	for (auto& ch : l)		//&��ԭ���������Ͳ�Ӱ��Ч�ʣ��Զ�������&��ֵ��Ч�ʸߣ�&���ÿ�����
	{
		ch = 'a';
		cout << ch << " ";		//a a a a a a
	}
	cout << endl;
}

//empty	size max_size		list�в�����capacity�ӿڣ���Ϊlist�ײ���˫���ͷѭ������
void test4()
{
	list<int> l;
	cout << l.size() << endl;	//0
	l.push_back(10);
	if (l.empty())
		cout << "listΪ��" << endl;	
	else
		cout << l.size() << endl;	//1
	
	cout << l.max_size() << endl;	//357913941
}

//front back
void test5()
{
	list<int> l;
	l.push_back(10);
	l.push_front(20);
	cout << l.front() << endl;	//20
	cout << l.back() << endl;	//10
}

//assign����ֵ����=������߼�һ����
void test6()
{
	string s("123456");
	list<char> l(s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//1 2 3 4 5 6
	cout << endl;

	//n��val��ֵ
	l.assign(3, '5');
	for (const auto& ch : l)
		cout << ch << " ";		//5 5 5
	cout << endl;

	//���丳ֵ
	l.assign(s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//1 2 3 4 5 6
	cout << endl;

	char arr[] = { 51,52,53,54,55,56 };
	l.assign(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (const auto& ch : l)
		cout << ch << " ";		//3 4 5 6 7 8
	cout << endl;

	//=�����
	list<char> l2;
	l2 = l;
	for (list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
		cout << *it << " ";		//3 4 5 6 7 8
	cout << endl;
}

//emplace_front emplace_back push_back push_front pop_front pop_back emplace insert erase clear
void test7()
{
	//����emplace��ʾ����ֱ�ӹ��죬�ȹ����ٲ���
	list<int> l;
	l.push_front(1);
	l.push_back(2);
	l.insert(l.begin(), 3);
	l.insert(l.end(), 4);

	for (const auto& ch : l)
		cout << ch << " ";		//3 1 2 4
	cout << endl;

	l.insert(++l.begin(), 3, 5);			//��begin����������һ��λ�ò���3��5
	//ǰ��++����begin����������һ��λ�ò��룬����++����begin��������λ�ò���
	for (const auto& ch : l)
		cout << ch << " ";		//3 5 5 5 1 2 4
	cout << endl;

	//�������
	string s = "123456";
	l.insert(--l.end(), s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//3 5 5 5 1 2 49 50 51 52 53 54 4
	cout << endl;
	l.pop_front();
	l.pop_back();

	//emplace
	l.emplace_back();		//��������Ĭ���ǲ���0����Ϊ��������Ĭ��ֵ����0ֵ
	l.emplace_front(15);
	for (const auto& ch : l)
		cout << ch << " ";		//15 5 5 5 1 2 49 50 51 52 53 54 0
	cout << endl;

	l.emplace(l.begin(), 10);	//begin������λ�ò���10
	//l.emplace(l.begin(), 3, 7);	//error������ʵ�֣�begin������λ�ò���3��7
	for (const auto& ch : l)
		cout << ch << " ";		//10 15 5 5 5 1 2 49 50 51 52 53 54 0
	cout << endl;

	//erase����ֵ������������ɾ��Ԫ�ص���һ��Ԫ�ص�λ��
	//ɾ������ֵ
	list<int>::iterator it = l.erase(l.begin());
	l.erase(it);
	for (const auto& ch : l)
		cout << ch << " ";		//5 5 5 1 2 49 50 51 52 53 54 0
	cout << endl;

	//ɾ��һ�����������ֵ
	l.erase(++l.begin(), --l.end());		//����ҿ���ɾ����һ��������λ�ã���ɾ���ڶ���������λ��
	for (const auto& ch : l)
		cout << ch << " ";		//5 0
	cout << endl;

	//������ʧЧ���⣺
	//1.����Ԫ�ز�����ɵ�����ʧЧ����Ϊlist�������ݣ�����ڵ��ʹ������ڵ�Ŀռ䡣
	//2.ɾ��Ԫ�ػ���ɵ�����ʧЧ����Ϊɾ���ڵ��ʹ����ڵ�����ݶ�ʧ��������ָ��������ǲ����ڵġ�

	//list�лᵼ�µ�����ʧЧ�Ľӿڣ�erase��pop_back��pop_front
	l.clear();	//���list
	if (l.empty())
		cout << "listΪ��" << endl;		//listΪ��
	else
		cout << "list��Ϊ��" << endl;
}

//swap resize
void test8()
{
	list<int> l1(5, 6);
	list<int> l2(1, 1);

	l1.swap(l2);		//�޷���ֵ

	for (const auto& ch : l1)
		cout << ch << " ";		//1
	cout << endl;

	for (const auto& ch : l2)
		cout << ch << " ";		//6 6 6 6 6
	cout << endl;

	l2.resize(3,4);
	for (const auto& ch : l2)
		cout << ch << " ";		//6 6 6 
	cout << endl;

	l1.resize(4);
	for (const auto& ch : l1)
		cout << ch << " ";		//1 0 0 0
	cout << endl;
	//resize���ٽڵ������size�ͱ�С��resize���ӽڵ������size�ͱ���ø���ֵ��䣬Ĭ������0ֵ
}

//splice��ƴ��		�޷���ֵ
void test9()
{
	//��ƴ�ӵ�list��û��������
	std::list<int> l1, l2;
	std::list<int>::iterator it;

	for (int i = 1; i <= 4; ++i)
		l1.push_back(i);      //1 2 3 4

	for (int i = 1; i <= 3; ++i)
		l2.push_back(i * 10);   //10 20 30

	//1.ƴ��ȫ��
	l1.splice(l1.begin(), l2);  
	for (const auto& ch : l1)
		cout << ch << " ";	//10 20 30 1 2 3 4
	cout << endl;

	if (l2.empty())
		cout << "l2Ϊ��" << endl;	//l2Ϊ��

	l2 = l1;
	for (const auto& ch : l2)
		cout << ch << " ";	//10 20 30 1 2 3 4
	cout << endl;

	//2.ƴ��һ��
	l1.splice(l1.end(), l2, --l2.end());	//����1��ƴ�ӵ���λ�ã�����2����ƴ�ӵ�list������3����ƴ�ӵ�λ�ã�ֻ�е�ǰλ�ã�

	for (const auto& ch : l1)
		cout << ch << " ";	//10 20 30 1 2 3 4 4
	cout << endl;

	for (const auto& ch : l2)
		cout << ch << " ";	//10 20 30 1 2 3 
	cout << endl;

	//3.ƴ��һ������
	l1.splice(l1.end(), l2, l2.begin(), --l2.end());
	for (const auto& ch : l1)
		cout << ch << " ";	//10 20 30 1 2 3 4 4 10 20 30 1 2 
	cout << endl;

	for (const auto& ch : l2)
		cout << ch << " ";	//3
	cout << endl;
}

//remove
void test10()
{
	string s = "fabcdef";
	list<char> l(s.begin(), s.end());
	l.remove('f');	//ɾ������l�е������ַ�'f'���������l�в�����'f'���ͺ����������
	for (const auto& ch : l)
		cout << ch << " ";		//abcde
	cout << endl;

	//�º���	����ָ��
	//l.remove_if();			//֮��
}

//�º��� ����ָ��
//����
bool single_digit(const int& value) 
{
	return (value < 5); 
}

//��
struct is_odd
{
	bool operator() (const int& value) 
	{
		return (value % 2) == 1;
	}
};

//remove_if		ɾ��ָ�����������
void test11()
{
	list<int> l;
	for (int i = 0; i < 10; ++i)
		l.push_back(i);

	l.remove_if(single_digit);		//ɾ��С��5������
	
	for (const auto& ch : l)
		cout << ch << " ";			//5 6 7 8 9 
	cout << endl;

	l.remove_if(is_odd());			//ɾ������������

	for (const auto& ch : l)
		cout << ch << " ";			//6 8
}

//unique�������ظ�Ԫ��ȥ��	�����		������������ȥ��
void test12()
{
	string s = "baaabbcddeffghh";
	list<char> l(s.begin(), s.end());

	for (const auto& ch : l)
		cout << ch << " ";	//a a a b b c d d e f f g h h
	cout << endl;

	l.unique();

	for (const auto& ch : l)
		cout << ch << " ";	//a b c d e f g h
	cout << endl;

	double arr[] = { 1.2,3.5,4.2,7.2,8.3,10.2,12.5,16 };
	list<double> l1(arr, arr + sizeof(arr) / sizeof(arr[0]));
}

//�ɴ�С����
bool compareList(const int& a, const int& b)
{
	return a > b;
}

//sort	Ĭ���ǰ�����С��������	�º���ʵ���ɴ�С����
void test13()
{
	string s = "bfdghace";
	list<char> l(s.begin(), s.end());

	for (const auto& ch : l)
		cout << ch << " ";	//b f d g h a c e
	cout << endl;

	l.sort();

	for (const auto& ch : l)
		cout << ch << " ";	//a b c d e f g h
	cout << endl;

	l.sort(compareList);

	for (const auto& ch : l)
		cout << ch << " ";	//h g f e d c b a
	cout << endl;
}

//�º����������ж�����Ԫ���Ƿ����
struct MyComparator
{
	bool operator()(const int& a, const int& b) const
	{
		return a % 3 == b % 3;  // ����Ԫ�ض� 3 ȡģ�Ľ���ж��Ƿ����
	}
};

//unique�º���	���Ƽ�ʹ��
void test14()
{
	std::list<int> l = { 1, 2, 4, 7, 8, 10, 11, 13, 14, 16 };

	// ʹ�� unique ȥ�������ظ�Ԫ�أ������Զ���ķº���
	l.unique(MyComparator());

	// ���ȥ�غ�Ľ��
	for (const auto& num : l) 
	{
		std::cout << num << " ";		//1 2 4 8 10 11 13 14 16
	}
	std::cout << std::endl;
}

//merge	�ϲ������list	����������������޷�Ԥ֪���߱���
void test15()
{
	list<int> l1 = { 1,3,5,7,9,11 };
	list<int> l2 = { 2,4,6,8,10,12 };
	
	l1.merge(l2);
	
	for (const auto& ch : l1)
		cout << ch << " ";		//1 2 3 4 5 6 7 8 9 10 11 12
	cout << endl;

	if (l2.empty())
		cout << "l2Ϊ��" << endl;	//l2Ϊ��
}

//reverse����תlist  �����ṩ�ӿھ����������ṩ�ģ�Ч�ʸߣ�û�о�ʹ��algorithm�ṩ�Ľӿ�
void test16()
{
	list<int> l = { 1,2,3,4,5,8,7,6 };
	l.reverse();
	for (const auto& ch : l)
		cout << ch << " ";	//6 7 8 5 4 3 2 1
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
	//test13();
	//test14();
	//test15();
	test16();
	return 0;
}