#include "BitOperate.h"



int BitOperate::getBit(char bitArray, int index)
{
	if (index >= 0 && index < 8)
	{
		char mask = 1;
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
		char mask = 1;
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

BitOperate::BitOperate()
{
}


BitOperate::~BitOperate()
{
}
