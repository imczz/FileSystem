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

	//获取bitArray的index位置（0-7）的位
	static int getBit(char bitArray, int index);

	//设置bitArray的index位置（0-7）的位为0还是1
	static char setBit(char bitArray, int index, int number);

	//从source的第sBitStart位（>=0）开始，复制bitLength位到target的从第tBitStart位（>=0）开始的地方
	static int bitCopy(char * target, int tBitStart, char * source, int sBitStart, int bitLength);

	//输出一个字节的8位
	static void outputBitArray(char ch);
	
	//输出字符数组的每一位
	static void outputBitArrays(char * ch, int number);


	BitOperate();
	~BitOperate();
};

