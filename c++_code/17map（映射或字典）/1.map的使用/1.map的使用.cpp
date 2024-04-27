#include <iostream>
#include <map>
#include <string>

using namespace std;

//�������������
template <class T1,class T2>
void printMap(const map<T1, T2>& m)
{
	//map�е�������pair 
	typename map<T1,T2>::const_iterator it = m.begin();
	while (it != m.end())
	{
		cout << (*it).first << " " << it->second << endl;
		it++;
	}
}

//�������������
template <class T1, class T2>
void printMapr(const map<T1, T2>& m)
{
	//map�е�������pair 
	typename map<T1, T2>::const_reverse_iterator it = m.rbegin();
	while (it != m.rend())
	{
		cout << (*it).first << " " << it->second << endl;
		it++;
	}
}

//���캯��
void test1()
{
	map<int, int> m1;
	
	//���������ʼ��
	pair<int, int> arr[] = { pair<int, int>(5,5),pair<int, int>(1,2),
	pair<int, int>(3,3),pair<int, int>(0,0),pair<int, int>(1,3) };
	map<int, int> m2(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (const auto& e : m2)
		cout << e.first << " " << e.second << endl;
	printMap(m2);		//�������������
	//�����
	//0 0
	//1 2
	//3 3
	//5 5
	//0 0
	//1 2
	//3 3
	//5 5

	printMapr(m2);		//�������������
	//�����
	//5 5
	//3 3
	//1 2
	//0 0

	//����˳�򣺰���keyֵ��С����������ײ��Ƕ�������������������������б�����
	//map�в��ܴ����ͬ��keyֵ��valueֵ������ͬ
	//map�в����޸�key�������޸�value

	map<int, int, greater<int>> m3(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (const auto& e : m3)
		cout << e.first << " " << e.second << endl;
	//�����	�ɴ�С���
	//5 5
	//3 3
	//1 2
	//0 0

	const auto& it = m3.begin();
	it->second = 10;	//value�����޸�
	//it->first = 20;	//key�����޸�

	//��������
	map<int, int> m4(m2);	
}

//���ʣ�at��[]
void test2()
{
	//[]
	map<int, int> m;
	//���ʣ�����    �޸ģ�д��	  ����	
	m[4] = 10;	//�൱�ڴ���һ��pair<int,int>(4,10)�Ķ�����в���
	cout << m[5] << endl;//�����0����ָ��value��Ĭ����0��
	//�൱�ڴ���һ��pair<int,int>(5,0)�Ķ�����в���
	
	for (const auto& e : m)
		cout << e.first << " " << e.second << endl;
	//�����
	//4 10
	//5 0

	m[5] = 20;	//�޸�	m[5]�ķ���ֵ��value&��ֱ���޸�vaule����Ϊ20
	for (const auto& e : m)
		cout << e.first << " " << e.second << endl;
	//�����
	//4 10
	//5 20

	//���ͣ�
	//operator[](k)	�ȼ���
	//(*( (this->insert(	make_pair(k,mapped_type()) ) ).first )).second	 
	//insert�ķ���ֵ��pair<iterator,bool>	
	//*iterator��pair<int,int>
	
	//operator[](k)
	//1.����һ��pair���������ǣ�k	value��valueȱʡֵ����0ֵ��
	//2.�����һ��������pair����
	//	2.1����ɹ�������pair<pair����ĵ�����,true>
	//	2.2����ʧ�ܣ�����pair<�Ѿ����ڵļ�ֵΪk��pair����ĵ�����,false>
	//3.��ȡ���뷵��ֵ��first��Ա����һ��map�е�pair����ĵ�����
	//4.�����õ�3���еĵ��������õ�map�е�pair����
	//5.�ӵ�4����õ�map�е�pair�����value
	//	5.1�������ɹ���value��ȱʡֵ�����룩
	//	5.2�������ʧ�ܣ����Ƕ�Ӧ��key��value

	//at
	//atԽ����ʻ����쳣
	cout << m.at(5) << endl;	//20
	//
	cout << m.at(6) << endl;	//�����ڵ�key������벢�����value�������쳣

	//�ܽ᣺һ��ʹ�ã���ʹ��at
}

//����
void test3()
{
	map<int, int> m;

	//����Ĳ��뷽ʽ��
	//auto ret = m.insert��1, 1��;	//error

	//��ȷ�Ĳ��뷽ʽ��
	//1.����pair���캯����������
	auto ret = m.insert(pair<int, int>(1, 1));
	//2.����make_pair������������
	ret = m.insert(make_pair(2, 3));
	cout << ret.first->first << endl;	//2
	cout << ret.second << endl;		//1		��ʾ����ɹ���
	//��һ��first�ǵ��������ڶ���first��key
}

void test4()
{

}

void test5()
{

}

void test6()
{

}

int main()
{
	//test1();
	//test2();
	test3();
	test4();
	test5();
	test6();
	return 0;
}