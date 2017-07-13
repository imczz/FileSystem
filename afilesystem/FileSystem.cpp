#include <fstream>

#include "FileSystem.h"


FileSystem::FileSystem()
{
	IsInitalized = false;
	init();
}

int FileSystem::WriteFileSystemDiskFile(string address)
{
	int result = 0;
	if (IsInitalized == false) return -1;				//文件系统未初始化

	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//分配内存空间失败
	buffer[1] = 'D';
	buffer[2] = 'K';
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
		char xyz = buffer[1];
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
	IsInitalized = true;
}
