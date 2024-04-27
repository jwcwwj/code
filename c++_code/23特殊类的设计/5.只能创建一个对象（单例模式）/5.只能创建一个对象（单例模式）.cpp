#include <iostream>
#include <thread>
#include <mutex> 

using namespace std;

//����ģʽ
//1.��
//2.����ֻ�ܱ�����һ��
class singleton
{
public:
	//���еķ�����ȡ����
	static singleton* getSingletion()
	{
		//��ȡ�Ѵ��ڶ���ĵ�ַ
		return &_singleton;	
	}

private:
	//���캯��˽��
	singleton()
	{}

	//����һ����ľ�̬��Ա
	static singleton _singleton;		//��̬��Ա����ھ�̬������

	//ֻ��һ��
	//��ֹ����
	singleton(const singleton&) = delete;

};

//��̬��Ա�����ʼ��
singleton singleton::_singleton;

//singleton::getSingletion();
//singleton g;

void test()
{
	cout << sizeof(singleton) << endl;
	//singleton::_singleton;
	singleton* ptr = singleton::getSingletion();
} 


//��������һ��ʹ�õ�ʱ�򴴽�����
mutex mtx;	//ȫ����

class singleton2
{
public:
	//���еķ�����ȡ����
	static singleton2* getSingleton()	//static����ֻ�ܵ���static����
	{
		//��һ�μ�飺���Ч��
		if (_sin == nullptr)
		{
			mtx.lock();
			//��һ�μ�飺�̰߳�ȫ
			if (_sin == nullptr)
			{
				_sin = new singleton2;
				cout << _sin << endl;
				//��һ��ʹ�ô���
				//return new singleton2;	
				//������Ҫ�޸Ķ�������ݣ��񺺲���Ҫ��������Ҫ�����������̣߳�����������̰߳�ȫ�����⣩
			}
			mtx.unlock();
		}
		return _sin;		//���ǵ�һ�δ���ֱ�ӷ���
	}

private:
	//���캯��˽��
	singleton2()
	{}

	//��ֹ����
	singleton2(const singleton2&) = delete;

	//ָ���Ա
	static singleton2* _sin;		//���캯��֮ǰ���ã���ʼֵΪnullptr
	//�������ʱ��ϵͳ�Զ������������������Ӷ��ͷŵ�������
};

singleton2* singleton2::_sin = nullptr;

void fun2(int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << singleton2::getSingleton() << endl;	//�����ַ
	}
}

void test2()
{
	//��һ�δ���
	//singleton2* ptr = singleton2::getSingleton();
	//�����ֱ�ӷ��ض��󣬲���������
	//ptr = singleton2::getSingleton();

	//���߳�
	int n;
	cin >> n;
	thread t1(fun2, n);
	thread t2(fun2, n);
	t1.join();
	t2.join();
}

int main()
{
	//test();
	test2();
	return 0;
}