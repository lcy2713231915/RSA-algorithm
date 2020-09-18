#include "bigint.h"
#include<algorithm>
//BigInt::BigInt(int number) {
//}

BigInt::BigInt(const std::string& number):_num(number) {}
BigInt BigInt::operator+(BigInt& number) {
	std::string s = Add(_num, number._num);
	BigInt ob(s);
	return ob;
}
BigInt BigInt::operator-(BigInt& number) {
	std::string s = Erase(_num, number._num);
	BigInt ob(s);
	return ob;
}
BigInt BigInt::operator*(BigInt& number) {
	std::string s = Mul(_num, number._num);
	BigInt ob(s);
	return ob;
}
BigInt BigInt::operator/(BigInt& number) {
	std::string s = Div(_num, number._num).first;
	BigInt ob(s);
	return ob;
}
BigInt BigInt::operator%(BigInt& number) {
	std::string s = Div(_num, number._num).second;
	BigInt ob(s);
	return ob;
}
std::ostream& operator<<(std::ostream& _cout, BigInt& number) {
	std::cout << number._num << std::endl;
	return _cout;
}

//�ж�����Ƿ���ұߴ�,���Ҳ����true
bool BigInt::IsLBigR(std::string& left, std::string& right) {
	int len1 = left.size();
	int len2 = right.size();
	if (len1 < len2) 
		return false;
	if(len1 > len2)
		return true;
	for (int i = 0; i < len1; ++i) {
		if (left[i] < right[i])
			return false;
		if (left[i] > right[i])
			return true;
	}
	return true;
}

void BigInt::BigRight(std::string& num1, std::string& num2) {
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 > len2) {
		int  temp = len2;
		len2 = len1;
		len1 = temp;
		swap(num1, num2);
	}
}

std::string BigInt::Add(std::string& num1, std::string& num2) {
	std::string ret;
	int step = 0;//��һλ�Ƿ��λ�ı�־
	int num;// ��λ����
	int len1 = num1.size();
	int len2 = num2.size();
	while (len1 != 0 || len2!=0) {
		num = step;
		if (len1 != 0)
			num += num1[--len1] - '0';
		if (len2 != 0)
			num += num2[--len2] - '0';
		step = num / 10;
		num %= 10;
		ret += (num + '0');
	}
	if (step == 1)
		ret += '1';
	std::string s(ret.rbegin(), ret.rend());
	return  s;
}

std::string BigInt::Erase(std::string& num1, std::string& num2) {
	std::string ret;
	int step = 0;//��һλ�Ƿ��λ�ı�־
	int num;// ��λ����
	int len1 = num1.size();
	int len2 = num2.size();
	while (len1 != 0 || len2 != 0) {
		num = (num1[--len1] - '0') - step;
		if (len2 != 0)
			num -= (num2[--len2] - '0');
		if (num < 0) {
			num += 10;
			step = 1;
		}
		else
			step = 0;
		ret += (num + '0');
	}
	for (int i = ret.size()-1; i >=0; --i) {
		if (ret[i] != '0' || i == 0)
			break;
		ret.pop_back();
	}
	std::string s(ret.rbegin(), ret.rend());

	return  s;
}

std::string BigInt::Mul(std::string& num1, std::string& num2) {
	std::string ret;
	BigRight(num1, num2);
	int len1 = num1.size();
	int len2 = num2.size();
	for (int i = 0; i < len2; i++) {
		int num = num2[len2-i-1] - '0';//С���ı�λ�������γ˷���һλ��
		int t_len1 = len1;
		std::string ret_n(len1+i,'0');
		int step = 0;//��һ�εĽ�λ
		while (num!=0&&t_len1 !=0) {
			int t_num = num * (num1[--t_len1] - '0') + step;
			step = t_num / 10;
			t_num %= 10;
			ret_n[t_len1] = t_num + '0';
		}
		if (step != 0)
			ret_n.insert(ret_n.begin(), step+'0');
		ret = Add(ret, ret_n);
	}

	return ret;
}
//����
std::pair<std::string,std::string> BigInt::Div(std::string& divdend, std::string& divisor){
	std::pair<std::string, std::string> ob;
	if (!IsLBigR(divdend,divisor)) {
		ob.first += '0';
		ob.second = divdend;
		return ob;
	}
	std::string quotient="0";//��
	std::string remainder(divdend);//����
	int len1 = remainder.size();
	int len2 = divisor.size();
	int j = len1 - len2;//Ҫִ�еĴ���
	for (int i = 0; i < j; i++)
		divisor += '0';
	while (j >= 0) {
		int i = 0;
		while (IsLBigR(remainder, divisor)) {
			i++;
			remainder = Erase(remainder, divisor);
		}
		if (quotient[0] == '0')
			quotient[0] = i + '0';
		else
			quotient += (i + '0');
		if(j!=0)
		divisor.pop_back();
		--j;
	}
	ob.first = quotient;
	ob.second = remainder;
	return ob;
}