#include <iostream>

using namespace std;

class Date
{
public:
	Date(int y = 1, int m = 1, int d = 1)
	{
		//判断日期是否有效
		if (y <= 0 || m <= 0 || m > 12 || d <= 0 || d > getDay(y,m))
		{
			//日期无效
			_y = 1;
			_m = 1;
			_d = 1;
			cout << "日期无效，设为默认值1-1-1" << endl;
		}
		else
		{
			//日期有效
			_y = y;
			_m = m;
			_d = d;
		}
	} 

	int getDay(int y, int m)
	{
		static int days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = days[m];
		//如果是2月且为闰年，2月天数加1
		if (m == 2 && (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0))
			day += 1;
		return day;
	}

	//运算符重载
	//日期运算
	//Date += int	日期 += 天数
	Date& operator+=(int day)
	{
		//判断天数是否为负数	
		if (day < 0)
			return *this -= -day;	//整个过程没有发生拷贝，效率很高
		//相加天数
		_d += day;
		//判断天数是否溢出
		while (_d > getDay(_y, _m))
		{
			//减去当月的天数
			_d -= getDay(_y, _m);
			//月份进位
			++_m;
			//判断月份是否溢出
			if (_m == 13)
			{
				//年份进位
				_y++;
				//下一年的1月份
				_m = 1;
			}
		}
		return *this;	//返回相加之后的结果
	}

	//Date + int
	//加法：返回相加之后的结果，操作数不能改变
	Date operator+(int day)
	{
		Date res = *this;
		return res += day;		//返回结果发生了值拷贝
	}

	//++Date	前置++
	Date& operator++()
	{
		return *this += 1;
	}

	//Date++	后置++
	Date operator++(int)	//占位符	//参数是无用的，只是为了区分前置++和后置++
	{
		Date res = *this;
		*this += 1;
		return res;		//值返回,发生了值拷贝
	}
	
	Date& operator-=(int day)
	{
		//判断天数是否为负数
		if (day < 0)
			return *this += -day;	//整个过程没有发生拷贝，效率很高
		_d -= day;
		while (_d <= 0)
		{
			//用上个月的天数回补
			_m--;
			//判断月份是否溢出，要注意先后顺序
			if (_m == 0)
			{
				//回退到上一个月的12月份
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

	//日期相减：Date - Date
	int  operator-(const Date& d)
	{
		//计算比较小的日期经过多少次自加的运算，可以和比较大的日期相同
		//自加的次数就是相差的次数
		Date max = *this;
		Date min = d;
		int flag = 1;		//*this大，是正值
		if (max < min)
		{
			min = *this;
			max = d;
			flag = -1;		//d大，是负值
		}
		int day = 0;
		while (min < max)
		{
			++min;
			++day;
		}
		return flag * day;
	}

	//输出年月日
	void play()
	{
		cout << "year = " << _y << " month = " << _m << " day = " << _d << endl;
	}

private:
	int _y;		//年
	int _m;		//月
	int _d;		//日
};

/* 
//加法操作
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
	d4.play();	//不发生改变	year = 2022 month = 1 day = 30
	++d3;
	d3.play();	//year = 2022 month = 5 day = 1
	Date d5 = d3++;
	d3.play();	//year = 2022 month = 5 day = 2
	d5.play();	//year = 2022 month = 5 day = 1
	//后置++
	//d5 = d4++10;	//error，编译器无法识别
	//d5 = d4.operator++(10);	//ok,这个是可以的，因为参数里面有内容表示后置，没内容表示前置，简写可以直接识别出来
	//参数是无用的，只是为了区分前置++和后置++
}
*/

//减法操作
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
	//日期自减
	cout << d4 - d3 << endl;	//-1
	cout << d3 - d4 << endl;	//1
}

int main()
{
	//test1();	//加法操作
	test2();
	return 0;
}