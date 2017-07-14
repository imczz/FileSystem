#pragma once

#include <iostream>

using namespace std;

class BitOperate
{
public:
	int To9Char(short number, char * result)
	{
		if (number < 0 || number >= 512 || result == NULL) return 0;
		int i;
		result[1] = number;
		result[0] = number >> 8;
	}

	//��ȡbitArray��indexλ�ã�0-7����λ
	static int getBit(char bitArray, int index);

	//����bitArray��indexλ�ã�0-7����λΪ0����1
	static char setBit(char bitArray, int index, int number);

	//��source�ĵ�sBitStartλ��>=0����ʼ������bitLengthλ��target�Ĵӵ�tBitStartλ��>=0����ʼ�ĵط�
	static int bitCopy(char * target, int tBitStart, char * source, int sBitStart, int bitLength);

	//���һ���ֽڵ�8λ
	static void outputBitArray(char ch);
	
	//����ַ������ÿһλ
	static void outputBitArrays(char * ch, int number);


	BitOperate();
	~BitOperate();
};

