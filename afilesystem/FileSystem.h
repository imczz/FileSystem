#pragma once

#define BLOCKSIZ 512
#define SYSOPENFILE 40
#define DIRNUM 128
#define DIRSIZ 14
#define PWDSIZ 12
#define PWDNUM 32
#define NOFILE 20
#define NADDR 10
#define NHINO 128
#define USERNUM 10
#define DINODESIZ 32
#define DINODEBLK 32
#define FILEBLK 512
#define NICFREE 50
#define NICINOD 50
#define DINODESTART 2*BLOCKSIZ
#define DATASTART (2+DINODEBLK)*BLOCKSIZ

#include <string>

using namespace std;

class FileSystem
{
	int type;

	bool IsInitalized;				//经过初始化

	int blockSize;		//每块大小
	int sysOpenFile;	//系统打开文件表最大项数
	int dirNum;			//每个目录所包含的最大目录项数（文件数）
	int dirSize;		//每个目录项名字部分所占字节数，另加i节点号2个字节
	int pwdSize;		//口令字
	int pwdNum;			//最多可设32个口令登录
	int noFile;			//每个用户最多可打开20个文件，即用户打开文件最大次数
	int nAddr;			//每个i节点最多指向10块，addr[0]~addr[9]
	int nHino;			//共128个Hash链表，提供索引i节点（必须为2的幂）
	int userNum;		//最多允许10个用户登录
	int dInodeSize;		//每个磁盘i节点所占字节
	int dInodeBLK;		//所有磁盘i节点共占32个物理块
	int fileBLK;		//共有512个目录文件物理块
	int nicFree;		//超级块中空闲块数组的最大块数
	int nicInode;		//超级块中空闲节点的最大块数
	int dInodeStart;	//i节点起始地址
	int dataStart;		//目录、文件区起始地址

	
public:
	FileSystem();

	void init();
	int WriteFileSystemDiskFile(string address);
	int ReadFileSystemDiskFile(string address);
};