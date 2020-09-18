#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/miller_rabin.hpp>
//typedef long DateType;
typedef  boost::multiprecision::int1024_t DateType;
struct Key {
	//公钥（e,n）  秘钥(d,n)
	DateType _ekey;//E
	DateType _nkey;//N
	DateType _dkey;//D
};

class RSA{
public:
	RSA();
	
	bool isprime(DateType date);//查看是否为素数
	DateType GetGcd(DateType date1, DateType date2);//求最大公约数

	DateType GetPrime();//得到素数
	DateType GetNkey(DateType prime1,DateType prime2);//得到N
	DateType GetFNkey(DateType prime1,DateType prime2);//求小于N的N的公质数
	DateType GetEkey(DateType fnkey);//得到E
	DateType GetDkey(DateType ekey, DateType& fnkey );//得到N
	void exgcd(DateType a, DateType b, DateType* x, DateType* y);//获取x

	Key getkeys();//获取公钥，秘钥
	DateType ecrypt(DateType date,DateType ekey,DateType nkey);//加密过程
	DateType decrypt(DateType date, DateType dkey, DateType nkey);//解密过程

	void ecrypt(const char* filename, const char* fileout);//加密过程
	void decrypt(const char* filename, const char* fileout);//解密过程
private:
	Key _key;
};