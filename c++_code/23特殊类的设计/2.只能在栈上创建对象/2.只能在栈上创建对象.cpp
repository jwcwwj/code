#include <iostream>

using namespace std;

//ֻ����ջ�ϴ�������(��ֹ�ڶ��ϴ�������)
//����1��
class StackObj
{
public:
	//���еķ������ù��캯����������
	static StackObj getObj()	//staticֻ�ܵ���static����
	{
		return StackObj();
	}

private:
	//���캯��˽�У����ⲿ�޷����ã�ֻ�������ڲ�����
	StackObj()
	{}

	//��������ջ�ϴ�������
};

StackObj so = StackObj::getObj();	//��ȫ�ִ��������������ݶ�

void test1()
{
	StackObj so = StackObj::getObj();
	//new StackObj();		//�����޷���������
}

//����2��
class StackObj1
{
public:
	//��ֹ����operator new
	void* operator new(size_t n) = delete;
};

void test2()
{
	//StackObj1* so = new StackObj1;	//������ɾ���ĺ���
	StackObj1 so1;
}

int main()
{
	test1();
	test2();
	return 0;
}