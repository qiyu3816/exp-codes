#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

class Big_int {
private:
	
public:
    string str_va;
	void Change(const Big_int& va)
	{
		str_va = va.str_va;
	}
	Big_int();
	Big_int(string str):str_va(str){}
	friend Big_int operator-(const Big_int& va0, const Big_int& va1);
	friend Big_int operator+(const Big_int& va0, const Big_int& va1);
	friend Big_int operator*(const Big_int& va0, const Big_int& va1);
	friend Big_int operator/(const Big_int& va0, const Big_int& va1);
	friend Big_int operator%(const Big_int& va0, const Big_int& va1);
	friend void operator++(Big_int& va);
	Big_int& operator=(const Big_int& va);
	friend ostream& operator<<(ostream& os, const Big_int& t);
};

void operator++(Big_int& va)//重载前置++
{
	va = va + Big_int("1");
}

bool Bigger(string& v0, string& v1)//无符号大数比较
{
	if (v0.length() > v1.length())
		return true;
	if (v0.length() < v1.length())
		return false;
	if (v0.length() == v1.length())
	{
		if (v0 > v1)
			return true;
		return false;
	}
}

Big_int& Big_int::operator=(const Big_int& va)
{
	Change(va);
	return(*this);
}

Big_int operator+(const Big_int& va0, const Big_int& va1)//加法
{
	//按位遍历字符串，逐位相加，满10则取模10，并且flag置True
	string result("");
	int va0_Len = va0.str_va.length() - 1;
	int va1_Len = va1.str_va.length() - 1;
	bool isMinus = false;
	if (va0.str_va[0] == '-' && va1.str_va[0] != '-')//负数加正数
	{
		Big_int vd=va0.str_va.substr(1, va0_Len);
		Big_int result = va1 - vd;
		return result;
	}
	if (va0.str_va[0] != '-' && va1.str_va[0] == '-')//正数加负数
	{
		Big_int vd = va1.str_va.substr(1, va1_Len);
		Big_int result = va0 - vd;
		return result;
	}
	if (va0.str_va[0] == '-' && va1.str_va[0] == '-')//负数加负数
	{
		isMinus = true;
	}
	//正数加正数
	int i = va0_Len;
	int j = va1_Len;
	int flag = false;//进位标志
	for ( ; i >= 0 || j >= 0; i--, j--)
	{
		int t = 0;
		if (i >= 0 && j >= 0)
			t = va0.str_va[i] - '0' + va1.str_va[j] - '0';
        else if (i >= 0)//某一大数位数更长，仍然继续加
			t = va0.str_va[i] - '0';
        else if (j >= 0)
			t = va1.str_va[j] - '0';

		if (flag)
		{
			t += 1;
			flag = false;
		}
		if (t >= 10)
		{
			t %= 10;
			flag = true;
		}
		result.push_back(t + '0');
	}
	if (flag)
	{
		result.push_back(1 + '0');
	}
	reverse(result.begin(), result.end());//result是逆序存储的，输出时要反过来
	if (isMinus)
		return '-' + result.substr(1);
	return result;
}

Big_int operator-(const Big_int& va0, const Big_int& va1)//减法
{
	string result("");
	string leftNum = va0.str_va;
	string rightNum = va1.str_va;

	int va0_Len = va0.str_va.length()-1;
	int va1_Len = va1.str_va.length()-1;

	bool isMinus = false; //结果负标志

	if (va0.str_va == va1.str_va)//两数相等
		return string("0");
	if (va0.str_va[0] == '-' && va1.str_va[0] != '-')//负数减正数
	{
		Big_int vd = va0.str_va.substr(1, va0_Len);
		result = (vd + va1).str_va;
		return '-' + result;
	}
	if (va0.str_va[0] != '-' && va1.str_va[0] == '-')//正数减负数
	{
		Big_int vd = va1.str_va.substr(1, va1_Len);
		result = (va0 + vd).str_va;
		return result;
	}
	if (va0.str_va[0] == '-' && va1.str_va[0] == '-')//负数减负数
	{
		if (va0.str_va < va1.str_va)
		{
			isMinus = false;
			leftNum.erase(0, 1);
			rightNum.erase(0, 1);
			leftNum.swap(rightNum);
		}
		if (va0.str_va > va1.str_va)
		{
			isMinus = true;
			leftNum.erase(0, 1);
			rightNum.erase(0, 1);
		}
	}
	if (va0.str_va[0] != '-' && va1.str_va[0] != '-')//两个正数
	{
		if (leftNum.length() < rightNum.length())
		{
			leftNum.swap(rightNum);
			isMinus = true;
		}
		else if (leftNum.length() == rightNum.length())
		{
			if (leftNum < rightNum)
			{
				leftNum.swap(rightNum);
				isMinus = true;
			}
		}
	}

	bool flag = false; //借位标志位
	int i = leftNum.length() - 1;
	int j = rightNum.length() - 1;
	for (; i >= 0 && j >= 0; --i, --j)
	{
		int t = leftNum[i] - rightNum[j];
		if (flag)
		{
			t -= 1;
			flag = false;
		}
		if (t < 0)
		{
			t += 10;
			flag = true;
		}
		result.push_back(t + '0');
	}

	//被减数较大，继续减
	while (i >= 0)
	{
		int t = leftNum[i] - '0';
		if (flag)
		{
			t -= 1;
			flag = false;
		}
		if (t < 0)
		{
			t += 10;
			flag = true;
		}
		result.push_back(t + '0');
		--i;
	}

	if (isMinus)
	{
		result.push_back('-');
	}

	reverse(result.begin(), result.end());//反转输出

	int zeroCount = 0; //高位0的个数
	bool Minus = false;
	for (unsigned int i = 0; i < result.length(); i++)
	{
		if (isMinus) //若结果为负数需要跳过符号
		{
			isMinus = false;
			Minus = true;
			continue;
		}
		if (result[i] != '0')
			break;
		else if (result[i] == '0')
		{
			++zeroCount;
		}
	}

	if (Minus)//跳过后还是把负号归位
		return result.erase(1, zeroCount);
	return result.erase(0, zeroCount);
}

