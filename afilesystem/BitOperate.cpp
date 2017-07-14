#include "BitOperate.h"



int BitOperate::getBit(char bitArray, int index)
{
	if (index >= 0 && index < 8)
	{
		char mask = 1;				//����
		int i, result;
		for (i = 0; i < (7 - index); i++) mask <<= 1;
		bitArray &= mask;
		for (i = 0; i < (7 - index); i++) bitArray >>= 1;
		result = bitArray;
		if (result < 0) return 1;
		return result;
	}
	return -1;
}

char BitOperate::setBit(char bitArray, int index, int number)
{
	if (index >= 0 && index < 8)
	{
		int i;
		char mask = 1;				//����
		char ch = bitArray;
		for (i = 0; i < (7 - index); i++) mask <<= 1;
		if (number == 0)     //set 0
		{
			ch &= (~mask);
		}
		else                //set 1
		{
			ch |= mask;
		}
		return ch;
	}
}

//��source�ĵ�sBitStartλ��>=0����ʼ������bitLengthλ��target�Ĵӵ�tBitStartλ��>=0����ʼ�ĵط�
int BitOperate::bitCopy(char * target, int tBitStart, char * source, int sBitStart, int bitLength)
{
	int i, sp, tp, tbit;
	sp = sBitStart;
	tp = tBitStart;
	for (i = 0; i < bitLength; i++)
	{
		tbit = tp / 8;
		target[tbit] = setBit(target[tbit], tp % 8, getBit(source[sp / 8], sp % 8));
		tp++;
		sp++;
	}
	return 0;
}

void BitOperate::outputBitArray(char ch)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		cout << getBit(ch, i) << " ";
	}
	cout << endl;
}

void BitOperate::outputBitArrays(char * ch, int number)
{
	int i, j;
	for (i = 0; i < number; i++)
	{
		for (j = 0; j < 8; j++)
		{
			cout << getBit(ch[i], j) << " ";
		}
		cout << " ";
	}
	cout << endl;
}

BitOperate::BitOperate()
{
}


BitOperate::~BitOperate()
{
}
