#include <iostream>

using namespace std;

class Date
{
public:
	Date(int y = 1, int m = 1, int d = 1)
	{
		//�ж������Ƿ���Ч
		if (y <= 0 || m <= 0 || m > 12 || d <= 0 || d > getDay(y,m))
		{
			//������Ч
			_y = 1;
			_m = 1;
			_d = 1;
			cout << "������Ч����ΪĬ��ֵ1-1-1" << endl;
		}
		else
		{
			//������Ч
			_y = y;
			_m = m;
			_d = d;
		}
	} 

	int getDay(int y, int m)
	{
		static int days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = days[m];
		//�����2����Ϊ���꣬2��������1
		if (m == 2 && (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0))
			day += 1;
		return day;
	}

	//���������
	//��������
	//Date += int	���� += ����
	Date& operator+=(int day)
	{
		//�ж������Ƿ�Ϊ����	
		if (day < 0)
			return *this -= -day;	//��������û�з���������Ч�ʺܸ�
		//�������
		_d += day;
		//�ж������Ƿ����
		while (_d > getDay(_y, _m))
		{
			//��ȥ���µ�����
			_d -= getDay(_y, _m);
			//�·ݽ�λ
			++_m;
			//�ж��·��Ƿ����
			if (_m == 13)
			{
				//��ݽ�λ
				_y++;
				//��һ���1�·�
				_m = 1;
			}
		}
		return *this;	//�������֮��Ľ��
	}

	//Date + int
	//�ӷ����������֮��Ľ�������������ܸı�
	Date operator+(int day)
	{
		Date res = *this;
		return res += day;		//���ؽ��������ֵ����
	}

	//++Date	ǰ��++
	Date& operator++()
	{
		return *this += 1;
	}

	//Date++	����++
	Date operator++(int)	//ռλ��	//���������õģ�ֻ��Ϊ������ǰ��++�ͺ���++
	{
		Date res = *this;
		*this += 1;
		return res;		//ֵ����,������ֵ����
	}
	
	Date& operator-=(int day)
	{
		//�ж������Ƿ�Ϊ����
		if (day < 0)
			return *this += -day;	//��������û�з���������Ч�ʺܸ�
		_d -= day;
		while (_d <= 0)
		{
			//���ϸ��µ������ز�
			_m--;
			//�ж��·��Ƿ������Ҫע���Ⱥ�˳��
			if (_m == 0)
			{
				//���˵���һ���µ�12�·�
				_y--;
				_m = 12;
			}
			_d += getDay(_y, _m);
		}
		return *this;
	}

	//Date - int
	Date operator-(int day)
	{
		Date res = *this;
		res -= day;
		return res;
	}

	//--Date
	Date& operator--()
	{
		return *this -= 1;
	}

	//Date--
	Date operator--(int)
	{
		Date res = *this;
		*this -= 1;
		return res;
	}

	//==
	bool operator==(const Date& d)
	{
		return _y == d._y && _m == d._m && _d == d._d;
	}

	//!=
	bool operator!=(const Date& d)
	{
		//return !operator==(d);
		return !(*this == d);
	}

	//>
	bool operator>(const Date& d)
	{
		if (_y > d._y)
			return true;
		else if (_y == d._y && _m > d._m)
			return true;
		else if (_y == d._y && _m == d._m && _d > d._d)
			return true;
		else
			return false; 
	}

	//<
	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}

	//>=
	bool operator>=(const Date& d)
	{
		return (*this > d) || (*this == d);
	}

	//<=
	bool operator<=(const Date& d)
	{
		return !(*this > d);
	}

	//���������Date - Date
	int  operator-(const Date& d)
	{
		//����Ƚ�С�����ھ������ٴ��Լӵ����㣬���ԺͱȽϴ��������ͬ
		//�ԼӵĴ����������Ĵ���
		Date max = *this;
		Date min = d;
		int flag = 1;		//*this������ֵ
		if (max < min)
		{
			min = *this;
			max = d;
			flag = -1;		//d���Ǹ�ֵ
		}
		int day = 0;
		while (min < max)
		{
			++min;
			++day;
		}
		return flag * day;
	}

	//���������
	void play()
	{
		cout << "year = " << _y << " month = " << _m << " day = " << _d << endl;
	}

private:
	int _y;		//��
	int _m;		//��
	int _d;		//��
};

/* 
//�ӷ�����
void test1()
{
	Date d1(2021, 2, 4);
	Date d2(2021, 2, 4);
	Date d3(2021, 2, 4);
	Date d4(2021, 2, 4);
	d1.operator+=(1);		//2021.2.5
	d2 += 30;				
	d3 += 90;
	d4 += 360;
	d1.play();	//year = 2021 month = 2 day = 5
	d2.play();	//year = 2021 month = 3 day = 6
	d3.play();	//year = 2021 month = 5 day = 5
	d4.play();	//year = 2022 month = 1 day = 30
	d3 = d4 + 90;
	d3.play();	//year = 2022 month = 4 day = 30
	d4.play();	//�������ı�	year = 2022 month = 1 day = 30
	++d3;
	d3.play();	//year = 2022 month = 5 day = 1
	Date d5 = d3++;
	d3.play();	//year = 2022 month = 5 day = 2
	d5.play();	//year = 2022 month = 5 day = 1
	//����++
	//d5 = d4++10;	//error���������޷�ʶ��
	//d5 = d4.operator++(10);	//ok,����ǿ��Եģ���Ϊ�������������ݱ�ʾ���ã�û���ݱ�ʾǰ�ã���д����ֱ��ʶ�����
	//���������õģ�ֻ��Ϊ������ǰ��++�ͺ���++
}
*/

//��������
void test2()
{
	Date d1(2021, 2, 5);
	Date d2(2021, 2, 5);
	Date d3(2021, 2, 5);
	Date d4(2021, 2, 5);
	d1 -= 1;
	d2 -= 30;
	d3 -= 90;
	d4 -= 360;
	d1.play();	//year = 2021 month = 2 day = 4
	d2.play();	//year = 2021 month = 1 day = 6
	d3.play();	//year = 2020 month = 11 day = 7
	d4.play();	//year = 2020 month = 2 day = 11
	d3 = d4 - 30;
	d3.play();	//year = 2020 month = 1 day = 12
	d3 = --d4;
	d3.play();	//year = 2020 month = 2 day = 10
	d4.play();	//year = 2020 month = 2 day = 10
	d3 = d4--;
	d3.play();	//year = 2020 month = 2 day = 10
	d4.play();	//year = 2020 month = 2 day = 9
	//�����Լ�
	cout << d4 - d3 << endl;	//-1
	cout << d3 - d4 << endl;	//1
}

int main()
{
	//test1();	//�ӷ�����
	test2();
	return 0;
}