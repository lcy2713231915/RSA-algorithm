#include <iostream>
#include<time.h>
#include<math.h>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>
#include<fstream>
#include<ostream>
#include "RSA.h"
#define NUMBER 256
//查看是否为素数
RSA::RSA(){getkeys();}
//bool RSA::isprime(DateType date) {
//	if (date < 1)
//		return false;
//	for (int i = 2; i <= sqrt(date); ++i) {
//		if (date % i == 0)
//			return false;
//	}
//	return true;
//}


bool RSA::isprime(DateType date) {
	boost::random::mt11213b gen(time(nullptr));
	
	if (miller_rabin_test(date, 25, gen)) {
		if (miller_rabin_test((date-1)/2, 25, gen))
			return true;
	}
	return false;
}


//求最大公约数  辗转相除法
DateType RSA::GetGcd(DateType date1, DateType date2) {
	DateType gcd = date2 % date1;
	while (gcd!=0) {
		date2 = date1;
		date1 = gcd;
		gcd = date2 % date1;
	}
	return date1;
}



//得到素数
DateType  RSA::GetPrime() {
	//随时间获取随机数
	boost::random::mt19937  gen(time(nullptr));
	boost::random::uniform_int_distribution<DateType> dist(0, DateType(1) << 256);
	DateType prime;
	while (1) {
		prime = dist(gen);
		if (RSA::isprime(prime))
			break;
	}
	return prime;
}

//得到N
DateType RSA::GetNkey(DateType prime1, DateType prime2) {
	return prime1 * prime2;
}

//求小于N的N的公质数
DateType RSA::GetFNkey(DateType prime1, DateType prime2) {
	return (prime1 - 1) * (prime2 - 1);
}

//得到E
DateType RSA::GetEkey(DateType fnkey) {
	boost::random::mt19937_64 gen(time(NULL));
	boost::random::uniform_int_distribution<DateType> dist(2, fnkey);
	DateType ekey;
	while (1) {
		ekey = dist(gen);
		if ( RSA::GetGcd(ekey, fnkey) == 1)
			break;
	}
	return ekey;
}

//得到D
DateType RSA::GetDkey(DateType ekey,DateType& fnkey) {
	DateType x, y;
	exgcd(ekey, fnkey, &x, &y);
	return (x%fnkey+fnkey)%fnkey;
}

void RSA::exgcd(DateType a, DateType b, DateType* x, DateType* y ) {
	if (b == 0)
	{
		*x = 1;
		*y = 0;
		return;
	}
     exgcd(b, a % b, x, y);
	//当前(a,b)对应的解可以通过(b,a%b)推导得出
	DateType* temp=y;
	*y = *x - (a / b) * (*y);
	*x = *temp;
}

//获取公钥，秘钥
Key RSA::getkeys() {

	DateType prime1,prime2;
	prime1 = RSA::GetPrime();
	prime2 = RSA::GetPrime();
	while (prime1 == prime2)
		prime2 = RSA::GetPrime();
	std::cout << prime1 << std::endl;
	std::cout << prime2 << std::endl;
	_key._nkey = RSA::GetNkey(prime1, prime2);
	std::cout << _key._nkey << std::endl;
	DateType fnkey = RSA::GetFNkey(prime1, prime2);
	std::cout <<fnkey << std::endl;
	_key._ekey = RSA::GetEkey(fnkey);
	std::cout << _key._ekey << std::endl;
	_key._dkey = RSA::GetDkey(_key._ekey, fnkey);
	std::cout << _key._dkey << std::endl;
	return _key;
}

//加密过程
DateType RSA::ecrypt(DateType date, DateType ekey, DateType nkey) {
	DateType password = 1;
	while (ekey != 0) {
		if ((ekey & 1) != 0)
			password = (password * date) % nkey;
		ekey >>= 1;
		date = (date * date) % nkey;
	}
	return password;
}

//解密过程
DateType RSA::decrypt(DateType date, DateType dkey, DateType nkey) {
	return ecrypt(date, dkey, nkey);
}


//加密过程
void RSA::ecrypt(const char* filename,const char* fileout) {
	std::ifstream fin(filename, std::ifstream::binary);//打开要读的文本
	std::ofstream fout(fileout, std::ifstream::binary);//打开要写入的文本

	//如果打不开报错
	if (!fin.is_open()) {
		perror("input file open failed!");
		return;
	}
	char* buffer = new char[NUMBER];
	DateType* bufferout = new DateType[NUMBER];
	while (!fin.eof()) {
		fin.read(buffer, NUMBER);
		int curNum = fin.gcount();//获取最近读取的字节
		for (int i = 0; i < curNum; ++i) {
			bufferout[i] = ecrypt((DateType)buffer[i], _key._ekey, _key._nkey);
		}
		fout.write((char*)bufferout,curNum*sizeof(DateType));
	}
	delete[] buffer;
	delete[] bufferout;
	fin.close();
	fout.close();
	
}

//解密过程
void RSA::decrypt(const char* filename, const char* fileout) {
	std::ifstream fin(filename, std::ifstream::binary);//打开要读的文本
	std::ofstream fout(fileout, std::ifstream::binary);//打开要写入的文本

	//如果打不开报错
	if (!fin.is_open()) {
		perror(" file open failed!");
		return;
	}
	DateType* buffer = new DateType[NUMBER];
	char* bufferout = new char[NUMBER];
	while (!fin.eof()) {
		fin.read((char*)buffer, NUMBER*sizeof(DateType));
		int Num = fin.gcount();//获取最近读取的字节
		 Num /= sizeof(DateType);
		for (int i = 0; i < Num; ++i) {
			bufferout[i] = (char)decrypt(buffer[i], _key._dkey, _key._nkey);
		}
		fout.write(bufferout, Num);
	}
	delete[] buffer;
	delete[] bufferout;
	fin.close();
	fout.close();
	
}