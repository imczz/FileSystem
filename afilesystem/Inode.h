#pragma once

//i节点
class Inode
{
	friend class FileSystem;
protected:
	bool state;					//状态：true:used，false:empty						(1 bit)
	int fileType;				//文件类型		0 普通文件 1 目录文件 2 特殊文件	(2 bit)
	int blockNumber;			//盘块数											(4 bit)
	bool permissions[9];		//权限												(9 bit)
	//2 Byte

	char userName;				//创建者											(8 bit)
	char userGroup;				//创建者所在组										(8 bit)
	//2 Byte

	long fileSize;				//文件大小											(64 bit)
	//8 Byte
	long createTime;			//创建时间											(64 bit)
	//8 Byte

	short blocksIndex[10];		//直接块号addr[0]-addr[9]							(96 bit - 6 bit)
	//12 Byte

	//long modifyTime;			//修改时间
public:
	Inode();
	Inode(bool state, int fileType, int blockNumber, bool * permissions, char userName, char userGroup, long fileSize, long createTime, short * blocksIndex);
	
	Inode(const Inode & inode);

	void init(bool state, int fileType, int blockNumber, bool * permissions, char userName, char userGroup, long fileSize, long createTime, short * blocksIndex);

	int LoadInodeInBuffer(char * buffer);			//char buffer[32]			
	static int CreateBufferFromInode(Inode & inode, char * buffer);		//外部的char buffer[32]

	~Inode();
};

