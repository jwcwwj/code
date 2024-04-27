#include <iostream>
#include <string.h>

using namespace std;

//�е�
template <class T>
bool isEqual(T& a, T& b)
{
	return a == b;
}

//ģ����ػ�
//ǰ�᣺����һ��ͨ�õ�ģ��

//1.ȫ�ػ�
template <>
bool isEqual<const char*>(const char*& a,const char*& b)
{
	return strcmp(a, b) == 0;		//strcmp����0��ʾ��ȣ�������0��ʾ�����
}

//1.Ҳ����дһ����ͨ�ĺ�����ȫ�ػ�������
//2.����ͨ������ģ�庯�����ʵ�ʱ��������ͨ��������ͨ������ȫƥ�䣩
//3.����ͨ�ĺ�����ģ�庯��ͬʱ����ʱ������һ�����������ͨ����
bool isEqual(const char* a, const char* b)
{
	return strcmp(a, b);
}

void test()
{
	//bool ret = isEqual(1, 2);
	//ret = isEqual(1.2, 1.2);
	bool ret = isEqual("123", "123");

	const char* ptr = "123";			//�����ַ���
    const char ptr2[] = "123";			//��constΪ�˺ͳ����ַ�������һ��

	ret = isEqual(ptr, ptr2);			
	cout << ret << endl;		//0
}

int main()
{
	test();
	return 0;
}