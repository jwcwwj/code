#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>	//�ļ�IO����ͷ�ļ�
#include <sstream>	//�ַ�����
#include <string.h>

using namespace std;

void test()
{
	//c���ԣ�atoi��atof��itoa(����ת���ַ���)��itof
	int a = 10;		//10����	10
	int b = 010;	//8����		8
	int c = 0x10;	//16����	16
	char arr[100];
	itoa(a, arr, 10);	//������a��10����ת��֮��洢��arr��
	//��һ��������Ҫת����ֵ���ڶ���������ת��֮��洢���ģ���������������������ת��
	cout << arr << endl;	//10
	itoa(a, arr, 8);
	cout << arr << endl;	//12
	itoa(a, arr, 16);
	cout << arr << endl;	//a

	//sprintf�������һ���ַ������� 
	sprintf(arr, "%d", a);		//��a�����arr�У�"%d"�������ʽ
	//printf("%d", 5);	//���������̨

	//c++
	stringstream ss;		//��������ַ�������
	//1.�������ڰ���ֵ����ת���ַ���
	string str;
	ss << a;
	ss >> str;		//str���汣��a���ַ�����ʽ

	ss.clear();		//����״̬λ�����(��һ��ת��֮ǰ����������Ҫ����clear�ӿ�����������е�״̬λ)
	//�����״̬λ������������ݣ���ʾ���Ը������´�ֵ�ˣ��������ֵ����a

	float f = 2.3;
	ss << f;
	ss >> str;

	//ss.str(��������);	//����stringstream�����е�����
	ss.str("");		//����Ϊ��

	//ss.str();		//��ȡstringstream�����е�����
	str = ss.str();	//��string�������ת��֮����ַ������ַ�����������

	ss.clear();		 
	ss << f;		//ss�������൱��cout������̨������f�����ss����
	str = ss.str();		//��ȡ�ַ�����ʽ��f

	//2.�ַ���ƴ��
	ss.str("");
	ss << "123" << "345" << "789";
	cout << ss.str();		//123456789   �������������123456789
}

int main()
{
	test();
	return 0;
}