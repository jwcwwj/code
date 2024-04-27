#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>	//文件IO流的头文件
#include <string.h>

using namespace std;

//文本文件的读写	字符流读写
void test1()
{
	//ofstream：输出文件流	输出到文件
	//写文件
	//输出文件流ofstream打开文件
	//方式1：直接打开文件		ofstream fout("文件名");
	//ofstream fout("文件IO流.cpp");
	//方式2：创建ofstream对象，再用open函数打开 ofstream 对象;	对象.open("文件名");
	ofstream fout1;
	fout1.open("text.txt");

	//判断文件有没有打开成功，使用is_open函数
	if (!fout1.is_open())		//打开成功返回true，打开失败返回false
		cout << "file not open" << endl;
	//输出流打开文件，文件不存在创建文件之后打开，文件存在直接打开

	//写内容  输出到文件里面去
	//方式1：文本形式写，按照字符写
	fout1 << "text.txt" << endl;

	fout1.close();		//不关页眉关系，因为ofstream里面有析构，会调用close进行关闭


	//ifstream：输入文件流	从文件中输入
	//读文件：文件不存在打开失败
	ifstream fin("text.txt");
	char arr[100];
	fin >> arr;
	cout << arr;

	ofstream fout2;
	fout1.open("text.txt");
	//写
	fout2.put('a');

	//读
	char ch;
	ch = fin.get();
	fin.get(ch);
	fin.get(arr, 100);
	//put只能放字符，get可以读字符也可以读字符串。

	fin.getline(arr, 100);	
	//读一行，默认是读取一行，给定字符个数表示读取这么多字符个数结束
	//如果要读的字符个数大于读取的行的个数，就把本行读完结束。
}

struct Student
{
	char name[10];
	int age;
};

//二进制的读写：字节流读写
void test2()
{
	//文本形式的写
	ofstream fout("test.txt");
	Student stu;
	stu.age = 30;
	strcpy(stu.name, "abc");
	fout << stu.name << endl;
	fout << stu.age << endl;
	fout.close();

	//二进制的写
	ofstream fout2("test.binary.txt");
	fout2.write((char*)&stu, sizeof(stu));
	fout2.close();

	//二进制的读
	ifstream fin("test.binary.txt",ifstream::binary);	//第二个参数表示按照二进制打开
	Student stu1;
	fin.read((char*)&stu1, sizeof(stu1));	//不关注是否有空格，是否有换行
	cout << stu1.name << endl;	//abc
	cout << stu1.age << endl;	//30
}

int main()
{
	//test1();		//文本文件的读写
	test2();		//二进制的读写
	return 0;
}