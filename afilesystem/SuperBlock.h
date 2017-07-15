#pragma once
struct SuperBlock
{
	//i节点块数
	int iNodeBlockNumber;

	//空闲i节点数
	int freeInodeNumber;
	
	//空闲i节点指针数组，存放空闲i节点号的一个数组
	int freeInodes[512];

	//铭记i节点
	int lastInode;

	//数据块块数
	int dataBlockNumber;

	//空闲数据块块数
	int freeBlockNumber;

	//栈元素个数
	int freeStackBlockNumber;

	//空闲块指针数组
	short freeBlocks[50];

	//超级块修改标志
	bool modifyFlag;

};

