# 1.c语言的输入与输出

C语言中我们用到的最频繁的输入输出方式就是scanf ()与printf()**。 **scanf(): 从标准输入设备(键盘)读取数据，并将

值存放在变量中。printf(): 将指定的文字/字符串输出到标准输出设备(屏幕)。注意宽度输出和精度输出控制。C语

言借助了相应的缓冲区来进行输入与输出。



cin和cout是对象，重载了输出类型。

printf和scanf是库函数，没有重载输出类型。



对输入输出缓冲区的理解：

1.可以屏蔽掉低级I/O的实现，低级I/O的实现依赖操作系统本身内核的实现，所以如果能够屏蔽这部分的差异，可

以很容易写出可移植的程序。

2.可以使用这部分的内容实现"行"读取的行为，对于计算机而言是没有“行”这个概念，有了这部分，就可以定

义“行”的概念，然后解析缓冲区的内容，返回一个“行”。

![image-20230701173658717](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230701173658717.png)

写数据是先写到缓冲区的，读数据是从缓冲区读的。



# 2.流是什么

“流”即是流动的意思，是物质从一处向另一处流动的过程，是对一种有序连续且具有方向性的数据（ 其单位可以是

bit,byte,packet ）的抽象描述。 C++流是指信息从外部输入设备（如键盘）向计算机内部（如内存）输入和从内

存向外部输出设备（显示器）输出的过程。这种输入输出的过程被形象的比喻为“流”。它的特性是：有序连续、具

有方向性为了实现这种流动，C++定义了I/O标准类库，这些每个类都称为流/流类，用以完成某方面的功能。



# 3.c++IO流

C++系统实现了一个庞大的类库，其中ios为基类，其他类都是直接或间接派生自ios类。

![image-20230701174232648](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230701174232648.png)



## 3.1c++标准IO流

C++标准库提供了4个全局流对象cin、cout、cerr（标准错误输出）、clog（日志输出），使用cout进行标准输

出，即数据从内存流向控制台(显示器)**。使用**cin进行标准输入即数据通过键盘输入到程序中，同时C++标准库还提

供了cerr用来进行标准错误的输出，以及clog进行日志的输出，从上图可以看出，cout、cerr、clog是ostream类

的三个不同的对象，因此这三个对象现在基本没有区别，只是应用场景不同。在使用时候必须要包含文件并引入

std标准命名空间。

```c++
int main()
{
    floast f;
    cin >> f;
    char arr[10];
    cin >> arr;
    cerr << f << endl;		//标准错误输出
    clog << arr << endl;	//日志输出
    return 0;
}
```

注意：

1.cin为缓冲流。键盘输入的数据保存在缓冲区中，当要提取时，是从缓冲区中拿。如果一次输入过多，会留在那

儿慢慢用，如果输入错了，必须在回车之前修改，如果回车键按下就无法挽回了。只有把输入缓冲区中的数据取完

后，才要求输入新的数据。

2.输入的数据类型必须与要提取的数据类型一致，否则出错。出错只是在流的状态字state中对应位置位（置1），

程序继续。

3.空格和回车都可以作为数据之间的分格符，所以多个数据可以在一行输入，也可以分行输入。但如果是字符型和

字符串，则空格（ASCII码为32）无法用cin输入，字符串中也不能有空格。回车符也无法读入。

4.cin和cout可以直接输入和输出内置类型数据，原因：**标准库已经将所有内置类型的输入和输出全部重载了。

5.对于自定义类型，如果要支持cin和cout的标准输入输出，需要对<<和>>进行重载。

6.在线OJ中的输入和输出：

​		6.1对于IO类型的算法，一般都需要循环输入。

```c++
//单个元素循环输入
while(cin>>a)
{
	// ...
}

//多个元素循环输入
while(c>>a>>b>>c)
{
	// ...
}

//整行接收
while(cin>>str)
{
	//...
}
```

6.2输出：严格按照题目的要求进行，多一个少一个空格都不行。



## 3.2c++文件IO流

查看二进制文件：

1.使用Edit	with	Notepad++软件打开二进制文件；

2.使用插件HEX-Editor中的View in HEX打开查看字节和ASILL（16进制）。（windows下查看是小端存储）



