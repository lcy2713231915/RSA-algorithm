#pragma once
#include<iostream>
class BigInt {
public:
	BigInt();
	//BigInt(int number);
	BigInt(const std::string& number);
	BigInt operator+(BigInt& number);
	BigInt operator-(BigInt& number);
	BigInt operator*(BigInt& number);
	BigInt operator/(BigInt& number);
	BigInt operator%(BigInt& number);
	friend std::ostream& operator<<(std::ostream& _cout,BigInt& number);
private:
	bool IsLBigR(std::string& left, std::string& right);
	void BigRight(std::string& num1, std::string& num2);
	std::string Add(std::string& num1, std::string& num2);
	std::string Erase(std::string& num1, std::string& num2);
	std::string Mul(std::string& num1, std::string& num2);
	std::pair<std::string, std::string> Div(std::string& divdend, std::string& divisor);
	std::string _num;
};