Big_int operator*(const Big_int& va0, const Big_int& va1)//整数乘法
{

	if (va0.str_va == "0" || va1.str_va == "0")
		return string("0");
	string leftNum;
	string rightNum;
	bool isMinus = false;//判断正负
	
	if (va0.str_va[0] == '-' && va1.str_va[0] == '-')//负负
	{
		leftNum = va0.str_va.substr(1);
		rightNum = va1.str_va.substr(1);
	}
	if (va0.str_va[0] != '-' && va1.str_va[0] == '-')//正负
	{
		leftNum = va0.str_va;
		rightNum = va1.str_va.substr(1);
		isMinus = true;
	}
	if (va0.str_va[0] == '-' && va1.str_va[0] != '-')//负正
	{
		leftNum = va0.str_va.substr(1);
		rightNum = va1.str_va;
		isMinus = true;
	}
	if (va0.str_va[0] != '-' && va1.str_va[0] != '-')//正正
	{
		leftNum = va0.str_va;
		rightNum = va1.str_va;
	}
	
	if (leftNum.length() < rightNum.length())
		leftNum.swap(rightNum);
	else if (leftNum.length() == rightNum.length())
	{
		if (leftNum < rightNum)
			leftNum.swap(rightNum);
	}

	int i = leftNum.length() - 1;
	int j = rightNum.length() - 1;

	int highBit = 0;//存储进位
	bool flag = false;//进位标志
	string str;

	int lessLen = rightNum.length() - 1;
	stack<string> NumStack; //存储每轮的结果的栈
	for (; j >= 0; --j) //遍历小数的各个位
	{
		for (; i >= 0; --i) //遍历大数
		{
			int ret = (leftNum[i] - '0') * (rightNum[j] - '0');
			if (flag)
			{
				ret += highBit; //若有进位，加上进位
				flag = false;
			}
			if (ret >= 10)//进位暂存于highBit
			{
				highBit = ret / 10;
				ret %= 10;
				flag = true;
			}
			str.push_back(ret + '0');
		}
		if (flag)//遍历结束后继续判断是否有进位
		{
			str.push_back(highBit + '0');
			flag = false;
		}
		
		reverse(str.begin(), str.end());//反转字符串
		
		for (int k = abs((int)(j - lessLen)); k != 0; --k)//在本轮结果后补0
		{
			str += '0';
		}
		
		NumStack.push(str);//本轮结果入栈

		highBit = 0;//置零
		i = leftNum.length() - 1;//归原
		str.clear();//清空容器
	}

	Big_int result("");
	Big_int left_k("");
	Big_int right_k("");
	while (!NumStack.empty())
	{
		if (rightNum.length() == 1)
		{
			result = NumStack.top();
			NumStack.pop();
			break;
		}
		if (result.str_va.length() != 0)
		{
			NumStack.push(result.str_va);
		}
		right_k = NumStack.top();
		NumStack.pop();
		left_k = NumStack.top();
		NumStack.pop();
		result = left_k + right_k;
	}
	if (isMinus)//结果为负则加上负号
		return '-' + result.str_va;
	return result.str_va;
}

