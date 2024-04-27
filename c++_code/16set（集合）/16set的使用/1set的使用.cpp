#include <iostream>
#include <string>
#include <set>

using namespace std;

//���캯��
void test1()
{
	//1.�޲ι���
	set<int> s1;

	//���乹��
	int arr[] = { 5,3,1,4,4 };
	set<int> s2(arr, arr + sizeof(arr) / sizeof(arr[0]));	//4���ظ��ģ�ֻ��洢һ��4

	for (const auto ch : s2)
		cout << ch << " ";		//1 3 4 5 ����������������Ȼ����ģ�set�������ǰ����������
	cout << endl;

	for (set<int>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";		//1 3 4 5	 
		//*it = 10;	//set��������֧���޸ģ�ԭ��set�ĵײ��Ƕ������������޸��˻��ƻ������������Ľṹ
	}
	cout << endl;

	cout << "reverse iterator:";
	set<int>::reverse_iterator rit = s2.rbegin();
	while(rit != s2.rend())
	{
		cout << *rit << " ";	//5 4 3 1
		++rit;
	}
	cout << endl;

	//��������
	set<int> s3(s2);
	for (auto ch : s3)
		cout << ch << " ";	//1 3 4 5
	cout << endl;
}

//��������	size	max_size	empty 
void test2()
{
	int arr[] = { 5,3,1,4,4 };
	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));	//4���ظ��ģ�ֻ��洢һ��4

	if (!s.empty())
		cout << s.size() << endl;		//4
	else
		cout << "s����Ϊ��" << endl;

	cout << "int���͵ļ������洢����" << s.max_size() << endl;	//int���͵ļ������洢����214748364
}

template <class T>
void printSet(const set<T>& s)
{
	for (auto& e : s)
		cout << e << " ";
	cout << endl;
}

//����
void test3()
{
	//���룺
	//1.����ԭ��pair<iterator, bool> insert(const value_type& x)	��õ�
	//����ֵ��pair<iterator, bool>	iterator�ǲ���ĵ�������λ�ã�bool�ǲ���ɹ���true������ʧ�ܣ�false��
	//set�в������ظ������ݣ�set��û��Ҫ���������Ѱ�Һ��ʵ�λ�ý��в��룬����true��
	//set����Ҫ��������ݣ�����ʧ�ܣ�����false��
	//����ʧ��Ҳ�᷵�ص�������λ�ã����ǺͲ���ʧ�ܵ����ݣ�ֵ����ȵ�Ԫ��λ��
	//����ɹ��˾��Ƿ��ز�����µ����ݵ�λ��
	int arr[] = { 5,3,1,4,10 };
	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));	
	
	auto ret = s.insert(10);	//��д��auto�����ƶ�
	cout << ret.second << endl;	//0(false)	��ʾ����ʧ��

	pair<set<int>::iterator, bool> ret1 = s.insert(10);
	//�����ò���ĵ�����λ�þ��ǲ��������
	cout << *ret1.first << endl;		//10	����ʧ�ܾ���֮ǰ�Ѿ����ڵ�����

	ret1 = s.insert(20);
	cout << *ret1.first << endl;		//20	����ɹ������²������ݵ�λ�� 
	cout << ret1.second << endl;		//1(true)	��ʾ����ɹ�
	//����ʧ�ܣ��������ݵĵ�������false
	//����ɹ����²������ݵĵ�������true


	//2.����ԭ�ͣ�iterator insert(iterator position,const value_type& val);
	//��һ������ֻ��һ�����飬��Ϊ���������������ʣ�ֻ�ǽ���������ݿ��������ĵ�������λ��
	//��������һ���ʾ�������������ǰ�����һ������
	//set������ɺ�Ҫ�������������������
	s.insert(ret.first, 100);
	printSet(s);		//1 3 4 5 10 20 100
	//insert(iterator,val);		iteratorֻ��һ��λ�ý��飬�������ݵ�λ�ò�һ����ָ��������֮ǰ

	//3.����һ������
	//����ԭ�ͣ�
	//template<class InputIterator>	
	//void insert(InputIterator first,InputIterator last);

	int arr2[] = { 5,12,17,13,25,20,18,12 };
	s.insert(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
	printSet(s);	//1 3 4 5 10 12 13 17 18 20 25 100
}

