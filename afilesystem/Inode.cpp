#include <cstdlib>

#include "Inode.h"
#include "BitOperate.h"

Inode::Inode()
{
	this->init(false, 0, 0, NULL, '\0', '\0', 0, 0 , NULL);
}

Inode::Inode(bool state, int fileType, int blockNumber, bool * permissions, char userName, char userGroup, long fileSize, long createTime, short * blocksIndex)
{
	this->init(state, fileType, blockNumber, permissions, userName, userGroup, fileSize, createTime, blocksIndex);
}

Inode::Inode(const Inode & inode)
{
	int i;
	this->state = inode.state;
	this->fileType = inode.fileType;
	this->blockNumber = inode.blockNumber;
	if (inode.permissions != NULL)
	{
		for (i = 0; i < 9; i++)
		{
			this->permissions[i] = inode.permissions[i];
		}
	}
	else
	{
		for (i = 0; i < 9; i++)
		{
			this->permissions[i] = false;
		}
	}
	this->userName = inode.userName;
	this->userGroup = inode.userGroup;
	this->fileSize = inode.fileSize;
	this->createTime = inode.createTime;
	if (inode.blocksIndex != NULL)
	{
		for (i = 0; i < 10; i++)
		{
			this->blocksIndex[i] = inode.blocksIndex[i];
		}
	}
	else
	{
		for (i = 0; i < 10; i++)
		{
			this->blocksIndex[i] = -1;
		}
	}
}

void Inode::init(bool state, int fileType, int blockNumber, bool * permissions, char userName, char userGroup, long fileSize, long createTime, short * blocksIndex)
{
	int i;
	this->state = state;
	this->fileType = fileType;
	this->blockNumber = blockNumber;
	if (permissions != NULL)
	{
		for (i = 0; i < 9; i++)
		{
			this->permissions[i] = permissions[i];
		}
	}
	else
	{
		for (i = 0; i < 9; i++)
		{
			this->permissions[i] = false;
		}
	}
	this->userName = userName;
	this->userGroup = userGroup;
	this->fileSize = fileSize;
	this->createTime = createTime;
	if (blocksIndex != NULL)
	{
		for (i = 0; i < 10; i++)
		{
			this->blocksIndex[i] = blocksIndex[i];
		}
	}
	else
	{
		for (i = 0; i < 10; i++)
		{
			this->blocksIndex[i] = -1;
		}
	}
}

int Inode::LoadInodeInBuffer(char * buffer)
{
	if (buffer == NULL) return -1;
	int i;
	int fileType = BitOperate::getBit(buffer[0], 1);
	fileType <<= 1;
	fileType |= BitOperate::getBit(buffer[0], 2);

	int blockNumber = 0;
	for (i = 0; i < 4; i++)
	{
		blockNumber <<= 1;
		blockNumber |= BitOperate::getBit(buffer[0], i + 3);
	}

	bool permissions[9];
	permissions[0] = BitOperate::getBit(buffer[0], 7) == 0 ? false : true;
	for (i = 1; i < 9; i++)
	{
		permissions[i] = BitOperate::getBit(buffer[i], 7) == 0 ? false : true;
	}

	char userName[1];
	BitOperate::bitCopy(userName, 0, buffer, 15, 8);

	char userGroup[1];
	BitOperate::bitCopy(userName, 0, buffer, 23, 8);

	char filesize[8];
	long size = 0;
	BitOperate::bitCopy(filesize, 0, buffer + 3, 0, 64);
	for (i = 0; i < 8; i++)
	{
		size << 8;
		size |= filesize[i];
	}

	char createtime[8];
	long cTime = 0;
	BitOperate::bitCopy(createtime, 0, buffer + 3, 0, 64);
	for (i = 0; i < 8; i++)
	{
		cTime << 8;
		cTime |= createtime[i];
	}

	char indexList[12];
	char index[2];
	short indexAddresss[10] = { 0 };
	BitOperate::bitCopy(indexList, 0, buffer + 20, 0, 90);
	for (i = 0; i < 10; i++)
	{
		index[0] = 0;
		BitOperate::bitCopy(index, 7, indexList, 0 + i * 9, 9);
		indexAddresss[i] |= index[0];
		indexAddresss[i] <<= 8;
		indexAddresss[i] |= index[1];
	}

	init(BitOperate::getBit(buffer[0], 0) == 0 ? false : true,
		fileType,
		blockNumber,
		permissions,
		userName[0],
		userGroup[0],
		size,
		cTime,
		indexAddresss
	);

	return 1;
}

int Inode::CreateBufferFromInode(Inode & inode, char * buffer)
{
	int i;
	if (buffer == NULL) return -1;
	buffer[0] = BitOperate::setBit(buffer[0], 0, inode.state == false ? 0 : 1);

	char type[1];
	type[0] = inode.fileType;
	BitOperate::bitCopy(buffer, 1, type, 6, 2);

	char blockNumber[1];
	blockNumber[0] = inode.blockNumber;
	BitOperate::bitCopy(buffer, 3, type, 4, 4);

	buffer[0] = BitOperate::setBit(buffer[0], 7, inode.permissions[0] == false ? 0 : 1);

	for (i = 0; i < 8; i++)
	{
		buffer[1] = BitOperate::setBit(buffer[1], i, inode.permissions[i + 1] == false ? 0 : 1);
	}

	buffer[2] = inode.userName;
	buffer[3] = inode.userGroup;

	char fileSize[8];
	long size = inode.fileSize;
	for (i = 0; i < 8; i++)
	{
		fileSize[7 - i] = size;
		size >>= 8;
	}
	BitOperate::bitCopy(buffer + 4, 0, fileSize, 0, 64);

	char createTime[8];
	long cTime = inode.createTime;
	for (i = 0; i < 8; i++)
	{
		createTime[7 - i] = cTime;
		cTime >>= 8;
	}
	BitOperate::bitCopy(buffer + 12, 0, createTime, 0, 64);

	char indexList[12];
	char index[2];
	for (i = 0; i < 10; i++)
	{
		index[0] = inode.blocksIndex[i] >> 8;
		index[1] = inode.blocksIndex[i];
		BitOperate::bitCopy(indexList, 0 + i * 9, index, 7, 9);
	}
	indexList[11] &= 0xC0;
	BitOperate::bitCopy(buffer + 20, 0, indexList, 0, 96);
	
	return 1;
}



Inode::~Inode()
{
}
