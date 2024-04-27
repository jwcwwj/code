#include <iostream>
#include <vector>

using namespace std;

//λͼ��ֻ�ܴ�����ֵ���͵�����
//ʹ�ó�������Ų��ظ����ݵļ���Ϣ������Ҫ������ݱ���
//�ŵ㣺��ʡ�ռ䣬����Ч�ʸߣ����ҵ�ʱ�临�Ӷ���O(1)
class BitSet
{
public:
	//λͼ���ڴ��С�����ݷ�Χ�й�ϵ
	BitSet(size_t range)
		:_bit(range / 32 + 1)
	{}

	//�洢��Ϣ
	void set(size_t num)
	{
		//����λ��
		//1.��������λ�ã�/ 32
		int idx = num / 32;
		//2.����bitλ�ã� % 32
		int bitIdx = num % 32;
		//�Ѷ�Ӧ��bitλ����Ϊ1
		//��λ������Ѷ�Ӧ��bitλ��Ϊ1
		_bit[idx] |= (1 << bitIdx);
	}

	//������Ϣ
	bool test(size_t num)
	{
		int idx = num / 32;
		int bitIdx = num % 32;
		return (_bit[idx] >> bitIdx) & 1;
	}

	//ɾ����Ϣ
	void reset(size_t num)
	{
		int idx = num / 32;
		int bitIdx = num % 32;
		if(test(num))
			_bit[idx] &= ~(1 << bitIdx);
	}

private:
	vector<int> _bit;	//��������
};

void test()
{
	BitSet bit(512);
	bit.set(1);
	bit.set(512);
	bit.set(32);
	bit.set(64);
	bit.set(15);
	bit.set(47);
	//cout << bit._bit[0] << endl;
	//cout << bit._bit[16] << endl;
	//cout << bit.test(47) << endl;
	bit.reset(15);
	bit.reset(1);
}

int main()
{
	test();
	return 0;
}