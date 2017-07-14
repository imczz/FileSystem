#include <fstream>

#include "FileSystem.h"


FileSystem::FileSystem()
{
	init();
}

FileSystem::FileSystem(string diskFile)
{
	init();
	this->diskFile = diskFile;
	
	ifstream file(diskFile, ios::in);

	if (file.is_open()) {
		IsInitalized = true;
		file.close();
		return;
	}
	else
	{
		int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;
		char * buffer = (char *)calloc(filesize, sizeof(char));
		if (buffer == NULL) return;						//分配内存空间失败
		ofstream file(diskFile, ios::out | ios::binary);
		if (file.is_open()) {
			file.write(buffer, filesize);					//操作成功
			IsInitalized = true;
			file.close();
		}
	}
	
}

int FileSystem::Initialize()
{
	if (IsInitalized) return 1;
	if (this->diskFile != "") 
	{
		Initialize(this->diskFile);
	}
	return 0;
}

int FileSystem::Initialize(string diskFile)
{
	if (IsInitalized) return 1;
	this->diskFile = diskFile;
	ifstream file(diskFile, ios::in);

	if (file.is_open()) {
		IsInitalized = true;
		file.close();
		return 1;
	}
	else
	{
		int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;
		char * buffer = (char *)calloc(filesize, sizeof(char));
		if (buffer == NULL) return 0;						//分配内存空间失败
		ofstream file(diskFile, ios::out | ios::binary);
		if (file.is_open()) {
			file.write(buffer, filesize);					//操作成功
			IsInitalized = true;
			file.close();
			return 1;
		}
	}
	return 0;
}

int FileSystem::WriteFileSystemDiskFile(string address)
{
	int result = 0;
	if (IsInitalized == false) return -1;				//文件系统未初始化

	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//分配内存空间失败
	for (int i = 0; i < 100; i++)
	{

	}
	ofstream file(address, ios::out | ios::binary );

	if (file.is_open()) {
		file.write(buffer, filesize);					//操作成功
		file.close();
		result = 1;
	}
	else
	{
		result =  -3;										//文件打开失败
	}
	free(buffer);
	return result;
}

int FileSystem::ReadFileSystemDiskFile(string address)
{
	int result = 0;
	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//分配内存空间失败
	ifstream file(address, ios::in | ios::binary);

	if (file.is_open()) {
		file.read(buffer, filesize);					//操作成功
		file.close();
		//char xyz = buffer[1];
		result = 1;
	}
	else
	{
		result = -3;										//文件打开失败
	}
	free(buffer);
	return result;
}

void FileSystem::init()
{
	blockSize = BLOCKSIZ;		//每块大小
	sysOpenFile = SYSOPENFILE;	//系统打开文件表最大项数
	dirNum = DIRNUM;			//每个目录所包含的最大目录项数（文件数）
	dirSize = DIRSIZ;		//每个目录项名字部分所占字节数，另加i节点号2个字节
	pwdSize = PWDSIZ;			//口令字
	pwdNum = PWDNUM;			//最多可设32个口令登录
	noFile = NOFILE;			//每个用户最多可打开20个文件，即用户打开文件最大次数
	nAddr = NADDR;			//每个i节点最多指向10块，addr[0]~addr[9]
	nHino = NHINO;			//共128个Hash链表，提供索引i节点（必须为2的幂）
	userNum = USERNUM;		//最多允许10个用户登录
	dInodeSize = DINODESIZ;		//每个磁盘i节点所占字节
	dInodeBLK = DINODEBLK;		//所有磁盘i节点共占32个物理块
	fileBLK = FILEBLK;		//共有512个目录文件物理块
	nicFree = NICFREE;		//超级块中空闲块数组的最大块数
	nicInode = NICINOD;		//超级块中空闲节点的最大块数
	dInodeStart = DINODESTART;	//i节点起始地址
	dataStart = DATASTART;		//目录、文件区起始地址

	superBlock.dataBlockNumber = 512;
	superBlock.freeBlockNumber = 0;
	superBlock.freeBlocks[0] = 0;			//终止指针，指针终止
	superBlock.freeStackBlockNumber = 1;
	superBlock.freeInodeNumber = 512;
	for (int i = 0; i < superBlock.freeInodeNumber; i++)
	{
		superBlock.freeInodes[i] = i;
	}
	superBlock.iNodeBlockNumber = 32;
	superBlock.lastInode = superBlock.freeInodeNumber - 1;
	superBlock.modifyFlag = false;

	IsInitalized = false;
}

int FileSystem::balloc()
{
	

	return 1;
}

int FileSystem::bfree(int blockindex)
{
	if (!IsInitalized) return 0;
	if (superBlock.freeStackBlockNumber == nicFree)
	{
		//wtire 堆栈S  到块BlockNo中；
		//S[0] = 1；
		//S[1] = BlockNo
	}
	else
	{
		//S[0] ++;
		//S[S[0]] = BlockNo;
	}
	return 0;
}

int FileSystem::format()
{
	if (!IsInitalized) return 0;


	return 1;
}



int FileSystem::ReadABlock(int blockNumber, char * buffer)
{
	if (buffer == NULL) return 0;
	ifstream file(diskFile, ios::in | ios::binary);

	if (file.is_open()) {
		file.seekg(blockNumber * this->blockSize, ios::beg);
		file.read(buffer, this->blockSize);					//操作成功
		file.close();
		return 1;
	}
	return 0;
}

int FileSystem::WriteABlock(int blockNumber, char * buffer)
{
	if (this->diskFile == "") return 0;
	ofstream file(this->diskFile, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		file.seekp(blockNumber * this->blockSize, ios::beg);
		file.write(buffer, this->blockSize);					//操作成功
		file.close();
		return 1;
	}
	return 0;
}

//存储在磁盘块中的空闲块栈转化成内存中的便于程序使用的数组（栈）
int FileSystem::BufferToStack(char * buffer, short * blockStack)
{
	int pointer = 2;			//一个指针
	int number = 0;
	number = buffer[0];
	number <<= 8;
	short tempshort = buffer[1];
	if (tempshort < 0) tempshort = -tempshort;
	number |= tempshort;
	if (number != this->nicFree) return 0;
	for (int i = 0; i < number; i++)
	{
		blockStack[i] = buffer[pointer];
		blockStack[i] <<= 8;
		tempshort = buffer[pointer + 1];
		if (tempshort < 0) tempshort = -tempshort;
		blockStack[i] |= tempshort;
		pointer += 2;
	}
	return 0;
}

//内存中的便于程序使用的数组（栈）转化成存储在磁盘块中的空闲块栈
int FileSystem::StackToBuffer(short * blockStack, char * buffer)
{
	if (blockStack == NULL || buffer == NULL) return 0;
	int pointer = 2;		//位置指针
	int number = this->nicFree;
	int i;
	buffer[0] = number >> 8;
	buffer[1] = number;
	for (i = 0; i < number; i++)
	{
		buffer[pointer] = blockStack[i] >> 8;
		buffer[pointer + 1] = blockStack[i];
		pointer += 2;
	}
	for (; i < this->blockSize; i++)
	{
		buffer[i] = 0;					//剩余部分填充0
	}
	return 1;
}
