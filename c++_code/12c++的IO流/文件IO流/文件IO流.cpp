#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>	//�ļ�IO����ͷ�ļ�
#include <string.h>

using namespace std;

//�ı��ļ��Ķ�д	�ַ�����д
void test1()
{
	//ofstream������ļ���	������ļ�
	//д�ļ�
	//����ļ���ofstream���ļ�
	//��ʽ1��ֱ�Ӵ��ļ�		ofstream fout("�ļ���");
	//ofstream fout("�ļ�IO��.cpp");
	//��ʽ2������ofstream��������open������ ofstream ����;	����.open("�ļ���");
	ofstream fout1;
	fout1.open("text.txt");

	//�ж��ļ���û�д򿪳ɹ���ʹ��is_open����
	if (!fout1.is_open())		//�򿪳ɹ�����true����ʧ�ܷ���false
		cout << "file not open" << endl;
	//��������ļ����ļ������ڴ����ļ�֮��򿪣��ļ�����ֱ�Ӵ�

	//д����  ������ļ�����ȥ
	//��ʽ1���ı���ʽд�������ַ�д
	fout1 << "text.txt" << endl;

	fout1.close();		//����ҳü��ϵ����Ϊofstream�����������������close���йر�


	//ifstream�������ļ���	���ļ�������
	//���ļ����ļ������ڴ�ʧ��
	ifstream fin("text.txt");
	char arr[100];
	fin >> arr;
	cout << arr;

	ofstream fout2;
	fout1.open("text.txt");
	//д
	fout2.put('a');

	//��
	char ch;
	ch = fin.get();
	fin.get(ch);
	fin.get(arr, 100);
	//putֻ�ܷ��ַ���get���Զ��ַ�Ҳ���Զ��ַ�����

	fin.getline(arr, 100);	
	//��һ�У�Ĭ���Ƕ�ȡһ�У������ַ�������ʾ��ȡ��ô���ַ���������
	//���Ҫ�����ַ��������ڶ�ȡ���еĸ������Ͱѱ��ж��������
}

struct Student
{
	char name[10];
	int age;
};

//�����ƵĶ�д���ֽ�����д
void test2()
{
	//�ı���ʽ��д
	ofstream fout("test.txt");
	Student stu;
	stu.age = 30;
	strcpy(stu.name, "abc");
	fout << stu.name << endl;
	fout << stu.age << endl;
	fout.close();

	//�����Ƶ�д
	ofstream fout2("test.binary.txt");
	fout2.write((char*)&stu, sizeof(stu));
	fout2.close();

	//�����ƵĶ�
	ifstream fin("test.binary.txt",ifstream::binary);	//�ڶ���������ʾ���ն����ƴ�
	Student stu1;
	fin.read((char*)&stu1, sizeof(stu1));	//����ע�Ƿ��пո��Ƿ��л���
	cout << stu1.name << endl;	//abc
	cout << stu1.age << endl;	//30
}

int main()
{
	//test1();		//�ı��ļ��Ķ�д
	test2();		//�����ƵĶ�д
	return 0;
}