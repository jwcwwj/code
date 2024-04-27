#include <iostream>
#include <vector>
#include <string>

using namespace std;

//λͼ
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
		if (test(num))
			_bit[idx] &= ~(1 << bitIdx);
	}

private:
	vector<int> _bit;	//��������
};

//m����Ҫ��bitλ��С
//n��Ԫ�ظ���
//k����ϣ��������
//k = m / n * ln2
//m = k * n * 1.4

//��¡������	�������������жϴ��ڽ����һ����ȷ		
//һ�㲻�ṩɾ��������ɾ�������������ɾ
//ʹ�ó�������Ÿ������ݵļ���Ϣ
//ʱ�临�Ӷȣ�O(k)
template <class T,class Hash1, class Hash2, class Hash3>
class BloomFilter
{
public:
	BloomFilter(size_t num)
		: _bit(5 * num)
		, _bitCount(5 * num)
		,_size(0)
	{}

	//�洢��Ϣ��ʹ�ö��bitλ�洢��Ϣ
	void set(const T& val)
	{
		Hash1 h1;
		Hash2 h2;
		Hash3 h3;
		
		int idx1 = h1(val) % _bitCount;		//��val������ϣ����ת�������ֿ��ܻ�ܴ�
		int idx2 = h2(val) % _bitCount;
		int idx3 = h3(val) % _bitCount;
		
		_bit.set(idx1);		//������idx1��bitλ����Ϊ1
		_bit.set(idx2);
		_bit.set(idx3);

		_size++;
	}

	//����
	bool test(const T& val)
	{
		Hash1 h1;
		Hash2 h2;
		Hash3 h3;
		
		int idx1 = h1(val) % _bitCount;		//��val������ϣ����ת�������ֿ��ܻ�ܴ�
		int idx2 = h2(val) % _bitCount;
		int idx3 = h3(val) % _bitCount;
		
		if (!_bit.test(idx1))
			return false;
		if (!_bit.test(idx2))
			return false;
		if (!_bit.test(idx3))
			return false;

		//�����ж�һ�������ڣ������ܱ�֤һ������
		return true;	//���������´��ڣ���Ҳ���ܲ����ڣ������һ�������Ǵ���ģ�
	}
	
	//��¡������һ��û��ɾ���Ľӿ�
	//ԭ����Ϊ��ͬԪ��ռ���bitλ��ɾ�������Ԫ�ص�bitλ�����Ǳ��Ԫ�ص�bitλ��
	//�����˱��Ԫ�ء�
	//����취�����۱Ƚϴ�
	//��ÿ��bitλ��һ���ۼӼ�������������ݰ������bitλ��
	//�ж������ݰ������bitλ�����bitλ�ļ��������Ƕ���
	//�ۼӼ����������⣺Ҫ��2λbitλ�Ļ����ۼӼ��������ֵ��3��Ҫ�Ǽӵ�4�ͻ�ص�0�����ۼӼ��������/�������⣩
	//��ǰ��֪���ж�ɱ�Ѹ����ݰ������bitλ���Ͳ�֪��Ҫ�����Ŀռ䡣����32λҲ���������

private:
	BitSet _bit;	//��װλͼ
	size_t _bitCount;	//bitλ�ĸ���
	size_t _size;
};

//��ϣ����
struct HashFun1
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
			hash = hash * 131 + ch;
		return hash;
	} 
};

struct HashFun2
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
			hash = hash * 1313131 + ch;
		return hash;
	}
};

struct HashFun3
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
			hash = hash * 65599 + ch;
		return hash;
	}
};

void test()
{
	BloomFilter<string, HashFun1, HashFun2, HashFun3> bf(10);		
	//���10�����ݣ�50��bitλ

	string str1 = "https://bbs.hupu.com/clippers-postdate";
	string str2 = "https://my.hupu.com/155535087800136";
	string str3 = "https://bbs.hupu.com/61330352.html";
	string str4 = "https://bbs.hupu.com/61330353.html";

	bf.set(str1);
	bf.set(str2);
	bf.set(str3);

	cout << bf.test(str1) << endl;
	cout << bf.test(str2) << endl;
	cout << bf.test(str3) << endl;
	cout << bf.test(str4) << endl;

	//λͼֻ�ܴ�����ֵ���͵����ݣ���¡���������Դ�������ֵ���͵�����
	//��¡������ʵ�֣�λͼ + ��ϣ����
}

int main()
{
	test();
	return 0;
}