Big_int operator/(const Big_int& va0, const Big_int& va1)//整数除法
{
	if (va0.str_va == "0")
		return string("0");
	if (va1.str_va == "0")
	{
		cout << "False.";
		exit;
	}
	string leftNum;
	string rightNum;
	bool isMinus = false;//判断正负

	if (va0.str_va[0] == '-' && va1.str_va[0] == '-')//负负
	{
		leftNum = va0.str_va.substr(1);
		rightNum = va1.str_va.substr(1);
	}
	if (va0.str_va[0] != '-' && va1.str_va[0] == '-')//正负
	{
		leftNum = va0.str_va;
		rightNum = va1.str_va.substr(1);
		isMinus = true;
	}
	if (va0.str_va[0] == '-' && va1.str_va[0] != '-')//负正
	{
		leftNum = va0.str_va.substr(1);
		rightNum = va1.str_va;
		isMinus = true;
	}
	if (va0.str_va[0] != '-' && va1.str_va[0] != '-')//正正
	{
		leftNum = va0.str_va;
		rightNum = va1.str_va;
	}

	if (leftNum.length() < rightNum.length())
		return string("0");
	else if (leftNum.length() == rightNum.length())
	{
		if (leftNum == rightNum)
		{
			if (isMinus)
				return "-" + string("1");
			return string("1");
		}
		if (leftNum < rightNum)
		{
			return string("0");
		}
	}

	int left_Len = leftNum.length(), right_Len = rightNum.length();
	int index = left_Len - right_Len; //得到基准值
	Big_int left_k(leftNum);
	Big_int right_k(rightNum);
	if (index == 0)
	{
		Big_int count("0");
		for (; left_k.str_va > string("0"); ++count)
		{
			left_k = left_k - right_k;
		}
		if (left_k.str_va == string("0"))
			return count.str_va;
		return (count - Big_int("1")).str_va;
	}
	stack<Big_int> NumStack; //存储结果的栈
	for (; index >= 0; index--)
	{
		int k = index;
		while (k > 0)
		{
			right_k.str_va += '0'; //给除数后添加 0 
			k--;
		}

		//除数大，返回
		if (Bigger(right_k.str_va , left_k.str_va) && right_k.str_va != left_k.str_va)
		{
			right_k.str_va.clear();
			right_k = rightNum;
			continue;
		}

		Big_int result = string("0");
		Big_int count = string("0");//存储每次够减的次数

		do
		{
			result = left_k - right_k;
			left_k.str_va = result.str_va;
			count = count + Big_int("1");
        } while (Bigger(result.str_va , right_k.str_va) &&
			left_k.str_va!=string("0"));//直到除数小，或左操作数为0，全部整除
		if (left_k.str_va == right_k.str_va)
		{
			count = count + Big_int("1");
			left_k = left_k - right_k;
		}

		k = index;
		while (k > 0)
		{
			//给够减的次数后添加 0，得出一轮结果
			count.str_va = count.str_va + "0";
			k--;
		}
		
		NumStack.push(count);//将结果入栈

		
		right_k.str_va.clear();//清空右操作数，进行下次运算
		right_k = va1;
	}
	
	if (NumStack.size() == 1)
	{
		if (isMinus)
			return '-' + NumStack.top().str_va;
		return NumStack.top().str_va;
	}
	//对栈的操作
	Big_int result("");
	Big_int left_t("");
	Big_int right_t("");
	while (!NumStack.empty())
	{
		if (result.str_va.length() != 0)
		{
			NumStack.push(result);
		}
		right_t = NumStack.top();
		NumStack.pop();
		left_t = NumStack.top();
		NumStack.pop();
		result = left_t + right_t;
	}
	if (isMinus)
		return '-' + result.str_va;
	return result.str_va;
}

Big_int operator%(const Big_int& va0, const Big_int& va1)//求模
{
	Big_int left_k = va0, right_k = va1;
	Big_int result = left_k - (left_k / right_k) * right_k;
	return result.str_va;
}

ostream & operator<<(ostream& os, const Big_int& t)//重载<<
{
	os << t.str_va;
	return os;
}

int main()
{
	string str_a, str_b;
	cin >> str_a;
	// cin >> str_b;
	// cout << endl;
	// Big_int va(str_a), vb(str_b);
	// Big_int	res_add = va + vb, res_mnu = va - vb, res_mul = va * vb, res_div = va / vb, res_mod = va % vb;
	// ++va;
	// cout << "+ " << res_add << endl;
	// cout << "- " << res_mnu << endl;
	// cout << "* " << res_mul << endl;
	// cout << "/ " << res_div << endl;
	// cout << "% " << res_mod << endl;
	// cout << "++ " << va;
    if(str_a == "0" || str_a == "1" || str_a == "2")
    {
        cout << "1";
        return 0;
    }
    Big_int a(str_a), b("2");
    Big_int c("2");
    while(Bigger(a.str_va, b.str_va))
    {
        b = b * c;
        if(b.str_va == a.str_va)
        {
            cout << "1";
            return 0;
        }
    }
    cout << "0";
	return 0;
}