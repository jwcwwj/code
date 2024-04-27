#include <iostream>

using namespace std;

//ֻ���ڶ��ϴ�������
class HeapObj
{
public:
	//���ù��캯����������
	static HeapObj* getObj()
	{
		//�����Ķ�������ջ��
		//HeapObj* p = new HeapObj();
		//return p;
		return new HeapObj;
	}

	//��ֹ���캯���ĵ��ã�˽�У�ֻ�������ڲ����ã����������ⲿ���ã�
private:
	HeapObj()
	{}

	//������	����֮��ľֲ�������ջ��
	//����취��
	//1.ֻ��������ʵ�֣�����������������ʹ�ÿ������죩	c++98
	//HeapObj(const HeapObj&);
	//2.�ѿ�������дΪdelete�������к�����Ҳ����ʹ�ã�	c++11
	HeapObj(const HeapObj&) = delete;

	//��ֵ��������������µĶ���ֻ���޸��Ѿ����ڵĶ��������
};

void test()
{
	HeapObj* ptr = HeapObj::getObj();
	HeapObj::getObj();
	//HeapObj copy(*ptr);		//������ջ���ϵĶ��󣬾�ֹ��������
}

int main()
{
	test();
	return 0;
}