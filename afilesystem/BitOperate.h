#pragma once

#include <iostream>

using namespace std;

class BitOperate
{
public:
	int To9Char(int number, char * result)
	{
		if (number < 0 || number >= 512 || result == NULL) return 0;
		int i;
		result[1] = number;
		result[0] = number >> 8;
	}

	//获取bitArray的index位置（0-7）的位
	static int getBit(char bitArray, int index);

	//设置bitArray的index位置（0-7）的位为0还是1
	static char setBit(char bitArray, int index, int number);

	int bitCopy(char * target, int tBitStart, char * source, int sBitStart, int bitLength)
	{

	}

	BitOperate();
	~BitOperate();
};

