#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/miller_rabin.hpp>
//typedef long DateType;
typedef  boost::multiprecision::int1024_t DateType;
struct Key {
	//��Կ��e,n��  ��Կ(d,n)
	DateType _ekey;//E
	DateType _nkey;//N
	DateType _dkey;//D
};

class RSA{
public:
	RSA();
	
	bool isprime(DateType date);//�鿴�Ƿ�Ϊ����
	DateType GetGcd(DateType date1, DateType date2);//�����Լ��

	DateType GetPrime();//�õ�����
	DateType GetNkey(DateType prime1,DateType prime2);//�õ�N
	DateType GetFNkey(DateType prime1,DateType prime2);//��С��N��N�Ĺ�����
	DateType GetEkey(DateType fnkey);//�õ�E
	DateType GetDkey(DateType ekey, DateType& fnkey );//�õ�N
	void exgcd(DateType a, DateType b, DateType* x, DateType* y);//��ȡx

	Key getkeys();//��ȡ��Կ����Կ
	DateType ecrypt(DateType date,DateType ekey,DateType nkey);//���ܹ���
	DateType decrypt(DateType date, DateType dkey, DateType nkey);//���ܹ���

	void ecrypt(const char* filename, const char* fileout);//���ܹ���
	void decrypt(const char* filename, const char* fileout);//���ܹ���
private:
	Key _key;
};