#include <iostream>
#include <string>

using namespace std;

class Person
{
protected:
	string _name;	//����
	string _sex;	//�Ա�
	int _age;		//����
};

class Student : public Person
{
public:
	int _No; // ѧ��
};

void test()
{
	Student sobj;
	//1.���������Ը�ֵ���������/ָ��/���ã���Ƭ��
	//���������͵���ʽ����ת��һ��
	//���� -> ����
	Person pobj = sobj;		//�����˿���������һ������
	Person* pp = &sobj;
	Person& rp = sobj;

	//2.������󣨸��ࣩ���ܸ�ֵ�������ࣨ���ࣩ����
	//sobj = pobj;		//error
	
	//3.���ࣨ���ࣩ��ָ�����ͨ��ǿ������ת����ֵ�������ࣨ���ࣩ��ָ��
	//����ָ�롢���ò���ֱ�Ӹ�ֵ������ָ������
	Student* ps1 = (Student*)pp; //�������ת���ǿ��Եġ�	pp�����ŵ���Student�ĵ�ַ
	ps1->_No = 10;
	pp = &pobj;		//pp�����ŵ���Person�ĵ�ַ

	//�����������ʲ������������ĳ�Ա����Ҫд
	Student* ps2 = (Student*)pp; // �������ת��ʱ��Ȼ���ԣ����ǻ����Խ����ʵ�����
	//ps2->_No = 10;	//error��Խ�����
}

int main()
{
	test();
	return 0;
}