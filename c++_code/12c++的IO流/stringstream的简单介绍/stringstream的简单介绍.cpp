#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>	//文件IO流的头文件
#include <sstream>	//字符串流
#include <string.h>

using namespace std;

void test()
{
	//c语言：atoi、atof、itoa(整数转成字符串)、itof
	int a = 10;		//10进制	10
	int b = 010;	//8进制		8
	int c = 0x10;	//16进制	16
	char arr[100];
	itoa(a, arr, 10);	//把数字a按10进制转换之后存储在arr中
	//第一个参数：要转换的值，第二个参数：转换之后存储在哪，第三个参数：按几进制转换
	cout << arr << endl;	//10
	itoa(a, arr, 8);
	cout << arr << endl;	//12
	itoa(a, arr, 16);
	cout << arr << endl;	//a

	//sprintf：输出到一个字符串里面 
	sprintf(arr, "%d", a);		//把a输出到arr中，"%d"是输出格式
	//printf("%d", 5);	//输出到控制台

	//c++
	stringstream ss;		//输入输出字符流对象
	//1.作用在于把数值类型转成字符串
	string str;
	ss << a;
	ss >> str;		//str里面保留a的字符串形式

	ss.clear();		//流的状态位的清空(下一次转换之前，流对象需要调用clear接口清空流对象中的状态位)
	//是清空状态位，不是清空内容，表示可以给流重新传值了，但里面的值还是a

	float f = 2.3;
	ss << f;
	ss >> str;

	//ss.str(重置内容);	//重置stringstream对象中的内容
	ss.str("");		//重置为空

	//ss.str();		//获取stringstream对象中的内容
	str = ss.str();	//用string对象接受转变之后的字符串，字符串在流里面

	ss.clear();		 
	ss << f;		//ss是流，相当于cout（控制台），把f输出到ss流中
	str = ss.str();		//获取字符串形式的f

	//2.字符串拼接
	ss.str("");
	ss << "123" << "345" << "789";
	cout << ss.str();		//123456789   流里面的内容是123456789
}

int main()
{
	test();
	return 0;
}