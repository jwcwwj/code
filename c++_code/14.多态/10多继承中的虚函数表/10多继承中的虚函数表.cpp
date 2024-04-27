#include <iostream>
#include <string>

using namespace std;

class Base1
{
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }

private:
	int b1;
};

class Base2
{
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }

private:
	int b2;
};

class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }

private:
	int d1;
};

typedef void(*vfptr)();

void printVTable(vfptr vfTable[])
{
	cout << "����ַ��" << vfTable << endl;
	vfptr* fptr = vfTable;
	while (*fptr != nullptr)
	{
		(*fptr)();
		++fptr;
	}
}

void test()
{
	Derive d;
	cout << "Derive��" << endl;
	vfptr* vTableb1 = (vfptr*)(*(int*)&d);
	printVTable(vTableb1);
	//�����
	//Derive��
	//����ַ��002A9B94
	//Derive::func1
	//Base1::func2
	//Derive::func3
	//����������ӵ��麯�����麯��ָ����ڵ�һ���麯����̳е��麯�����麯��ָ��ĺ���

	vfptr* vTableb2 = (vfptr*)(*(int*)((char*)&d + sizeof(Base1)));		//ָ��ƫ��
	printVTable(vTableb2);
	//����ַ��002A9BA8
	//Derive::func1
	//Base2::func2
}

int main()
{	
	test();
	return 0;
}