//ɾ��
void test4()
{
	int arr[] = { 17,20,12,17,13,25,5,18,12 };
	set<int> s;
	s.insert(arr, arr + sizeof(arr) / sizeof(arr[0]));
	printSet(s);	//5 12 13 17 18 20 25

	//ɾ��
	//1.��ֵɾ��
	//����ԭ�ͣ�size_type erase erase(const value_type& val);
	//����ֵ��ɾ�������ݸ���	ֻ����1����0����ΪԪ�ز��ظ�	(size_type���ڲ������ݣ��ⲿ���շ���ֵ���������ͽ���)
	int size = s.erase(18);
	printSet(s);	//5 12 13 17 20 25
	cout << size << endl;	//1	���ݴ��ڣ�ɾ���ɹ�

	size = s.erase(1000);
	cout << size << endl;	//0	���ݲ����ڣ�ɾ��ʧ��

	//2.��������λ��ɾ��
	//����ԭ�ͣ�void erase(iterator position);
	//ɾ���ǰ��������������������λ��ɾ���ģ����ǰ������λ��ɾ����
	s.erase(s.begin());	//����ҿ������䣬��Ҫɾ��end������λ�ã��ᱨ��Խ�磩������begin��������end
	printSet(s);		//12 13 17 20 25		ɾ���Ĳ��ǵ�һ�������Ԫ�أ�����С��Ԫ��

	//3.������������ɾ��
	//�޷���ֵ
	s.erase(++s.begin(), --s.end());
	printSet(s);		//12 25
}

//swap��ǳ������ֻ�ύ�����ڵ��ָ��  clear   
void test5()
{
	int arr1[] = { 5,3,2,6,4 };
	int arr2[] = { 8,7,9,6,4 };
	set<int> s1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
	set<int> s2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));

	cout << "����ǰ��" << endl;
	cout << "s1:";
	printSet(s1);
	cout << "s2:";
	printSet(s2);
	//����ǰ��
	//s1: 2 3 4 5 6
	//s2: 4 6 7 8 9

	s1.swap(s2);

	cout << "������" << endl;
	cout << "s1:";
	printSet(s1);
	cout << "s2:";
	printSet(s2);
	//������
	//s1 : 4 6 7 8 9
	//s2 : 2 3 4 5 6

	cout << s1.size() << endl;		//5
	s1.clear();
	cout << s1.size() << endl;		//0
}

//emplace�����첢�Ҳ������ݣ���insert��������insert�����ݱ����ȴ����ã�emplace���ã�
struct Person
{
	std::string name;
	int age;

	Person(const std::string& n, int a)
		: name(n)
		, age(a)
	{}

	//ָ���ȽϹ���
	//�������ʹ������const�������β���
	//����ᱨ��������"<":û���ҵ�����" const_Ty"���͵���������������(��û�пɽ��ܵ�ת��)
	bool operator<(const Person& other) const
	{
		return age < other.age;
	}
};

void test6()
{
	set<Person> people;

	//ʹ��emplaceֱ�ӹ��첢����Ԫ��
	people.emplace("Alice", 25);
	people.emplace("Bob", 30);
	people.emplace("Charlie", 20);

	//������ӡset�е�Ԫ��
	for (const auto& person : people)
	{
		std::cout << person.name << " - " << person.age << std::endl;
	}
	//�����
	//Charlie - 20
	//Alice - 25
	//Bob - 30
}

//find	count
void test7()
{
	set<int> s;
	s.insert(20);
	s.insert(30);
	s.insert(50);
	s.insert(40);
	s.insert(10);
	printSet(s);		//10 20 30 40 50

	//find���ҵ��˷����ҵ������ݵĵ�����λ�ã�û���ҵ�����end������λ��
	//�ҵ���
	set<int>::iterator it = s.find(30);
	cout << *it << endl;	//30
	s.erase(it);
	printSet(s);		//10 20 40 50

	//û���ҵ�
	auto it2 = s.find(60);
	if (it2 == s.end())
		cout << "û���ҵ�" << endl;	//û���ҵ�

	//count:ͳ��ָ�����ݵĸ���������ֵ��0����1

	//�ҵ���
	int size = s.count(20);
	cout << size << endl;	//1

	//û���ҵ�
	size = s.count(100);
	cout << size << endl;	//0
}

//set�еĲ��ҡ������ɾ����ʱ�临�Ӷȶ���O(logn)

//setĬ���ǰ���less�Ƚϵģ�Ĭ��������С�ڵ����ݷ�����ߣ����ڵ����ݷ����ұߣ�
void test8()
{
	//�Զ������ıȽϹ���������Ҫ���� > ����������� < �������ָ���ȽϹ���
	//�����ȶ���һ����set���캯����3����������һ�����󣬵ڶ����ǱȽϹ��򣬵������ǵײ�����
	
	//Ĭ���ǰ���С�ڽ��бȽϵ�
	//less����С�ڱȽϣ�������ģ�greater���մ��ڱȽϣ��ǽ����
	set<int,greater<int>> s;	
	s.insert(20);
	s.insert(30);
	s.insert(50);
	s.insert(40);
	s.insert(10);

	for (const auto& e : s)
		cout << e << " ";
	cout << endl;
}

//set��key��value����һ����map�е�key����һ����map�е�key��value���Բ�һ��

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	test8();
	return 0;
}