#include <iostream>
#include <numeric>		//��ֵͷ�ļ�	�ۼ���Ҫ������ͷ�ļ�
#include <vector>

using namespace std;

//accumulate�����㷨�����Ƕ������е�Ԫ�ؽ����ۼ�
struct Mul2
{
	//x = Mul2(x,y);
	int operator()(int x, int y) { return x + 2 * y; }		//x���ۼӵ�ֵ��y���µ�Ҫ�ӵ�ֵ
};

void test()
{
	// �������е�Ԫ�ؽ����ۼ�
	vector<int> v{ 10, 20, 30 };
	cout << accumulate(v.begin(), v.end(), 0) << endl;	//60
	// �������е�ÿ��Ԫ�س�2��Ȼ���ۼ�
	cout << accumulate(v.begin(), v.end(), 0, Mul2()) << endl;	//120
	cout << accumulate(v.begin(), v.end(), 50, Mul2()) << endl;	//170
}

int main()
{
	test();
	return 0;
}

//1.STL�㷨��������		8
//2.STL�㷨md�ĵ�		3
//3.STL�ܽ�md�ĵ�		11
//4.��վ����			12