备注：文本形式写的用文本形式读，二进制形式写的用二进制形式读，否则会有问题。



C++根据文件内容的数据格式分为**二进制文件**和**文本文件**。采用文件流对象操作文件的一般步骤：

1.定义一个文件流对象：

​	1.1ifstream ifile(只输入用)

​	1.2ofstream ofile(只输出用)

​	1.3fstream iofile(既输入又输出用)

2.使用文件流对象的成员函数打开一个磁盘文件，使得文件流对象和磁盘文件之间建立联系

3.使用提取和插入运算符对文件进行读写操作，或使用成员函数进行读写

4.关闭文件

```c++
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
```

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>	//文件IO流的头文件
#include <string.h>
#include <string>

using namespace std;

// 使用文件IO流用文本及二进制方式演示读写配置文件
struct ServerInfo
{
	char _ip[32]; // ip
	int _port; // 端口
};
struct ConfigManager
{
public:
	ConfigManager(const char* configfile = "bitserver.config")
		:_configfile(configfile)
	{}
	void WriteBin(const ServerInfo& info)
	{
		// 这里注意使用二进制方式打开写
		ofstream ofs(_configfile, ifstream::in | ifstream::binary);
		ofs.write((const char*)&info, sizeof(ServerInfo));
		ofs.close();
	}
	void ReadBin(ServerInfo& info)
	{
		// 这里注意使用二进制方式打开读
		ifstream ifs(_configfile, ifstream::out | ifstream::binary);
		ifs.read((char*)&info, sizeof(ServerInfo));
		ifs.close();
	}
	void WriteText(const ServerInfo& info)
	{
		// 这里会发现IO流写整形比C语言那套就简单多了，
		// C 语言得先把整形itoa再写
		ofstream ofs(_configfile);
		ofs << info._ip << endl;
		ofs << info._port << endl;
		ofs.close();
	}
	void ReadText(ServerInfo& info)
	{
		// 这里会发现IO流读整形比C语言那套就简单多了，
		// C 语言得先读字符串，再atoi
		ifstream ifs(_configfile);
		ifs >> info._ip;
		ifs >> info._port;
		ifs.close();
	}
private:
	string _configfile; // 配置文件
};
int main()
{
	ConfigManager cfgMgr;
	ServerInfo wtinfo;
	ServerInfo rdinfo;
	strcpy(wtinfo._ip, "127.0.0.1");
	wtinfo._port = 80;
	// 二进制读写
	cfgMgr.WriteBin(wtinfo);
	cfgMgr.ReadBin(rdinfo);
	cout << rdinfo._ip << endl;
	cout << rdinfo._port << endl;
	// 文本读写
	cfgMgr.WriteText(wtinfo);
	cfgMgr.ReadText(rdinfo);
	cout << rdinfo._ip << endl;
	cout << rdinfo._port << endl;
	return 0;
}
```



# 4.stringstream的简单介绍

c语言中，将一个整形变量的数据转化为字符串格式，如何去做？

1.使用itoa()函数；

2.使用sprintf()函数。

但是两个函数在转化时，都得需要先给出保存结果的空间，那空间要给多大呢，就不太好界定，而且转化格式不匹

配时，可能还会得到错误的结果甚至程序崩溃。  



在C++中，可以使用stringstream类对象来避开此问题。

在程序中如果想要使用stringstream，必须要包含头文件。在该头文件下，标准库三个类：istringstream、

ostringstream 和 stringstream，分别用来进行流的输入、输出和输入输出操作，本文主要介绍stringstream。

stringstream主要可以用来：

1.将数值类型数据格式化为字符串；

2.字符串拼接（一般不使用，推荐使用string类对象拼接操作）

```c++
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
```

注意：

1.stringstream实际是在其底层维护了一个string类型的对象用来保存结果。

2.多次数据类型转化时，一定要用clear()来清空，才能正确转化，但clear()不会将stringstream底层的string对象

清空。

3.可以使用s. str("")方法将底层string对象设置为""空字符串。

4.可以使用s.str()将让stringstream返回其底层的string对象。

5.**stringstream使用string类对象代替字符数组，可以避免缓冲区溢出的危险**，而且其会对参数类型进行推演，

不需要格式化控制，也不会出现格式化失败的风险，因此使用更方便，更安全。