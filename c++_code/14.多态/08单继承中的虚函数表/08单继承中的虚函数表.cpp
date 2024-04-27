#include <iostream>
#include <string>

using namespace std;

class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }

private:
	int a;
};

class Derive :public  Base {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
	virtual void func4() { cout << "Derive::func4" << endl; }

private:
	int b;
};

typedef void(*vfptr)();		//vfptr�Ǻ���ָ��

void printVTable(vfptr vfTable[])	//����ָ������
{
	cout << "����ַ��" << vfTable << endl;
	vfptr* fptr = vfTable;
	while (*fptr != nullptr)
	{
		(*fptr)();		//*fptr���麯��ָ��
		++fptr;
	}
}

void test()
{
	Base b;
	Derive d;
	cout << "Base��" << endl;
	//˼·��ȡ��b��d�����ͷ4bytes����������ָ�룬ǰ������˵���麯��������һ�����麯��ָ���ָ�����飬
	//���������������һ��nullptr
	//1.��ȡb�ĵ�ַ��ǿת��һ��int*��ָ��
	//2.�ٽ�����ȡֵ����ȡ����b����ͷ4bytes��ֵ�����ֵ����ָ������ָ��
	//3.��ǿת��vfptr*����Ϊ������һ����vfptr����(�麯��ָ������)�����顣
	//4.���ָ�봫�ݸ�printVTable���д�ӡ���
	//5.��Ҫ˵�����������ӡ���Ĵ��뾭�����������Ϊ��������ʱ�����Ĵ����ɾ���
	//��������û�з�nullptr������Խ�磬���Ǳ����������⡣
	//����ֻ��Ҫ��Ŀ¼���� - ���� - �������������ٱ���ͺ��ˡ�
	vfptr* vftable = (vfptr*)(*(int*)&b);	
	//vftable����ǰ4���ֽڵ�ֵ����һ��ָ���麯��ָ�������ָ�루�麯����ָ�룩��ָ��ָ��������׵�ַ
	printVTable(vftable);
	//�����
	//Base��
	//����ַ��00CC9B34
	//Base::func1
	//Base::func2

	cout << "Derive��" << endl;
	vftable = (vfptr*)(*(int*)&d);
	printVTable(vftable);
	//Derive��
	//����ַ��00CC9B64
	//Derive::func1
	//Base::func2
	//Derive::func3
	//Derive::func4
}

int main()
{
	test();
	return 0;
}