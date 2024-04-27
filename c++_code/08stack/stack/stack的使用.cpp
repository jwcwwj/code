#include <iostream>
#include <stack>

using namespace std;

void test()
{
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	cout << "��ջǰ��size : " << st.size() << endl;

	while (!st.empty())
	{
		cout << st.top() << " ";  //4 3 2 1
		st.pop();
	}
	cout << endl;

	cout << "��ջ���size : " << st.size() << endl;
}

int main()
{
	//test();
	stack<int> st;
	cout << st.top() << endl;
	return 0;
}