#include <iostream>

using namespace std;

class A
{
public:
	virtual void fun(){}
};

class B : public A
{

};

void test()
{
	//c����
	int a = 10;
	double f = 1.2;
	//��ʽ����ת��
	a = f;

	int* pa = &a;
	//ǿ������ת��
	a = (int)pa;

	int* p = (int*)malloc(4);

	//c++������ת��
	//1.static_cast��֧�����е���ʽ����ת��
	//����������̳��аѸ����������ת��(ֻ����ָ��������ã�������ֵ����)
	//��֧��������ǿ������ת��
	a = static_cast<int>(f);
	A* a1 = new A;
	//B* b1 = (B*)a1;		//����ȫ
	B* b1 = static_cast<B*>(a1);

	A a2;
	B b2;
	//a2 = (A)b2;		//error
	//b2 = static_cast<B>(a2);			//error


	//2.reinterpret_cast��֧��ǿ������ת������д���ͣ�
	A a3;
	A* a4 = &a3;
	//a3 = reinterpret_cast<A>(a4);		//error
	a = reinterpret_cast<int>(pa);


	//3.const_cast��ȥ��������const����
	volatile const int c = 10;
	volatile const int* pcc = &c;		
	int* pc = const_cast<int*>(&c);
	*pc = 20;
	//*pcc = 30;		//error�����ʽ�����ǿ��޸ĵ���ֵ
	cout << *pc << endl;	//20
	//cout << c << endl;		//10��ԭ���Ǳ���������const����һ���Ż���û�д��ڴ��ж�ȡ���ݣ���������constȷ��ֵû�䣬��10��ʵ�����ڴ��е�ֵ��20
	//����취�����Ϲؼ���volatile����ʾÿ�λ�ȡ���ݴӼĴ����ж�ȡ���ݣ����ܴ��ݴ��ж�ȡ����
	cout << c << endl;			//20
	//�﷨ֻ�ڱ���ʱ��Ч���������������Ϳ��Դ�͸����﷨������


	//4.dynamic_cast��ֻ���ڶ�̬�����µĸ�������/ָ������������/ָ��ת��
	//���ת���Ƿ�ȫ��ֻ�а�ȫ�Ż�ת���ɹ�������ȫ����nullptr
	//���� -> ����	����ת��
	//���� -> ����	����ת��
	A* pppa = new A;
	B* pppb = dynamic_cast<B*>(pppa);
	B* pppb1 = static_cast<B*>(pppa);
	cout << pppb << endl;		//00000000  	����ȫ��ת��	�൱������һ�����ͼ��	��ȫת���ɹ�������ȫת��ʧ��
	cout << pppb1 << endl;		//00BAF320		

	A* pppa2 = new B;
	pppb = dynamic_cast<B*>(pppa2);
	pppb1 = static_cast<B*>(pppa2);
	cout << pppb << endl;		//00BAF350
	cout << pppb1 << endl;		//00BAF350
}

int main()
{
	test();
	return 0;
}