#include <iostream>

using namespace std;

//���ܱ��̳�
//����1��
class A final		//final��ʾ���յ���˼����A���ܱ��̳�
{

};

/*
class B : public A	//���ܼ̳���A�����ܽ���final���������������ࣩ
{

};
*/

//����2������Ĺ��캯������Ϊ˽�е�
class C
{
public:

private:
	C() {};
};

class D : public C
{};

void test()
{
	//D d;	//error���޷����á�D����Ĭ�Ϲ��캯��--������ɾ���ĺ���

}

int main()
{
	test();
	return 0;
}