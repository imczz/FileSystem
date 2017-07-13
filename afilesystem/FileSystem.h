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
	//沟槽函数
	FileSystem();

	//初始化参数
	void init();

	//将文件系统写入到文件中
	int WriteFileSystemDiskFile(string address);

	//将文件系统从文件中读取
	int ReadFileSystemDiskFile(string address);

	//磁盘i节点的分配
	int ialloc();

	//磁盘i节点的回收
	int ifree();

	//内存i节点获取
	int iget();

	//内存i节点释放
	int iput();

	//判断用户对文件有无某种特性访问权限
	int access();

	//实现对文件的存取搜索，将给定的路径名转换成所要搜索的文件的内存i结点指针（在目录数组中的位置）
	int namei();

	//在当前目录下搜索到一个空的目录数组，以便建立新的目录或文件时使用
	int iname();

	//空闲块的分配
	int balloc();

	//index块的回收
	int bfree(int blockindex);

	//文件系统格式化
	void format();

	//文件打开
	int open();

	//文件关闭
	int close();

	//文件创建
	int CreateFile();

	//文件删除
	int DeleteFile();

	//读取文件
	int read();

	//写入文件
	int write();

	//创建目录
	int mkdir();

	//改变当前目录
	int chdir();

	//列出文件目录
	int dir();
};